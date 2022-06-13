# -ACYE-GRUPO2
<p style="text-align: justify;"><b>Universidad de San Carlos de Guatemala</b></p>
<p style="text-align: justify;"><b>Arquitectura de computadores y ensambladores 1</b></p>
<p style="text-align: justify;"><b>Ing. Otto Rene Escobar Leiva</b></p>
<p style="text-align: justify;"><b>Aux Frederick Jonathan Faugier Pinto</b></p>




      
| Carnet | Nombre | 
|:--------------|:-------------:|
| 201404341| Ocsael Neftalí Ramírez Castillo |
| 201710392| John Henry Lopez Mijangos |

  

#                               Manual Técnico Proyecto 1
  

  

## INTRODUCCIÓN
<p align="justify">La comunicación I2C es  una tecnología que nos permite comprender más a fondo la comunicación serial, comportándose esta con un mecanismo parecido a como una página web funciona con el Frontend y el Backend permitiendo dividir los trabajos en dos partes siendo estas: El arduino maestro y los arduinos esclavos, dando así un mayor alcance para la manipulación de bits e información de entrada y salida,
</p>
 <p align="justify">La memoria Eeprom de arduino nos permite el almacenamiento de bytes de forma no volátil , siendo estos un conjunto de 8 bits y cada uno la representación de un char o de dígitos, y siendo gracias a  la característica antes mencionada de no volatilidad, adquiere  suma importancia para el entendimiento del almacenaje de información y recuperación de datos  en el caso de apagones de energía, esta memoria posee una cantidad máxima de almacenamiento dependiendo del tipo del microcontrolador arduino usado siendo una de las cantidades más grandes 4 kilobytes. En esta práctica fue usada dicha memoria para el almacenamiento de cantidad de bolas de helado, siendo usada esta memoria para la validación de bolas y costos.. Además usamos un integrado para la conexión bluetooth de un teléfono a la computadora y otro para el control de la pantalla LCD con solo dos entradas a través del adaptador I2C, siendo este un expansor de entradas y salidas
 </p>
 
 ## Objetivos
 ### Objetivo General
 
* Que el estudiante adquiera conocimientos e interactúe con el microcontrolador Arduino, de manera que este sea capaz de construir un sistema complejo.

 ### Objetivos Específicos

* Comprender el funcionamiento de las entradas y salidas, tanto digitales como analógicas del microcontrolador
* Comprender el funcionamiento de dispositivos electromecánicos (Motores dc, stepper, servomotor)
* Utilizar sensores para la resolución de problemas
* Comprender el funcionamiento de la comunicación I2C

 ## Diagrama del Circuito:
 
![Descripción de la imagen](/imagenes/p1.jpeg)
 
 ## Diseño gráfico de la aplicación

![Descripción de la imagen](/imagenes/a1.jpeg)
 
 ## Explicación de Código:
 ### Motores: 
 
 <p align="justify">Se hizo uso de la librería #include <Stepper.h>, por la cual sirvió para dirigir al motor con driver por medio de 12 pasos en una vuelta.
 Stepper stepper(20, 8, 9, 10, 11); se inicializan los puertos a utilizar y la revolución que tendrá nuestro motor.
 </p>
  
  ```c++
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
  ```
Se valida que de 12 pasos continuos para que mueva el motor a 360 grados.
Se usa el método  stepper.step(1); para darle dirección al motor stepper por medio de la librería. asi mismo usando este el integrado L293D.
 Para el motor sin driver, se utiliza los pines del arduino y  conforme a una tabla de estados de medio paso se mueve el motor, repitiendo esto 3 veces para así dar un giro al motor.
 
 ```c++
		
void esperar(long unsigned tiempo_ms) {
  long unsigned tiempo_actual = millis();
  while (true) {
    if ((millis() - tiempo_actual) >= tiempo_ms) {
      break;
    }
  }
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
  ```
  
  
  
<p align="justify">Por medio del anterior método se recorre los estados del motor medio paso, para así repetirlo 3 veces seguidas en 10 minutos y generar el movimiento que simula la abertura de un portón
</p>
                        
![Descripción de la imagen](/imagenes/m1.jpeg)
  
![Descripción de la imagen](/imagenes/m2.jpeg)
                        
                                                  
 ### La pantalla LCD: 
  
