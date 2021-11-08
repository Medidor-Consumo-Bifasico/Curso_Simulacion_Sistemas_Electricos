/*
  Autor: Vidal Bazurto (avbazurt@espol.edu.ec)
  GitHub: https://github.com/avbazurt/Simulacion_Sistemas_Electricos
  Practica 0: ESP32 en Arduino IDE
*/

#define VARIABLE "HOLA MUNDO"

//Definimos una constante
int contador = 0;

void setup() {
  Serial.begin(115200); //ACTIVAMOS EL PUERTO SERIAL
}

void loop() {
  Serial.print(VARIABLE);
  Serial.print(" ");
  Serial.println(contador); //Mostramos el valor del contador
  contador++;
  delay(1000);
}
