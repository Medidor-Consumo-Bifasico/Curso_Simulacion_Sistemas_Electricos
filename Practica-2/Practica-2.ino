/*
  Autor: Vidal Bazurto (avbazurt@espol.edu.ec)
  GitHub: https://github.com/avbazurt/Simulacion_Sistemas_Electricos
  Practica 1: Introduccion Sensor PZEM004TV30
*/

#include <PZEM004Tv30.h>

//Definimos los pines de comunicacion PZEM004T
#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17

//Creamos un objeto PZEM004Tv30 con los pines
PZEM004Tv30 pzem(Serial2, PZEM_RX_PIN, PZEM_TX_PIN);

void setup() {
  //ACTIVAMOS EL PUERTO SERIAL
  Serial.begin(9600);

  //Limpiamos la informacion
  Serial.println("CLEARDATA");
  
  //Definimos los encabezados de la tabla
  Serial.println("LABEL,t,voltaje [V],corriente [A],potencia [W],energia [KwH],frecuencia [Hz],factor potencia");
}

void loop() {
  //Leemos los datos del sensor
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();

  // Validamos los datos del sensor
  if (isnan(voltage)) {
    Serial.println("Error reading voltage");
  } else if (isnan(current)) {
    Serial.println("Error reading current");
  } else if (isnan(power)) {
    Serial.println("Error reading power");
  } else if (isnan(energy)) {
    Serial.println("Error reading energy");
  } else if (isnan(frequency)) {
    Serial.println("Error reading frequency");
  } else if (isnan(pf)) {
    Serial.println("Error reading power factor");
  } else {
    
    //Enviamos los datos para archivar en el EXCEL
    Serial.printf("DATA,TIME,%f,%f,%f,%f,%f,%f\n",voltage,current,power,energy,frequency,pf);
  }

  //Esperamos un tiempo
  delay(1000);
}
