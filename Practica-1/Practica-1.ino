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
  Serial.begin(115200); //ACTIVAMOS EL PUERTO SERIAL
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

    // Mostramos por consola los datos
    Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
    Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
    Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
    Serial.print("Energy: ");       Serial.print(energy, 3);     Serial.println("kWh");
    Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
    Serial.print("PF: ");           Serial.println(pf);
  }

  //Esperamos un tiempo
  Serial.println();
  delay(2000);
}
