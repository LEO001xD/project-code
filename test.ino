#include <TridentTD_LineNotify.h>
#include <WiFi.h>
#define SSID "DX100"               
#define PASSWORD "11111111"                      
#define LINE_TOKEN "HUZldWYLqry1RakCi7gxmgTzjdxccHUwrrvApBWWs05"


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

#define SOI_PIN 2
#define Relay1 14

#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 13, 16, 17, 18, 19);

void setup() {
  pinMode(SOI_PIN,INPUT);
  pinMode(Relay1, OUTPUT);
  dht.begin();
  
  strip.begin();
  strip.show(); // ตั้งค่าสีเริ่มต้นให้ทุกหลอดเป็น 'ปิด'

  lcd.begin(16, 2);

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  LINE.setToken(LINE_TOKEN);
  LINE.notify("line work");
  
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
    LINE.notify("เติมน้ำ");
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
void soi_moisture_and_rod_nam() {//ความขื้นในดิน
  moisture = analogRead(SOI_PIN); // read the analog value from sensor
  Serial.print("Moisture in soi value: ");
  Serial.println(moisture);
  delay(500);
  if(moisture<=1000){
    digitalWrite(Relay1,HIGH);
    } 
  else{
    digitalWrite(Relay1,LOW);
    } 
  }
void loop() {
  soi_moisture_and_rod_nam();
  fillSolidColor(strip.Color(55, 10, 255)); // black light
  DHT();
  ultra();

  delay(100);
}
