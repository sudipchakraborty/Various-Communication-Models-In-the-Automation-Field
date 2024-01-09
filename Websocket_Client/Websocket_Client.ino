#include <WiFi.h>
#include <ArduinoWebsockets.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* webSocketServer = "ws://your_server_address:port"; // Replace with your server details

WebsocketsClient client;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  client.begin(webSocketServer);
  client.onMessage([](WebsocketsMessage message) {
    if (message) {
      Serial.print("Received: ");
      Serial.println(message.data());
    }
  });
}

void loop() {
  client.loop();
  if (!client.available()) return;

  // Sending data
  String dataToSend = "Hello, server!";
  client.send(dataToSend);
  delay(1000); // Adjust delay as needed
}
