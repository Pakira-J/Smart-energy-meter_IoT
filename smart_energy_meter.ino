/*
 * Smart Energy Meter with ESP32, PZEM-004T, and 20x4 LCD
 * Features: Real-time monitoring with Blynk IoT integration
 * Author: Joydeep Pakira
 */

#define BLYNK_TEMPLATE_ID "TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "TEMPLATE_NAME" 
#define BLYNK_AUTH_TOKEN "AUTH_TOKEN"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>
#include <PZEM004Tv30.h>
#include <EEPROM.h>

// WiFi credentials
char ssid[] = "name_of_mobile_hotspot_or_wifi";
char pass[] = "password_to_connect_to_wifi";

// Blynk Auth Token
char auth[] = "AUTH_TOKEN";

// PZEM-004T setup (using Hardware Serial2)
PZEM004Tv30 pzem(Serial2, 16, 17); // RX=16, TX=17

// LCD setup (I2C address 0x27, 20 columns, 4 rows)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Variables for energy calculations
float voltage = 0.0;
float current = 0.0;
float power = 0.0;
float energy = 0.0;
float frequency = 0.0;
float pf = 0.0;

// Energy and billing variables
float totalEnergy = 0.0;
float energyRate = 5.50; // Rate per kWh (adjust according to your local rate)
float totalBill = 0.0;
unsigned long previousMillis = 0;
const long interval = 2000; // Update interval (2 seconds)

// EEPROM addresses
#define ENERGY_ADDR 0
#define EEPROM_SIZE 64

// Blynk Virtual Pins
#define VPIN_VOLTAGE    V0
#define VPIN_CURRENT    V1
#define VPIN_POWER      V2
#define VPIN_ENERGY     V3
#define VPIN_FREQUENCY  V4
#define VPIN_PF         V5
#define VPIN_BILL       V6

// Custom LCD characters for units
byte kwhChar[8] = {
  0b00000,
  0b10101,
  0b10101,
  0b10110,
  0b10100,
  0b10101,
  0b10101,
  0b00000
};

void setup() {
  Serial.begin(115200);
  
  // Initialize EEPROM
  EEPROM.begin(EEPROM_SIZE);
  
  // Load saved energy value from EEPROM
  EEPROM.get(ENERGY_ADDR, totalEnergy);
  if (isnan(totalEnergy) || totalEnergy < 0) {
    totalEnergy = 0.0;
  }
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, kwhChar);
  
  // Display startup message
  lcd.setCursor(0, 0);
  lcd.print("Smart Energy Meter");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  lcd.setCursor(0, 2);
  lcd.print("Connecting WiFi");
  
  // Initialize WiFi and Blynk
  Blynk.begin(auth, ssid, pass);
  
  // Initialize PZEM
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready!");
  delay(2000);
  lcd.clear();
  
  Serial.println("Smart Energy Meter Started");
}

void loop() {
  Blynk.run();
  
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    // Read PZEM data
    readPZEMData();
    
    // Update LCD display
    updateLCDDisplay();
    
    // Send data to Blynk
    sendDataToBlynk();
    
    // Save energy data to EEPROM every 10 readings (20 seconds)
    static int saveCounter = 0;
    saveCounter++;
    if (saveCounter >= 10) {
      saveEnergyToEEPROM();
      saveCounter = 0;
    }
  }
}

void readPZEMData() {
  voltage = pzem.voltage();
  current = pzem.current();
  power = pzem.power();
  energy = pzem.energy();
  frequency = pzem.frequency();
  pf = pzem.pf();
  
  // Handle NaN values
  if (isnan(voltage)) voltage = 0.0;
  if (isnan(current)) current = 0.0;
  if (isnan(power)) power = 0.0;
  if (isnan(energy)) energy = 0.0;
  if (isnan(frequency)) frequency = 0.0;
  if (isnan(pf)) pf = 0.0;
  
  // Update total energy (PZEM energy resets, so we maintain our own total)
  static float lastEnergy = 0.0;
  if (energy > lastEnergy) {
    totalEnergy += (energy - lastEnergy);
  } else if (energy < lastEnergy && energy > 0) {
    // Energy counter reset, add the difference
    totalEnergy += energy;
  }
  lastEnergy = energy;
  
  // Calculate total bill
  totalBill = totalEnergy * energyRate;
  
  // Debug output
  Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
  Serial.print("Current: "); Serial.print(current); Serial.println("A");
  Serial.print("Power: "); Serial.print(power); Serial.println("W");
  Serial.print("Energy: "); Serial.print(totalEnergy); Serial.println("kWh");
  Serial.print("Frequency: "); Serial.print(frequency); Serial.println("Hz");
  Serial.print("PF: "); Serial.println(pf);
  Serial.print("Bill: Rs."); Serial.println(totalBill);
  Serial.println("---");
}

void updateLCDDisplay() {
  lcd.clear();
  
  // Line 1: Voltage and Frequency
  lcd.setCursor(0, 0);
  lcd.print("V:");
  lcd.print(voltage, 1);
  lcd.print("V");
  lcd.setCursor(10, 0);
  lcd.print("F:");
  lcd.print(frequency, 1);
  lcd.print("Hz");
  
  // Line 2: Current and Power Factor
  lcd.setCursor(0, 1);
  lcd.print("I:");
  lcd.print(current, 3);
  lcd.print("A");
  lcd.setCursor(10, 1);
  lcd.print("PF:");
  lcd.print(pf, 2);
  
  // Line 3: Power
  lcd.setCursor(0, 2);
  lcd.print("P:");
  lcd.print(power, 1);
  lcd.print("W");
  
  // Line 4: Energy and Bill
  lcd.setCursor(0, 3);
  lcd.print("E:");
  lcd.print(totalEnergy, 3);
  lcd.print("kWh");
  //lcd.write(0); // Custom kWh character
  lcd.setCursor(11, 3);
  lcd.print("Rs.");
  lcd.print(totalBill, 2);
}

void sendDataToBlynk() {
  Blynk.virtualWrite(VPIN_VOLTAGE, voltage);
  Blynk.virtualWrite(VPIN_CURRENT, current);
  Blynk.virtualWrite(VPIN_POWER, power);
  Blynk.virtualWrite(VPIN_ENERGY, totalEnergy);
  Blynk.virtualWrite(VPIN_FREQUENCY, frequency);
  Blynk.virtualWrite(VPIN_PF, pf);
  Blynk.virtualWrite(VPIN_BILL, totalBill);
}

void saveEnergyToEEPROM() {
  EEPROM.put(ENERGY_ADDR, totalEnergy);
  EEPROM.commit();
  Serial.println("Energy data saved to EEPROM");
}

// Blynk function to reset energy counter
BLYNK_WRITE(V7) {
  int resetValue = param.asInt();
  if (resetValue == 1) {
    totalEnergy = 0.0;
    totalBill = 0.0;
    pzem.resetEnergy();
    saveEnergyToEEPROM();
    Serial.println("Energy counter reset");
  }
}

// Blynk function to update energy rate
BLYNK_WRITE(V8) {
  float newRate = param.asFloat();
  if (newRate > 0 && newRate < 100) { // Reasonable rate limits
    energyRate = newRate;
    Serial.print("Energy rate updated to: Rs.");
    Serial.println(energyRate);
  }
}

// Blynk connected callback
BLYNK_CONNECTED() {
  Serial.println("Blynk Connected");
  // Request the latest values from the server
  Blynk.syncAll();
}