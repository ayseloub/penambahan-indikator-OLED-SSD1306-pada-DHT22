#include <DHTesp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  
#define SCREEN_HEIGHT 64  
#define OLED_RESET    -1   
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define pinDHT 27

DHTesp dhtSensor;

void setup() {
  Serial.begin(115200);

  dhtSensor.setup(pinDHT, DHTesp::DHT22);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  
  }

  
  display.clearDisplay();
  display.display();


  Serial.print("Free memory: ");
  Serial.println(ESP.getFreeHeap());
}

void loop() {
  delay(1000);  

  TempAndHumidity data = dhtSensor.getTempAndHumidity();
  float temp = data.temperature;
  float hum = data.humidity;

  if (isnan(hum) || isnan(temp)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0); 

  display.print("Temp: ");
  display.print(temp);
  display.println(" C");
  display.print("Humidity: ");
  display.print(hum);
  display.println(" %");

  if (temp > 30) {
    display.setTextSize(1); 
    display.setCursor(0, 30); 
    display.println("Suhu Tinggi!"); 
  }
  
  if (hum < 20) {
    display.setTextSize(1); 
    display.setCursor(0, 50); 
    display.println("Kelembapan Rendah!"); 
  }

  display.display();

  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C, Humidity: ");
  Serial.print(hum);
  Serial.println(" %");
  Serial.print("Free memory: ");
  Serial.println(ESP.getFreeHeap());
}
