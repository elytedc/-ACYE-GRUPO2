//#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <LedControl.h>
#include <Stepper.h>


// MATRIZ
LedControl lc = LedControl(51, 52, 53, 1);

int TRIG = 30;
int ECO = 31;
int DURACION;
int DISTANCIA;


int bolas[3];
// BUZZER
int buzzer = 40;
int conteo=0;
bool estadomotor=true;
bool estadocinta=true;
// MOTOR SIN DRIVER
int pin1 = 4;
int pin2 = 5;
int pin3 = 6;
int pin4 = 7;
int tiempo = 40;
int contador_motor = 1;
int conaux = 0;
bool estado_motor = false;

// MOTOR CON DRIVER
int direccion = 1;
int led1 = 12;
int led2 = 13;
int led3 = 14;
int led4 = 15;
int led5 = 16;
Stepper stepper(100, 8, 9, 10, 11);



void setup() {
  Serial.begin(9600);
  // BUZZER
  pinMode(buzzer, OUTPUT);

  // sin driver
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  /// con driver
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  bolas[0] = 127;
  bolas[1] = 124;
  bolas[2] = 126;
 pinMode(TRIG, OUTPUT);
  pinMode(ECO, INPUT);   
}

void loop() {
    
    
 if (estadocinta==true) {
  // ordenamiento-          bubble sort
  ordenamiento(bolas, 3);
  cinta();
  limpiarmatriz();
 }

}


void limpiarmatriz() {
  for(int i=0; i<3; i++){
    bolas[i]=0;
  }
}

void cinta(){
    for(int i=0; i<3; i++){

digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    DURACION = pulseIn(ECO, HIGH);
    DISTANCIA = (DURACION * 0.034) / 2;
    Serial.print(DISTANCIA);
    
      
    if (bolas[i]==123) {
     motores();
     estadomotor=true;
    digitalWrite(led1, HIGH);
    delay(5000);
    digitalWrite(led1, LOW);
    }
    else if (bolas[i]==124) {
     motores();
     estadomotor=true;
    digitalWrite(led2, HIGH);
    delay(5000);
    digitalWrite(led2, LOW);
    }

    else if (bolas[i]==125) {
     motores();
     estadomotor=true;
    digitalWrite(led3, HIGH);
    delay(5000);
    digitalWrite(led3, LOW);
    }

    else if (bolas[i]==126) {
     motores();
     estadomotor=true;
    digitalWrite(led4, HIGH);
    delay(5000);
    digitalWrite(led4, LOW);
    }

    else if (bolas[i]==127) {
     motores();
     estadomotor=true;
    digitalWrite(led5, HIGH);
    delay(5000);
    digitalWrite(led5, LOW);
    }




  }
  motores(); 
  estadomotor=true;
  estadocinta=false;
}



void ordenamiento(int* values, int length)
{
   int i, j, flag = 1;
   int temp;
   for (i = 1; (i <= length) && flag; i++)
   {
      flag = 0;
      for (j = 0; j < (length - 1); j++)
      {
         if (values[j + 1] < values[j])
         {
            temp = values[j];
            values[j] = values[j + 1];
            values[j + 1] = temp;
            flag = 1;
         }
      }
   }
}





void motores(){
  acc();
  for (int i = 0; i <= 2; i++) {
  if (estadomotor==true) {
  con_driver();
    digitalWrite(pin1, HIGH);
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, HIGH);
    digitalWrite(pin4, LOW);
  delay(tiempo);

con_driver();
  digitalWrite(pin1, HIGH);
     digitalWrite(pin2, LOW);
      digitalWrite(pin3, LOW);
     digitalWrite(pin4, HIGH);
     delay(tiempo);

con_driver();
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, LOW);
      digitalWrite(pin4, HIGH);
      delay(tiempo);

con_driver();
      digitalWrite(pin1, LOW);
      digitalWrite(pin2, HIGH);
      digitalWrite(pin3, HIGH);
      digitalWrite(pin4, LOW);
      delay(tiempo);
  
}
}
estadomotor=false;
stopMotor();
}




void sonarAlarma(long unsigned tiempo_ms) {
  digitalWrite(buzzer, HIGH);
  delay(2000);
  digitalWrite(buzzer, LOW);
}

void acc() {
  stepper.setSpeed(3);
}



void con_driver()
{ direccion = 1;
  stepper.step(1);
}



void stopMotor() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}

//void sin_driver() {
// // for (int i = 0; i <= 0; i++) {
//    retroceso();
//    conteo=0;
// // }
//  //stopMotor();
//
//}

void iniciar() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);

  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);


  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, HIGH);

  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, LOW);
}


//void retroceso() {
//  unsigned long ti = millis();
// if (conteo==1) {
//
//  conaux++;
//  while (true) {
//    if (millis() - ti >= tiempo) {
//      digitalWrite(pin1, HIGH);
//      digitalWrite(pin2, LOW);
//      digitalWrite(pin3, HIGH);
//      digitalWrite(pin4, LOW);
//      //delay(tiempo);
//      break;
//    }
//  }
//
//}
//
//if (conteo==2) {
//ti = millis();
//  while (true) {
//    if (millis() - ti >= tiempo) {
//      digitalWrite(pin1, HIGH);
//      digitalWrite(pin2, LOW);
//      digitalWrite(pin3, LOW);
//      digitalWrite(pin4, HIGH);
//      //delay(tiempo);
//      break;
//    }
//  }
//  
//}
//
//
//if (conteo==3) {
//  ti = millis();
//  while (true) {
//    if (millis() - ti >= tiempo) {
//      digitalWrite(pin1, LOW);
//      digitalWrite(pin2, HIGH);
//      digitalWrite(pin3, LOW);
//      digitalWrite(pin4, HIGH);
//      delay(tiempo);
//      break;
//    }
//  }
//  
//}
//
//}




//
//void retroceso() {
//  unsigned long ti = millis();
//  conaux++;
//  while (true) {
//    if (millis() - ti >= tiempo) {
//      digitalWrite(pin1, HIGH);
//      digitalWrite(pin2, LOW);
//      digitalWrite(pin3, HIGH);
//      digitalWrite(pin4, LOW);
//      //delay(tiempo);
//      break;
//    }
//  }
//  ti = millis();
//  while (true) {
//    if (millis() - ti >= tiempo) {
//      digitalWrite(pin1, HIGH);
//      digitalWrite(pin2, LOW);
//      digitalWrite(pin3, LOW);
//      digitalWrite(pin4, HIGH);
//      //delay(tiempo);
//      break;
//    }
//  }
//
//  //if(conaux>=3){
//
//  //}
//  ti = millis();
//  while (true) {
//    if (millis() - ti >= tiempo) {


//      digitalWrite(pin1, LOW);
//      digitalWrite(pin2, HIGH);
//      digitalWrite(pin3, LOW);
//      digitalWrite(pin4, HIGH);
//      delay(tiempo);
//      break;
//    }
//  }
//
//  //if(conaux<3){
//  ti = millis();
//  while (true) {
//    if (millis() - ti >= tiempo) {
//      digitalWrite(pin1, LOW);
//      digitalWrite(pin2, HIGH);
//      digitalWrite(pin3, HIGH);
//      digitalWrite(pin4, LOW);
//      //delay(tiempo);
//      break;
//    }
//  }
//
//  //}
//  if (conaux >= 3) {
//    conaux = 0;
//    delay(50);
//    stopMotor();
//  }
//}