La pantalla LCD se conectó por medio de la librería <LiquidCrystal_I2C.h>, para crear el objeto lcd se debe utilizar la dirección 0x27 o 0X3F (probar con cual funciona), e indicar el tamaño del LCD.
  ```c++
	LiquidCrystal_I2C lcd(0x27, 16, 2);	
  ```
  
  Se debe inicializar el LCD en el void setup()
  
  
  ```c++
		lcd.init();
  ```
  
En el void loop() se debe utilizar lcd.print() para imprimir los valores que queremos mostrar.
Las conexiones en proteus se muestran a continuación, el pin SCL y SDA deben conectarse al pin SCL y SDA del arduino Mega
![Descripción de la imagen](/imagenes/p1.jpeg)
 
  
  
 ### Ordenamiento de bolas de helado: 
  En este metodo se guarda la informacion en un arrat y despues se guarda en una nueva array ya ordenados, por medio del ordenamiento sort.
  
  ```c++
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
  ```  
  
  
  
   ### Mensaje Inicial: 
  En este metodo se ve la gestion e impresion del mensaje: Grupo2, Proyecto1, para que el usuario pueda ver la dinamica de la misma, esto fue elaborado por medio de la libreia I2C, usando LCD.pritn.
   ```c++
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
  lcd.setCursor(10, 0);
  lcd.write(byte(0));
  // Fila 2
  lcd.setCursor(1, 1);
  lcd.print("PROYECTO 1");
  // ESPERAR
  //esperar(10000);
  delay(5000);
}
  ``` 
  
  
   ### cinta: 
  En esta parte se declaran las variables de los 5 led, que representan a los helados, por medio del codigo asignado a cada helado, se valida cual va prender, ayudandose de un array de ordenamiento con los codigos, por medio de 2 motores se mueve la cinta.
   ```c++
if (bolas[i]==123) {
     motores();
     estadomotor=true;
    digitalWrite(led1, HIGH);
    delay(2000);
    digitalWrite(led1, LOW);
    }
    else if (bolas[i]==124) {
     motores();
     estadomotor=true;
    digitalWrite(led2, HIGH);
    delay(2000);
    digitalWrite(led2, LOW);
    }
    else if (bolas[i]==125) {
     motores();
     estadomotor=true;
    digitalWrite(led3, HIGH);
    delay(2000);
    digitalWrite(led3, LOW);
    }
  ``` 
  
   ### keypad: En esta parte se programa las teclas, cocatenando por un token los datos ingresados en el keypad, ayudandose de las iteracciones que nos demuestrtan en el keypad, al concatenar cada codigo ingresado, se valida si esta correcto o no.
  ```c++
		while (escuchar2) {
  char tecla = teclado.getKey();
    if (tecla) {
      if (tecla == '*') {
        //estado aceptacion 
          
          if(token=="123"||token=="124"||token=="125"||token=="126"||token=="127"){
           
            if(cantidad_limon==0 && token=="123"){
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("existencias");
                lcd.setCursor(0, 1);
                lcd.print("limon 0");
                token="";
                delay(1000);
            }
            else if(cantidad_vainilla==0 && token=="124"){
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("existencias");
                lcd.setCursor(0, 1);
                lcd.print("vainilla 0");
                token="";
                delay(1000);
            }
  ```  
  
  
   ### sensor ultrasonico: 
  Es este se usa un pin para medir el tiempo del potenciometro, usando una formula, donde se influye un factor: 0.004 y dando como resultado la distancia.
  ```c++
		digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    DURACION = pulseIn(ECO, HIGH);
    DISTANCIA = (DURACION * 0.034)/20;
  ```  
  
   ### sensor temperatura:
  Por medio de un pin que mide la cantidad de tiempo, se usa un factor para encontrar el numero de temperatura que se registra. 
  
  ```c++
		val=analogRead(A1);
       float mv=(val/1024.0)*5000;
       temperatura=mv/10;
  ```  
  
  ### EEPROM:
  Guardar datos:
  ```c++
		void guardar_eeprom() {
  /////////////////Guardar en memoria eeprom..............
EEPROM.put(0, cantidad_limon);
EEPROM.put(10, cantidad_vainilla);
EEPROM.put(20, cantidad_fresa);
EEPROM.put(30, cantidad_uva);
EEPROM.put(40, cantidad_napolitano);
EEPROM.put(50, costo);
}
  ```                                         
                                       
  Extraer datos:
  ```void extraer_eeprom() {
cantidad_limon=EEPROM.get(0,cantidad_limon);
cantidad_vainilla=EEPROM.get(10,cantidad_vainilla);
cantidad_fresa=EEPROM.get(20,cantidad_fresa);
cantidad_uva=EEPROM.get(30,cantidad_uva);
cantidad_napolitano=EEPROM.get(40,cantidad_napolitano);
costo=EEPROM.get(50,costo);
}
  ```                                       
  
  
 ### Explicacion Código Aplicación: 
  ### Conexión Bluetooth
  En el primer fragmento, lo que hace es listar todos los dispositivos bluetooth con los cuales se puede conectar la aplicación.
