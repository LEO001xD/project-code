#include <DHT.h>
#define DHTPIN 15   // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT sensor type
DHT dht(DHTPIN, DHTTYPE);
int moisture;
float temperature;
float humidity;

#include <HCSR04.h>
HCSR04 hc(23, 22);

#include <Adafruit_NeoPixel.h>
#define PIN            13  // พินที่ Neopixel ต่ออยู่
#define NUMPIXELS      16 // จำนวน Neopixel ในสตริป
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  dht.begin();
  
  strip.begin();
  strip.show(); // ตั้งค่าสีเริ่มต้นให้ทุกหลอดเป็น 'ปิด'
  
  Serial.begin(115200);
}
void DHT() {
  //dht
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  char mix_temp_humi[50];
  sprintf(mix_temp_humi, "Temperature %d \n Humidity %d", temperature ,humidity);

  Serial.print("temperature : ");
  Serial.println(temperature);
  Serial.print("humidity :");
  Serial.println(humidity);
  
}
void ultra() { 
  int distance = hc.dist();
  if (distance <= 20){
    Serial.println("เติมน้ำ");
  }
  Serial.print("distance :"); //return current distance (cm) in serial
  Serial.println(distance); //return current distance (cm) in serial

}
void fillSolidColor(uint32_t color) { //neopixel
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}
void loop() {
  fillSolidColor(strip.Color(55, 10, 255)); // black light
  DHT();
  ultra();
  delay(100);
}
