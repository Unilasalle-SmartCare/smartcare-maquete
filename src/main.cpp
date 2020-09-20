#include <Arduino.h>

// --- ULTRASSÔNICO ---
#include <Ultrasonic.h>
#include <PubSubClient.h>
#include <string.h>
#include <Ethernet.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192, 168, 0, 105);
IPAddress server(192, 168, 0, 74);

void verificaIdosoDeitado();
void  verificaUltrasonico();
void  verificaPresenca();

#define pinoPIRQuarto 7 //Pino ligado ao sensor PIR do quarto
int statusPIRQuarto; //Variavel para guardar valor do sensor do quarto

#define pinoTriggerQuarto 4
#define pinoEchoQuarto 5
Ultrasonic ultrasonic(pinoTriggerQuarto, pinoEchoQuarto);
int distance;

#define pinoButtonQuarto  9 //PINO DIGITAL UTILIZADO PELO BOTAO
#define pinoLedVermelho  8 //PINO DIGITAL UTILIZADO PELO LED
#define pinoLedAmarelo  3 //PINO DIGITAL UTILIZADO PELO LED
#define pinoLedQuarto  12 //PINO DIGITAL UTILIZADO PELO LED


void setup() {
  Serial.begin(9600);

  pinMode(pinoPIRQuarto, INPUT); //Define pino do sensor de presença como entrada  
  pinMode(pinoButtonQuarto, INPUT);
  pinMode(pinoLedQuarto, OUTPUT); //DEFINE O PINO do led COMO SAÍDA
  pinMode(pinoLedVermelho, OUTPUT); //DEFINE O PINO do led COMO SAÍDA
  pinMode(pinoLedAmarelo, OUTPUT); //DEFINE O PINO do led COMO SAÍDA  
  
}

void loop() { 
  verificaIdosoDeitado();
  verificaUltrasonico();
  verificaPresenca();
}

void verificaUltrasonico() {  
  float distancia = ultrasonic.distanceRead(CM); 
  Serial.println(distancia);

  if (distancia < 20)
  {
    digitalWrite(pinoLedAmarelo, HIGH);
  } else {
    digitalWrite(pinoLedAmarelo, LOW);
  }  
}

void verificaIdosoDeitado(){
  int sensorVal = digitalRead(pinoButtonQuarto);  
  if (sensorVal == HIGH) {
    digitalWrite(pinoLedVermelho, LOW);
    Serial.println("O idoso esta deitado");
  } else {
    digitalWrite(pinoLedVermelho, HIGH);
    Serial.println("O idoso nao esta deitado");
  }
}

void verificaPresenca(){
  int sensorVal = digitalRead(pinoPIRQuarto);  
  if (sensorVal == HIGH) {
    digitalWrite(pinoLedQuarto, HIGH);
    //Serial.println("Tem alguem no quarto");
  } else {
    digitalWrite(pinoLedQuarto, LOW);
    //Serial.println("O quarto esta vazio");
  }
}
