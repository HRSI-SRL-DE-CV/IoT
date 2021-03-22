/////////////////////////////////////////////////////////////////////////////
/*
 * Author: HRSI IoT
 * Prácitca 1 encendiendo un led en el ESP32
 */
/////////////////////////////////////////////////////////////////////////////

int pin_led = 15; //Incializamos nuestro puerto de propósito general GPIO15(D15) 

void setup() //Sección de configuraciones
{      pinMode(pin_led, OUTPUT); //Configuración de nuestro puerto como salida
}

void loop() //Secuencia del programa basado en la configuración
{  digitalWrite(pin_led, HIGH);  //Enviar un valor lógico alto a la salida para activar el led
   delay(1000);  //Generar un retardo de 1 segundo para enviar un valor lógico bajo
   digitalWrite (pin_led, LOW); //Enviar un vlor lógico bajo para apagar el led
   delay(2000);  //Retardo de 2 segundos
}
