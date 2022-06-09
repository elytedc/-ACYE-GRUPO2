#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <LedControl.h>
#include <Stepper.h>
#include <Keypad.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


// MATRIZ
LedControl lc = LedControl(51, 52, 53, 1);

int TRIG = 30;
int ECO = 31;
int DURACION;
int DISTANCIA;
// variables EEPROM..............
int cantidad_limon=0;
int cantidad_vainilla=0;
int cantidad_fresa=0;
int cantidad_uva=0;
int cantidad_napolitano=0;
float costo=0;


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

//TECLADO

const byte FILAS = 4;     // Filas
const byte COLUMNAS = 4;  // Columnas
int estadoIngre = 0;
// Matriz de las teclas
char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}
};
// Asignación de las teclas a los pines de arduino
byte filaPines[FILAS] = { 41, 42, 43, 44};
byte columnaPines[COLUMNAS] = {23, 24, 25, 26};
Keypad teclado = Keypad(makeKeymap(teclas), filaPines, columnaPines, FILAS, COLUMNAS);

void setup() {

  Serial.begin(9600);
  // BUZZER
  pinMode(buzzer, OUTPUT);
lcd.init();

 lc.shutdown(0, false); //inicia apagado - dispositivo 1
  lc.setIntensity(0, 15);
  lc.clearDisplay(0);
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
//Serial.print("valor gua");
//Serial.println(EEPROM.read(0));
//Serial.print("leer");
//EEPROM.write(0,45);

/////////////////Guardar en memoria eeprom..............
//EEPROM.put(0, cantidad_limon);
//EEPROM.put(10, cantidad_vainilla);
//EEPROM.put(20, cantidad_fresa);
//EEPROM.put(30, cantidad_uva);
//EEPROM.put(40, cantidad_napolitano);
//EEPROM.put(50, costo);

extraer_eeprom();

Serial.println(cantidad_limon);
Serial.println(cantidad_vainilla);
Serial.println(cantidad_fresa);
Serial.println(cantidad_uva);
Serial.println(cantidad_napolitano);
Serial.println(costo);
mensajeInicial();
//Serial.println(EEPROM.get(0,cantidad_limon));
//Serial.print("vainilla:");
//Serial.println(EEPROM.get(10,cantidad_vainilla));
//Serial.print("fresa:");
//Serial.println(EEPROM.get(20,cantidad_fresa));
//Serial.print("uva:");
//Serial.println(EEPROM.get(30,cantidad_uva));
//Serial.print("napolitano:");
//Serial.println(EEPROM.get(40,cantidad_napolitano));
//Serial.print("costo:");
//Serial.println(EEPROM.get(50,costo));


  
}

void loop() {
    ingresoTeclado();
    //estadocinta=true;
    //guardar_eeprom();
    //extraer_eeprom()
 if (estadocinta==true) {
  // ordenamiento-          bubble sort
  ordenamiento(bolas, 3);
  cinta();
  limpiarmatriz();
  

 }
 
}


void mensajeInicial() {
  byte candado[] = {
    B00000,
    B01110,
    B10001,
    B10001,
    B11111,
    B11011,
    B11111,
    B11111
  };
  // MENSAJE INICIAL
  lcd.clear();
  // Fila 1
  lcd.createChar(0, candado);
  lcd.setCursor(2, 0);
  lcd.write(byte(0));
  lcd.setCursor(3, 0);
  lcd.print("GRUPO 2");
  lcd.setCursor(13, 0);
  lcd.write(byte(0));
  // Fila 2
  lcd.setCursor(1, 1);
  lcd.print("PROYECTO 1");
  // ESPERAR
  //esperar(10000);
  delay(5000);
}


void ingresoTeclado(){
bool escuchar = true;
lcd.clear();//limpiamos la lcd p
lcd.setCursor(0,0);//seteamos el cursos en la linea 0 
lcd.print("Ingrese algun Valor");
lcd.setCursor(0,1);//seteamos el cursor en la linea 1
  while (escuchar) {
  char tecla = teclado.getKey();
    if (tecla) {
      if (tecla == '*') {
        //estado aceptacion 
         lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Ingreso");
          lcd.setCursor(0, 1);
          lcd.print("Correctamente");
          
          escuchar = false;
        }
       else if (tecla == '#') {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Ingreso");
        lcd.setCursor(0, 1);
        lcd.print("Cancelado");
       
        escuchar = false;
      }
      else {
        //tokenIngresado += tecla;
        lcd.print(tecla);
      }
    }


  }
  
}

void guardar_eeprom() {
  /////////////////Guardar en memoria eeprom..............
EEPROM.put(0, cantidad_limon);
EEPROM.put(10, cantidad_vainilla);
EEPROM.put(20, cantidad_fresa);
EEPROM.put(30, cantidad_uva);
EEPROM.put(40, cantidad_napolitano);
EEPROM.put(50, costo);
}


void extraer_eeprom() {
cantidad_limon=EEPROM.get(0,cantidad_limon);
cantidad_vainilla=EEPROM.get(10,cantidad_vainilla);
cantidad_fresa=EEPROM.get(20,cantidad_fresa);
cantidad_uva=EEPROM.get(30,cantidad_uva);
cantidad_napolitano=EEPROM.get(40,cantidad_napolitano);
costo=EEPROM.get(50,costo);
}

void limpiarmatriz() {
  for(int i=0; i<3; i++){
    bolas[i]=0;
  }
}

void cinta(){
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    DURACION = pulseIn(ECO, HIGH);
    DISTANCIA = (DURACION * 0.034)/20;
    
    for(int i=0; i<3; i++){
    //Serial.println(DURACION);
    //Serial.println(DISTANCIA);
    
      
    if (bolas[i]==123) {
     motores();
     estadomotor=true;
    digitalWrite(led1, HIGH);
    delay(3000);
    digitalWrite(led1, LOW);
    }
    else if (bolas[i]==124) {
     motores();
     estadomotor=true;
    digitalWrite(led2, HIGH);
    delay(3000);
    digitalWrite(led2, LOW);
    }

    else if (bolas[i]==125) {
     motores();
     estadomotor=true;
    digitalWrite(led3, HIGH);
    delay(3000);
    digitalWrite(led3, LOW);
    }

    else if (bolas[i]==126) {
     motores();
     estadomotor=true;
    digitalWrite(led4, HIGH);
    delay(3000);
    digitalWrite(led4, LOW);
    }

    else if (bolas[i]==127) {
     motores();
     estadomotor=true;
    digitalWrite(led5, HIGH);
    delay(3000);
    digitalWrite(led5, LOW);
    }




  }
  motores();
  estadomotor=true;
  estadocinta=false;
  sonarAlarma();
   while (DISTANCIA <= 25) { 
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    DURACION = pulseIn(ECO, HIGH);
    DISTANCIA = (DURACION * 0.034)/20;
    
      }
  Serial.print("retirado");
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




void sonarAlarma() {
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

void esperar(long unsigned tiempo_ms) {
  long unsigned tiempo_actual = millis();
  while (true) {
    if ((millis() - tiempo_actual) >= tiempo_ms) {
      break;
    }
  }
}
