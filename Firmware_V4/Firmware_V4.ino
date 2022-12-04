#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
// Sustituir por los datos de vuestro WiFi
const char* ssid = "INFINITUM7188";              //Add your WIFI network name 
const char* password =  "pKTnn7CvtU";           //Add WIFI password
String url = "http://project-8266-2022.000webhostapp.com/esp32_update.php";

//Variables used in the code
String LED_id = "1";                  //Just in case you control more than 1 LED
bool toggle_pressed = false;          //Each time we press the push button    
String data_to_send = "";             //Text data to send to the server
unsigned int Actual_Millis, Previous_Millis;
int refresh_time = 200;               //Refresh rate of connection to website (recommended more than 1s)


//Inputs/outputs
int button1 = 13;                     //Connect push button on this pin
int LED = 5;                          //Connect LED on this pin (add 150ohm resistor)


//Button press interruption

void setup() {
  delay(10);
  Serial.begin(115200);                   //Start monitor
  pinMode(LED, OUTPUT);                   //Set pin 2 as OUTPUT
  //pinMode(button1, INPUT_PULLDOWN);       //Set pin 13 as INPUT with pulldown
  //attachInterrupt(button1, isr, RISING);  //Create interruption on pin 13

  WiFi.begin(ssid, password);             //Start wifi connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected, my IP: ");
  Serial.println(WiFi.localIP());
  Actual_Millis = millis();               //Save time for refresh loop
  Previous_Millis = Actual_Millis; 
}
HTTPClient http;
WiFiClient client;
String payload;
void loop() {  
  //We make the refresh loop using millis() so we don't have to sue delay();
  
  if (http.begin(client, url)) //Iniciar conexión
   {
      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();  // Realizar petición
      if (httpCode > 0) {
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);
         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            payload = http.getString();   // Obtener respuesta
            Serial.println(payload);   // Mostrar respuesta por serial
            yield();
         }
      }
      else {
         Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
      if(payload == "LED_is_on"){
        digitalWrite(LED,HIGH);
      }
      else if(payload == "LED_is_off"){
        digitalWrite(LED,LOW);
      }
   }
   else {
      Serial.printf("[HTTP} Unable to connect\n");
   }

   Serial.println("Llego aqui");
   
   delay(3000);
   //Serial.println("Llego aqui x2");
  
}