El segundo fragmento permite seleccionar un dispositivo del listado anterior, y si se pudo, entonces envía al arduino un caracter ‘a’, indicando se la conexión se estableció con éxito.
  foto de blu
  
   ### Recibir datos: 
Este se maneja con un reloj, el cual en la primera condición verifica si hay un dispositivo bluetooth está conectado actualmente; en la segunda condición valida que haya algo en el buffer, si lo hay ingresa a un conjunto de condiciones en la que, dependiendo de la ventana que se encuentre visible, ejecutará una determinada acción
  
   
  ```c++
		void conexion() {
char aux;
String cadena="";
  while (Serial.available()) {
    aux = Serial.read();
    
    if (aux=='R') {  // este es 123 limon
      cadena+=aux;
     Serial1.print("RR");
      //envio de datos en formato Cant1,cant2,cant3,cant4,cant5,Dinero,Temp 
      cadena1();
      Serial1.print(envio);
      Serial.print(envio);
  }else  if (aux=='A') {  // este es 123 limon
     
  
     delay(50);
      //envio de datos en formato Cant1,cant2,cant3,cant4,cant5,Dinero,Temp 
      
      
      long value2=cadena.toInt();
      delay(50);
      cantidad_limon=value2;
      aux=' ';
      cadena="";
      Serial1.println("nuevo");
      Serial1.println(cantidad_limon);
      cadena1();
      Serial.print(envio);
  }
    else if (aux=='B') {  // este es 124 VAINILLA
  ```  
![Descripción de la imagen](/imagenes/b1.jpeg)
![Descripción de la imagen](/imagenes/b2.jpeg)
## EQUIPO UTILIZADO
1. Dos motores stepper(uno con driver y otro sin driver)
2. Teclado alfanumérico matricial de 4x4 (en la aplicación).
3. Módulo Bluetooth.
4. Buzzer
5. Driver Max7219
6. Integrado Adaptador  I2C
  
  
  
### CONCLUSIONES:
   <p align="justify">La memoria Eeprom de arduino nos permite el almacenamiento de bytes de forma no volátil , siendo estos un conjunto de 8 bits y cada uno la representación de un char o de dígitos, y siendo gracias a  la característica antes mencionada de no volatilidad, adquiere  suma importancia para el entendimiento del almacenaje de información y recuperación de datos  en el caso de apagones de energía, esta memoria posee una cantidad máxima de almacenamiento dependiendo del tipo del microcontrolador arduino usado siendo una de las cantidades más grandes 4 kilobytes. En esta práctica fue usada dicha memoria para el almacenamiento de cantidad de bolas de helado, siendo usada esta memoria para la validación de bolas y costos.. Además usamos un integrado para la conexión bluetooth de un teléfono a la computadora y otro para el control de la pantalla LCD con solo dos entradas a través del adaptador I2C, siendo este un expansor de entradas y salidas
 </p>
  
  <p align="justify">Eeprom es una memoria de suma importancia para el almacenamiento de datos de entrada hacia el arduino, siendo esta una memoria de respaldo de confianza en caso se desconecte la energía.
 </p>
   <p align="justify">El Adaptador I2C permite la ocupación de menos pines para la graficación en la pantalla LCD, permitiendo la posibilidad de agregar más funciones extra que conectando la lcd directamente al microcontrolador arduino.
 </p>
   <p align="justify">La memoria Eeprom a pesar de que a simple vista pareciera una memoria rápida, a comparación de otras es opacada por gran medida en cuanto a velocidad como por ejemplo con memorias como la RAM.
 </p>











