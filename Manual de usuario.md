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
 
 
 
 
