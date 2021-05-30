#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClient.h>
#include <GY21.h>
GY21 sensor;

const char* ssid = "";
const char* password = "";
const char* serverName = "";
String apiKeyValue = "tPmAT5Ab3j7F9";

unsigned char FucCheckSum(unsigned char *i, unsigned char ln)//CheckSum
{
  unsigned char j, tempq = 0;
  i += 1;
  for (j = 0; j < (ln - 2); j++)
  {
    tempq += *i;
    i++;
  }
  tempq = (~tempq) + 1;
  return (tempq);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 15, 13);//Start Serial2, mode, RX, TX
  Wire.begin();

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  float temp = sensor.GY21_Temperature();
  float hum = sensor.GY21_Humidity();
  float O3;
  byte readBuffer[9] = {};

  Serial2.readBytes(readBuffer, sizeof(readBuffer));//Q&A read
  byte Check = FucCheckSum(readBuffer, sizeof(readBuffer));//Call checksum and compare
  if (Check == readBuffer[8]) {//Compare checksum
    O3 = ((readBuffer[2] * 256) + readBuffer[3]) * 0.1; //If checksum matches, save O3 value
  }

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "api_key=" + apiKeyValue + "&value1=" + String(temp) + "&value2=" + String(hum) + "&value3=" + String(O3) + "";
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  delay(10000);
}
