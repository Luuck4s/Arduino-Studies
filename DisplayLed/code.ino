/**
* Receive a signal from remote controller and show a number in led 
* library:
* - IRremote version 1.0
* ref:
* - https://kitsarduino.com.br/cmp/display.html 
* - https://kitsarduino.com.br/cmp/controle_remoto.html
*/

#include <IRremote.h>

byte seven_seg_digits[10][7] = {
  { 1, 1, 1, 1, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 0, 0 },
  { 1, 1, 0, 1, 1, 0, 1 },
  { 1, 1, 1, 1, 0, 0, 1 },
  { 0, 1, 1, 0, 0, 1, 1 },
  { 1, 0, 1, 1, 0, 1, 1 },
  { 1, 0, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 0, 0, 0, 0 },
  { 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 0, 1, 1 }
};


const int Controle_Pin = 12;
IRrecv irrecv(Controle_Pin);
decode_results resultados;
unsigned long key_value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void sevenSegWrite(byte digit) {
  byte pin = 2;
  for (byte segCount = 0; segCount < 7; ++segCount) {
    digitalWrite(pin, seven_seg_digits[digit][segCount]);
    ++pin;
  }
}

void loop() {
  if (irrecv.decode(&resultados)) {
    Serial.println(resultados.value);

    switch (resultados.value) {
      case 0xFF6897:
        Serial.println("Botão 0");
        sevenSegWrite(0);
        break;
      case 0xFF30CF:
        Serial.println("Botão 1");
        sevenSegWrite(1);
        break;
      case 0xFF18E7:
        Serial.println("Botão 2");
        sevenSegWrite(2);
        break;
      case 0xFF7A85:
        Serial.println("Botão 3");
        sevenSegWrite(3);
        break;
      case 0xFF10EF:
        Serial.println("Botão 4");
        sevenSegWrite(4);
        break;
      case 0xFF38C7:
        Serial.println("Botão 5");
        sevenSegWrite(5);
        break;
      case 0xFF5AA5:
        Serial.println("Botão 6");
        sevenSegWrite(6);
        break;
      case 0xFF42BD:
        Serial.println("Botão 7");
        sevenSegWrite(7);
        break;
      case 0xFF4AB5:
        Serial.println("Botão 8");
        sevenSegWrite(8);
        break;
      case 0xFF52AD:
        Serial.println("Botão 9");
        sevenSegWrite(9);
        break;
    }
    key_value = resultados.value;
    irrecv.resume();
  }
}