
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//---------------------------------
#include "html.h"                       //header file containing HTML code
//---------------------------------
const char* ssid     = "CETYS_Universidad";
int led = 5;
//const char* password = "password";
ESP8266WebServer server(80);            //pointer to communicate with client via port 80
//---------------------------------

void handleRoot()
{
  server.send(200, "text/html", html);
}
void ledon()
{
  digitalWrite(led, 1);
  server.send(200, "text/html", html);
}
void ledoff()
{
  digitalWrite(led, 0);
  server.send(200, "text/html", html);
}
void setup()
{
  pinMode(led,OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid);           //connect to Wi-Fi network with SSID and password
  Serial.print("\n\r \n\rWorking to connect");
  while (WiFi.status() != WL_CONNECTED) {delay(500); Serial.print(".");}
  Serial.println("");
  Serial.println("ESP8266 Webpage");
  Serial.println("Connected to WiFi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);           //initialize web server
  server.on("/ledon", ledon);
  server.on("/ledoff", ledoff);
  server.begin();
  Serial.println("HTTP server started");
}
//==============================================================
void loop()
{
  server.handleClient();                //server continously looks for client request
}