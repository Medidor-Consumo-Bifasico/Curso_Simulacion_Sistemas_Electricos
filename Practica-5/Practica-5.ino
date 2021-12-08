/*
  ********** 2pem100a ***********
  Autor: Vidal Bazurto (avbazurt@espol.edu.ec)
  Reviewed: vasanza
  GitHub: https://github.com/Medidor-Consumo-Bifasico/Curso_Simulacion_Sistemas_Electricos
  More information: https://2pem100a.blogspot.com/
  Practica 5: Adquisicion de datos Bifasicos Sensor PZEM004TV30

*/

#include <PZEM004Tv30.h>

//Definimos los pines de comunicacion PZEM004T
#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17

//Creamos dos objeto PZEM004Tv30 con los pines
PZEM004Tv30 faseA(Serial2, PZEM_RX_PIN, PZEM_TX_PIN, 0x20);
PZEM004Tv30 faseB(Serial2, PZEM_RX_PIN, PZEM_TX_PIN, 0x05);

struct Sensor
{ float voltaje;    // Nombre del modelo
  float corriente;       // Numero de pines digitales
  float potencia;       // Numero de pines digitales
  float energia;       // Numero de pines digitales
  float frecuencia;       // Numero de pines digitales
  float fp;       // Numero de pines digitales
} ;

Sensor DatosFaseA = {0, 0, 0, 0, 0, 0};
Sensor DatosFaseB = {0, 0, 0, 0, 0, 0};

//Funciones Correspondiente Sensor PZEM004T
float ValidarDato(float dato);
void MedicionSensor(Sensor &DatosFase, PZEM004Tv30 Fase);
void MostrarDatos(String TextoFase, Sensor &DatoFase,PZEM004Tv30 Fase);

void setup() {
  //ACTIVAMOS EL PUERTO SERIAL
  Serial.begin(115200);
}

void loop() {
  MostrarDatos("Fase A",DatosFaseA,faseA);
  MostrarDatos("Fase B",DatosFaseB,faseB);
  delay(5000); 
}

float ValidarDato(float dato) { //Funcion que nos permite validar el dato medido
  if (isnan(dato)) {
    return -1;
  }
  return dato;
}

void MedicionSensor(Sensor &DatoFase, PZEM004Tv30 Fase) { //Fucion que se encargara de realizar las consultas al modulo PZEM004T
  DatoFase.voltaje = ValidarDato(Fase.voltage());
  DatoFase.corriente = ValidarDato(Fase.current());
  DatoFase.potencia = ValidarDato(Fase.power());
  DatoFase.energia = ValidarDato(Fase.energy());
  DatoFase.frecuencia = ValidarDato(Fase.frequency());
  DatoFase.fp = ValidarDato(Fase.pf());
}

void MostrarDatos(String TextoFase,Sensor &DatoFase, PZEM004Tv30 Fase) {
  // Mostramos por consola los datos
  Serial.printf("Mediciones %s:\n",TextoFase);
  MedicionSensor(DatoFase, Fase);
  Serial.print("Voltage: ");      Serial.print(DatoFase.voltaje);      Serial.println("V");
  Serial.print("Current: ");      Serial.print(DatoFase.corriente);      Serial.println("A");
  Serial.print("Power: ");        Serial.print(DatoFase.potencia);        Serial.println("W");
  Serial.print("Energy: ");       Serial.print(DatoFase.energia, 3);     Serial.println("kWh");
  Serial.print("Frequency: ");    Serial.print(DatoFase.frecuencia, 1); Serial.println("Hz");
  Serial.print("PF: ");           Serial.println(DatoFase.fp);
  Serial.println(" ");
}
