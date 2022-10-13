#include <RunningMedian.h>

//motores en m1 y m4
// sensores de piso blanco es cero y negro es 1
//#include "RunningMedian.h"  //libreria para calculo de mediana estadistica
#include <AFMotor.h>
#include <NewPing.h>

NewPing sonar_izq(14, 15, 40);  //14 trigger 15echo
NewPing sonar_der(16, 17, 40);  //16trigger 17echo
RunningMedian us_izquierda = RunningMedian(3);
RunningMedian us_derecha = RunningMedian(3);
AF_DCMotor motord(1);  // create motor #1, 64KHz pwm
AF_DCMotor motori(4);  // create motor #4, 64KHz
//Declaracion de pines para sensores
int IrIzq = 19;
int IrDer = 18;
//Declaracion de variables para leer los valores de los sensores
int Sirizq = 0;
int Sirder = 0;
int UsIzq = 0;
int UsDer = 0;
//Declaracion de pines para los motores

void setup() {
  pinMode(IrIzq, INPUT);
  pinMode(IrDer, INPUT);
  motord.setSpeed(200);  // set the speed to 200/255
  motori.setSpeed(200);  // set the speed to 200/255
  delay(5000);           // Tiempo de Seguriadad
}

void loop() {
  sensores();

  if ((UsDer > UsIzq) && (UsIzq != 0)) {
    //derechasuave();
    //izquierdasuave();
    izquierdafuerte();
    
  }
  if ((UsDer < UsIzq) && (UsDer != 0)) {
    //izquierdasuave();
    //derechasuave();
    derechafuerte();
  }
  if ((UsDer != 0) && (UsIzq == 0)) {
    //izquierdasuave();
    //derechasuave();
    derechafuerte();
  }
  if ((UsDer == 0) && (UsIzq != 0)) {
    //derechasuave();
    //izquierdasuave();
    izquierdafuerte();
  }
  if ((UsDer == 0) && (UsIzq == 0)) {
    adelante();
    //atras();
  }
  if ((Sirder == 1) || (Sirizq == 1)) {
    atras();  //el tiempo del delay depende de que tan rapido sea tu robot
    delay(300);
    derechafuerte();
    delay(1000);
  }
}

// Lectura de Sensores
void sensores() {

  UsIzq = sonar_izq.ping_cm();
  delay(40);
  us_izquierda.add(UsIzq);
  UsIzq = us_izquierda.getMedian();
  UsDer = sonar_der.ping_cm();
  delay(40);
  us_derecha.add(UsDer);
  UsDer = us_derecha.getMedian();
  Sirizq = digitalRead(IrIzq);
  delay(1);
  Sirder = digitalRead(IrDer);
  delay(1);
}

void adelante() {
  motord.run(FORWARD);  // turn it on going forward
  motori.run(FORWARD);  // turn it on going forward
}
void atras() {
  motord.run(BACKWARD);  // turn it on going forward
  motori.run(BACKWARD);  // turn it on going forward
}
void parar() {
  motord.run(RELEASE);  // turn it on going forward
  motori.run(RELEASE);  // turn it on going forward
}
void derechasuave() {
  motord.run(FORWARD);  // turn it on going forward
  motori.run(RELEASE);  // turn it on going forward
}
void derechafuerte() {
  motord.run(FORWARD);   // turn it on going forward
  motori.run(BACKWARD);  // turn it on going forward
}
void izquierdasuave() {
  motord.run(RELEASE);  // turn it on going forward
  motori.run(FORWARD);  // turn it on going forward
}
void izquierdafuerte() {
  motord.run(BACKWARD);  // turn it on going forward
  motori.run(FORWARD);   // turn it on going forward
}
