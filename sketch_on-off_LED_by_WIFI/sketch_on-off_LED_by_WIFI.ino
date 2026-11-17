
#include <WiFi.h>
#include <WebServer.h>

// Access Point Settings
const char* ssid = "ESP32-C3";
const char* password = "12345678";

// Static IP
IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// LED
#define LED_PIN 4

WebServer server(80);

bool ledState = false;

void handleRoot() {

  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>ESP32-C3 LED</title>
    <style>
      body {
        background: #222;
        color: white;
        text-align: center;
        font-family: Arial;
        padding-top: 50px;
      }
      button {
        padding: 20px 45px;
        font-size: 22px;
        border: none;
        border-radius: 12px;
        margin: 15px;
        color: white;
      }
      .on { background: green; }
      .off { background: red; }
    </style>
  </head>
  <body>
    <h1>ESP32-C3</h1>
    <h2>LED CONTROL</h2>
    <a href="/on"><button class="on">LED ON</button></a>
    <a href="/off"><button class="off">LED OFF</button></a>
  </body>
  </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void setup() {

  Serial.begin(115200);
  delay(1500);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.mode(WIFI_AP);
  WiFi.setSleep(false);

  // Configure fixed IP
  WiFi.softAPConfig(local_IP, gateway, subnet);

  // Start Access Point on channel 1
  bool result = WiFi.softAP(
    ssid,
    password,
    1,
    0,
    4
  );

  if (!result) {
    Serial.println("AP FAILED!");
    return;
  }

  Serial.println("ACCESS POINT STARTED");

  Serial.print("SSID: ");
  Serial.println(ssid);

  Serial.print("PASSWORD: ");
  Serial.println(password);

  Serial.print("IP ADDRESS: ");
  Serial.println(WiFi.softAPIP());

  // LED ON
  server.on("/on", []() {
    ledState = true;
    digitalWrite(LED_PIN, HIGH);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  // LED OFF
  server.on("/off", []() {
    ledState = false;
    digitalWrite(LED_PIN, LOW);
    server.sendHeader("Location", "/");
    server.send(303);
  });

  server.on("/", handleRoot);

  server.begin();

  Serial.println("WEB SERVER STARTED");
}

void loop() {
  server.handleClient();
}
