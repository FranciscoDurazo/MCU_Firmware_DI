
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>

//---------------------------------
//#include "html.h"                       //header file containing HTML code

#include "DHTesp.h"
 
DHTesp dht;
//---------------------------------
const char* ssid     = "CETYS_Universidad";
const char* password = "";
const char* host = "project-8266-2022.000webhostapp.com";
const char* host2 = "files.000webhost.com";
int led = 5;
ESP8266WebServer server(80);            //pointer to communicate with client via port 80
//---------------------------------

/*void handleRoot()
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
}*/
void setup()
{
    pinMode(led,OUTPUT);
    
    dht.setup(4,DHTesp::DHT11);
    Serial.begin(115200);
    WiFi.begin(ssid,password);           //connect to Wi-Fi network with SSID and password
    Serial.print("\n\r \n\rWorking to connect");
    while (WiFi.status() != WL_CONNECTED) {delay(500); Serial.print(".");}
    Serial.println("");
    /*Serial.println("ESP8266 Webpage");*/
    Serial.println("Connected to WiFi");
    /*Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    server.on("/", handleRoot);           //initialize web server
    server.on("/ledon", ledon);
    server.on("/ledoff", ledoff);
    server.begin();
    Serial.println("HTTP server started");*/
}
//==============================================================
void loop()
{
  //server.handleClient();                //server continously looks for client request
  float temperature = dht.getTemperature();
  if(isnan(temperature)){
    Serial.println("Failed to read DHT11");
  }else{
    /*Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");*/
  }
  //delay(300);
  WiFiClient client;
  HTTPClient http;
  const int httpPort = 21; //estaba 5555
   /* if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }
    else if(client.connect(host, httpPort)){
      Serial.println("Success!!");
    }*/

//https://project-8266-2022.000webhostapp.com/connect.php?temperature=2


/*
    String serverPath = "https://project-8266-2022.000webhostapp.com/connect.php?temperature=8";
      
      // Your Domain name with URL path or IP address with path
    http.begin(client, serverPath.c_str());

    int httpResponseCode = http.GET();
      
    if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
      // Free resources
      http.end();
*/


    client.connect(host2, httpPort);
    //client.print("GET https://project-8266-2022.000webhostapp.com/connect.php?temperature=2 HTTP/1.1\r\nHost: files.000webhost.com:21\r\nConnection: close\r\n\r\n");

//http://files.000webhost.com/project-8266-2022/pbulic_html/connect.php?


    client.print(String("GET /connect.php?") + 
                              ("temperature=") + temperature +
                              " HTTP/1.1\r\n" +
                    "Host: " + host + "\r\n" +
                    "Connection: close\r\n\r\n");
                    
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 1000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        
    }

    Serial.println();
    Serial.println("closing connection");

}





