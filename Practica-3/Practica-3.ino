/*
  Autor: Vidal Bazurto (avbazurt@espol.edu.ec)
  GitHub: https://github.com/avbazurt/Simulacion_Sistemas_Electricos
  Practica 1: Introduccion Sensor PZEM004TV30
*/

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <PZEM004Tv30.h>

#define ssid "TU_SIID"
#define password "TU_CONTRASEÑA"

//Definimos los pines de comunicacion PZEM004T
#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17

//Creamos un objeto PZEM004Tv30 con los pines
PZEM004Tv30 pzem(Serial2, PZEM_RX_PIN, PZEM_TX_PIN);

struct Sensor
{ float voltaje;    // Nombre del modelo
  float corriente;       // Numero de pines digitales
  float potencia;       // Numero de pines digitales
  float energia;       // Numero de pines digitales
  float frecuencia;       // Numero de pines digitales
  float fp;       // Numero de pines digitales
} ;

Sensor DatosSensor = {0,0,0,0,0,0};

void MedicionSensor() {
  DatosSensor.voltaje = pzem.voltage();
  if (isnan(DatosSensor.voltaje)) {// Validamos los datos del sensor
    DatosSensor.voltaje = -1;
  }

  DatosSensor.corriente = pzem.current();
  if (isnan(DatosSensor.corriente)) {
    DatosSensor.corriente = -1;
  }

  DatosSensor.potencia = pzem.power();
  if (isnan(DatosSensor.potencia)) {
    DatosSensor.potencia = -1;
  }


  DatosSensor.energia = pzem.energy();
  if (isnan(DatosSensor.energia)) {
    DatosSensor.energia = -1;
  }

  DatosSensor.frecuencia = pzem.frequency();
  if (isnan(DatosSensor.frecuencia)) {
    DatosSensor.frecuencia = -1;
  }

  DatosSensor.fp = pzem.pf();
  if (isnan(DatosSensor.fp)) {
    DatosSensor.fp = -1;
  }
  
}



//WEB SERVER
AsyncWebServer server(80);

char* formato_html =
  "<!DOCTYPE html>"
  "<html lang=\"en\">"
  "<head>"
  "    <meta charset=\"UTF-8\">"
  "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">"
  "    <META HTTP-EQUIV='Refresh' CONTENT='1'>"
  "    <title>ESP32 WebServer</title>"
  "    <style> body { background-color: #fffff; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }</style>"
  "</head>"
  "<body>"
  "    <h2>SENSOR CONSUMO ENERGETICO</h2>"
  "    <h3>Voltaje: %f [V]</h3>"
  "    <h3>Corriente: %f [A]</h3>"
  "    <h3>Potencia: %f [W]</h3>"
  "    <h3>Energia: %f [KwH]</h3>"
  "    <h3>Frecuencia: %f [Hz]</h3>"
  "    <h3>Factor Potencia: %f</h3>"
  "</body>"
  "</html>";

char buffer_html[1000];

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void connectToWifi() {
  WiFi.enableSTA(true);

  delay(2000);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

}

void setup() {
  delay(5000);
  
  //ACTIVAMOS EL PUERTO SERIAL
  Serial.begin(115200);
  Serial.println(WiFi.macAddress());

  //Conectamos el WIFI
  connectToWifi();

  //Configuramos el Web Server
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    MedicionSensor();

    //Mostramos los datos
    sprintf(buffer_html, 
    formato_html, 
    DatosSensor.voltaje,
    DatosSensor.corriente,
    DatosSensor.potencia,
    DatosSensor.energia,
    DatosSensor.frecuencia,
    DatosSensor.fp);

    request->send_P(200, "text/html", buffer_html);
  });

  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
  delay(4000);
}
