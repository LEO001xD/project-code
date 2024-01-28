#include <DHT.h>
#define DHTPIN 15   // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT sensor type
DHT dht(DHTPIN, DHTTYPE);
int moisture;
float temperature;
float humidity;

#include <HCSR04.h>
HCSR04 hc(23, 22);

void setup() {
  dht.begin();
  Serial.begin(115200);
}
void DHT() { //อุณหภูมิในอากาศ เขียนไม่เป็น
  //dht
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  char mix_temp_humi[50];
  sprintf(mix_temp_humi, "Temperature %d \n Humidity %d", temperature ,humidity);
  Serial.println(temperature);
  Serial.println(humidity);
}
void ultra() { //อุณหภูมิในอากาศ เขียนไม่เป็น
  int distance = hc.dist();
  Serial.println(distance); //return current distance (cm) in serial
  delay(60);
}
void loop() { //อุณหภูมิในอากาศ เขียนไม่เป็น
  DHT();
  ultra();
  delay(100);
}
