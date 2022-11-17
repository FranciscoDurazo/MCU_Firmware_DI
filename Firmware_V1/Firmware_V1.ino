//Libraries
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
//
//Global Variables
String html = R"***(
<!DOCTYPE html>
<html>
  <head>    
    <title>SWITCH LED</title>
  </head>
  <body>
    <h1>SWITCH LED</h1>
    <p><a href=/ledon>LED on</a></p>
    <p><a href=/ledoff>LED off</a></p>
  </body>
</html>
)***";

uint8_t led = 5;         
const char* ssid = "ESP8266_AP";
ESP8266WebServer server(80);



void handleRoot(){
  server.send(200,"text/html", html); 
}

void ledon(){
  digitalWrite(led,HIGH);
  server.send(200,"text/html", html); 
}

void ledoff(){
  digitalWrite(led,LOW);
  server.send(200,"text/html", html); 
}

void setup() {
  delay(1000);
  Serial.begin(460800);
  Serial.println("Configurando, aguanta...");
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  
  //Acciones
  server.on("/", handleRoot);
  server.on("/ledon", ledon);
  server.on("/ledoff", ledoff);

  server.begin();
  Serial.println("¡Servidor iniciado correctamente!");  
  pinMode(led, OUTPUT);
}

void loop() {
  server.handleClient();
}
