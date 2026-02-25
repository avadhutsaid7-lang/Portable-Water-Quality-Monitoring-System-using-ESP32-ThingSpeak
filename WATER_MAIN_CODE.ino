#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include "ThingSpeak.h"

// ---------------- PIN DEFINITIONS ----------------
#define ONE_WIRE_BUS 5
#define TURBIDITY_PIN 35
#define PH_PIN 34
#define BUZZER_PIN 12

// ---------------- WIFI DETAILS ----------------
const char* ssid = "Avadhut's M35";
const char* password = "12345678";

// ---------------- THINGSPEAK ----------------
WiFiClient client;
unsigned long channelNumber = 3243286;
const char* apiKey = "WMNH2DQT6RZXGQ5D";

// ---------------- OBJECTS ----------------
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- TIMING ----------------
unsigned long lastSend = 0;

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  sensors.begin();
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Quality");
  lcd.setCursor(0, 1);
  lcd.print("Monitoring Sys");
  delay(2000);

  lcd.clear();
  lcd.print("Connecting WiFi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    lcd.print(".");
  }

  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1500);

  ThingSpeak.begin(client);
}

void loop() {

  // ----------- READ TEMPERATURE -----------
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  // ----------- READ TURBIDITY -----------
  int turbidityRaw = analogRead(TURBIDITY_PIN);
  float turbidity = map(turbidityRaw, 0, 4095, 0, 100);

  // ----------- READ pH -----------
  int phRaw = analogRead(PH_PIN);
  float voltage = (phRaw / 4095.0) * 3.3;

  // Basic pH conversion formula (approximate)
  float pH = 7 + ((2.5 - voltage) / 0.18);

  // ----------- LCD DISPLAY -----------
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature,1);
  lcd.print("C pH:");
  lcd.print(pH,1);

  lcd.setCursor(0, 1);
  lcd.print("Turb:");
  lcd.print(turbidity,0);
  lcd.print("%");

  // ----------- BUZZER LOGIC -----------
  if (temperature > 30 || pH < 6 || pH > 8.5) {
    digitalWrite(BUZZER_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
  }

  // ----------- SEND TO THINGSPEAK EVERY 10 SEC -----------
  if (millis() - lastSend >= 10000) {

    ThingSpeak.setField(1, temperature);
    ThingSpeak.setField(2, turbidity);
    ThingSpeak.setField(3, pH);

    int status = ThingSpeak.writeFields(channelNumber, apiKey);
    Serial.println(status == 200 ? "ThingSpeak Updated" : "Update Failed");

    lastSend = millis();
  }

  delay(1000);
}