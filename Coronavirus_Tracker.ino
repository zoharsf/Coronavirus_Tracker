#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <BearSSLHelpers.h>
#include <CertStoreBearSSL.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display
const char* ssid = "WIFI_NETWORK_NAME";
const char* password = "WIFI_NETWORK_PASSWORD";

String countrylUrl = "https://corona.lmao.ninja/v2/countries/COUNTRY_NAME";
String worldUrl = "https://corona.lmao.ninja/v2/all";

DynamicJsonDocument doc(1024);
HTTPClient https;

void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\n");

  u8g2.begin();
  u8g2.enableUTF8Print();
}

void loop(void) {
  JsonObject obj = getData(countrylUrl);

  long cases = obj[String("cases")];
  long deaths = obj[String("deaths")];

  char countryCasesChar[16];
  itoa(cases, countryCasesChar, 10);
  char countryDeathsChar[16];
  itoa(deaths, countryDeathsChar, 10);
  Serial.println(cases);
  Serial.println(deaths);

  obj.clear();
  obj = getData(worldUrl);

  cases = obj[String("cases")];
  deaths = obj[String("deaths")];

  char worldCasesChar[16];
  itoa(cases, worldCasesChar, 10);
  char worldDeathsChar[16];
  itoa(deaths, worldDeathsChar, 10);

  Serial.println(cases);
  Serial.println(deaths);
  Serial.println("----------");

  u8g2.firstPage();
  while (u8g2.nextPage()) {
    u8g2.setFont(u8g2_font_profont17_mf);
    u8g2.drawStr(45, 19, "Corona");

    u8g2.setFont(u8g2_font_profont12_mf);
    u8g2.drawStr(2, 48, "Cases");
    u8g2.drawStr(2, 64, "Deaths");

    u8g2.drawStr(42, 33, "World");
    u8g2.drawStr(42, 48, worldCasesChar);
    u8g2.drawStr(42, 64, worldDeathsChar);

    u8g2.drawStr(92, 33, "COUNTRY_NAME");
    u8g2.drawStr(92, 48, countryCasesChar);
    u8g2.drawStr(92, 64, countryDeathsChar);
  }
  
  obj.clear();
  
  delay(600000);
}

JsonObject getData(String dataUlr) {
  doc.clear();

  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();

  https.begin(*client, dataUlr);
  int httpCode = https.GET();
  String payloadString = https.getString();
  https.end();

  deserializeJson(doc, payloadString);
  return doc.as<JsonObject>();
}
