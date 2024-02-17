#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_BME280 bme;

void printDisplay(const char* customMessage, int height = 0) {
  //display.clearDisplay();

  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0, height);             // Start at the top-left corner
  display.println(customMessage);

  display.display();
  //delay(10);
}

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(1000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  if (!bme.begin(0x76)) {
    Serial.println(F("Could not find a valid BME280 sensor, check wiring!"));
    while (1)
      ;
  }

}

void loop() {
  // Clear the display once before entering the loop
  display.clearDisplay();

  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F; // Convert pressure to hPa

  // Convert sensor values to const char*
  char tempStr[30];
  snprintf(tempStr, sizeof(tempStr), "Temp: %.2f degrees", temperature);

  char humidityStr[30];
  snprintf(humidityStr, sizeof(humidityStr), "Humidity: %.2f %%", humidity);

  char pressureStr[30];
  snprintf(pressureStr, sizeof(pressureStr), "Pressure: %.2f hPa", pressure);

  // Display each reading on the OLED screen
  printDisplay(tempStr, 0);    // Display temperature
  printDisplay(humidityStr, 8); // Display humidity below temperature
  printDisplay(pressureStr, 16); // Display pressure below humidity

  delay(2000); // Adjust delay as needed
}