# -ACYE-GRUPO2
<p style="text-align: justify;"><b>Universidad de San Carlos de Guatemala</b></p>
<p style="text-align: justify;"><b>Arquitectura de computadores y ensambladores 1</b></p>
<p style="text-align: justify;"><b>Ing. Otto Rene Escobar Leiva</b></p>
<p style="text-align: justify;"><b>Aux Frederick Jonathan Faugier Pinto</b></p>




      
| Carnet | Nombre | 
|:--------------|:-------------:|
| 201404341| Ocsael Neftalí Ramírez Castillo |
| 201710392| John Henry Lopez Mijangos |

  

#                               Manual Usuario Proyecto 1
  

  

## INTRODUCCIÓN
<p align="justify">El presente manual, trata de que usted como usuario sepa como funciona la máquina de helado, teniendo en cuenta los tiempos de pandemia, es de mucha importancia para la comodidad de la gente y un servicio más personalizado y rápido.
</p>
 <p align="justify">Para la graficación del estado del programa se uso tanto la interfaz de la aplicación del celular como una pantalla LCD de 2 filas, siendo esta pantalla graficada gracias a Arduino y el adaptador de I2C a LCD.
</p>
 
 ## Flujo del Programa:
 
 ## Conexión:
 
Usted deberá descargar su aplicación móvil para poder entrar y hacer uso de nuestros servicios, deberá conectar su bluetooth para  poder conectarse a nuestro servicio.


![Descripción de la imagen](/imagenes/conexion.jpeg)


En esta parte usted puede solicitar y actualizar la cantidad de bolas de helado, asi como ver el costo de dinero y la temperatura que esta en el medio ambiente de la producción de helados.


![Descripción de la imagen](/imagenes/actualizar.jpeg)


En esta parte se puede seleccionar qué código de helado quiere adquirir de helado, en el sentido de actualizar la cantidad de helados, cuando se llegue agotar y hacer su respectivo mantenimiento. 


![Descripción de la imagen](/imagenes/elegir.jpeg)


![Descripción de la imagen](/imagenes/meter.jpeg)


 
  ## maquina de helados:
 
 ![Descripción de la imagen](/imagenes/g1.jpeg)
 
 
 
   ### keypad:
   Aparecerá por 5 segundos un mensaje en la pantall LCD que contendrá en su primera fila dos caracteres semejantes a candados y la leyenda de “bienvenida”, y en la segunda fila “Grupo2 proyecto1”:
   
   Este mecanismo, usted puede elegir qué códigos de helado quiere, que sabores, pero en primera instancia elegir si quiere uno, dos y tres, bolas, con categorías.
   
| Tamaño de vaso | No. Bolas de helado | 
|:--------------|:-------------:|
| Pequeño | 1 |
| Mediano| 2 |
| Grande| 3 |
 
 
 Por medio del keypad, usted puede aplicar y elegir el helado que desea, media vez este disponible, si no existe el código, le mostrará un mensaje que no existe el helado, si usted coloca un helado incorrecto, le mostrará que no existe el helado. Los siguientes helados son los disponibles.
 
 | No.| helado | 
|:--------------|:-------------:|
| 123 | limon |
| 124| vainilla |
| 125| fresa |
| 126| uva |
| 127| napolitano |



 ![Descripción de la imagen](/imagenes/h1.jpeg)
 
 
 
 ![Descripción de la imagen](/imagenes/h1.jpeg)
 

   ## Temperatura:
 Por medio de los botones, usted puede ver y mover la temperatura, del almacén donde esta el área de producción, esta temperatura llega a la aplicación. 
  
  
  ![Descripción de la imagen](/imagenes/t1.jpeg)
 
   ## retirar vaso:
   
   Por medio del sensor se verifica cuando el vaso ha llegado a la posición final, que activara una alarma, o puede también quitar su vaso ya servido de helados y el sensor automáticamente lo va reconocer que ya se retiro.
   
 
 
 ![Descripción de la imagen](/imagenes/g1.jpeg)
 
 
 
 
