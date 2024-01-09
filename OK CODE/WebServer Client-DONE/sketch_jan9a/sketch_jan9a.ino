#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const char* ssid = "Dr.SudipChakraborty";
const char* password = "sudip@07011977";
String serverName = "http://192.168.199.92:80/";

WiFiClient client;
HTTPClient http;
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;
//______________________________________________________________________________________________________________________________________
void setup() 
{
  Serial.begin(115200); 
  Connect_With_Router();
 }
//_____________________________________________________________________________________________________________________________________
void loop() 
{
  if (TimeOut())
  {
      String Request_Packet= serverName + "?"+ Get_Json_Str();
      String data=Get_Data_From_Server(Request_Packet);
      Serial.println(data);
     // Parse_Receive_Data();     
  }
}
//_____________________________________________________________________________________________________________________________________
String Get_Data_From_Server(String pkt)
{
  String payload="";
  if(WiFi.status()== WL_CONNECTED)
    {
        http.begin(client, pkt.c_str());     
        int httpResponseCode = http.GET(); 
        if (httpResponseCode>0) 
        {
          payload = http.getString();
        }       
        http.end();
    }
    else 
    {
      Serial.println("WiFi Disconnected");
    }
    return payload;    
}
//_____________________________________________________________________________________________________________________________________
bool TimeOut(void)
{
  if ((millis() - lastTime) > timerDelay) 
    {
      lastTime = millis();
      return true;
    }
    else 
    {
      return false;
    }
}
//_____________________________________________________________________________________________________________________________________
void Connect_With_Router(void)
{
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
    Serial.println(WiFi.localIP());
}
//_____________________________________________________________________________________________________________________________________
String Get_Json_Str(void)
{
  String jsonString;
  StaticJsonDocument<200> doc;

  doc["cmd"]  = "GET";
  doc["cmd_str"]  = "test";

  serializeJson(doc, jsonString);
  return jsonString;
}
//_____________________________________________________________________________________________________________________________________
void Parse_Receive_Data(String payload)
{
    int i1 = payload.indexOf('{');
    int i2 = payload.indexOf("}");
    String subString2 = payload.substring(i1, i2+1);
    
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, subString2);

    if (error)
    {
      // Serial.print("JSON parsing failed: ");
      // Serial.println(error.c_str());
    } 
    else 
    {
      // // Access JSON elements
      // // Example: Accessing a value
      // int value = doc["SYS"]; // Replace "key" with your JSON key
      // Serial.println(value);
    }
}
//_____________________________________________________________________________________________________________________________________



