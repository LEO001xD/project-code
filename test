#include <DHT.h>
#define DHTPIN 15   // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT sensor type
DHT dht(DHTPIN, DHTTYPE);
int moisture;
float temperature;
float humidity;

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
void loop() { //อุณหภูมิในอากาศ เขียนไม่เป็น
  DHT();
  delay(100);
}
