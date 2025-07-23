#include <Wire.h>                 // Include Wire library for I2C communication
#include <LiquidCrystal_I2C.h>     // Include the LCD library for I2C
#include <DHT.h>                   // Include the DHT sensor library

// Define the DHT sensor pin and type
#define DHTPIN 2                  // Pin where the data pin of DHT11 is connected
#define DHTTYPE DHT11             // DHT 11 sensor type

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Initialize the LCD with I2C address 0x27 (most common)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 16 columns, 2 rows

void setup() {
  // Start the serial communication (optional for debugging)
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();                  // Use the init() function for LCD initialization
  lcd.backlight();             // Turn on the backlight

  // Initialize the DHT sensor
  dht.begin();

  // Display a welcome message on LCD
  lcd.setCursor(0, 0);  // Set cursor to column 0, row 0
  lcd.print("DHT11 Sensor");
  lcd.setCursor(0, 1);  // Set cursor to column 0, row 1
  lcd.print("Temp & Humidity");
  delay(2000); // Display the welcome message for 2 seconds
}

void loop() {
  // Wait a few seconds between readings (DHT11 requires this)
  delay(2000);

  // Read humidity and temperature from the DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Temperature in Celsius

  // Check if the readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("DHT Read Error");
    return;
  }

  // Print the readings to the serial monitor (optional for debugging)
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Clear the LCD and display the temperature and humidity on the LCD
  lcd.clear();               // Clear the LCD
  lcd.setCursor(0, 0);       // Set cursor to the first row
  lcd.print("Temp: ");
  lcd.print(temperature);    // Print temperature on the first row
  lcd.print(" C");

  lcd.setCursor(0, 1);       // Set cursor to the second row
  lcd.print("Humidity: ");
  lcd.print(humidity);       // Print humidity on the second row
  lcd.print(" %");
}
