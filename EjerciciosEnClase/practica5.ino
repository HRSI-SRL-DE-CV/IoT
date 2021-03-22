/*******************************************************************************
 HRSI .- IoT
 Práctica 5 - Leyendo datos de sensor de temperatura y húmedad en pantalla oled
 Autor: HRSI IoT
 Nota: La pantalla oled utilizada en la práctica se le conoce en mercadolibre
 como pantalla oled 7 pines, por lo que por default trabajará con el protocolo
 SPI, es por eso que en el desarrollo de la práctica se utiliza ese protocolo,
 para cambiar a I2C visita el siguiente sitio:
 *******************************************************************************/

#include <SPI.h> //Protocolo utilizado para comunicar pantalla oled
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

#define SCREEN_WIDTH 128 // Inicializar ancho de pantalla oled en pixeles
#define SCREEN_HEIGHT 64 // Inicializar largo de pantalla oled en pixeles
#define DHTPIN 4     // inicializar Pin para sensor DHT11
#define DHTTYPE DHT11 // Inicializar sensor DHT11
DHT dht(DHTPIN, DHTTYPE); //crear variable para pin y funcionalidad de sensor

// Declaración de pines de la librería SSD1306 utilizando el protocolo SPI (configuración por default)
#define OLED_MOSI  21 //MOSI ó D1
#define OLED_CLK   18 //SCL ó D0
#define OLED_DC    19 //MISO ó DC
#define OLED_CS    23 //CS
#define OLED_RESET 22 //RES
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 }; 

void setup() {
  Serial.println("Práctica 4 - HRSI - IoT");
  Serial.println(F("Midiendo Temperatura y Húmedad")); 
  dht.begin();
  Serial.begin(9600);

  //Generar voltaje para display SSD1306 de 3.3 volts para alimentar el LCD
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // No proceder en caso de fallo
  }

  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,10);
  //Display Static Text
  display.println("HRSI - IoT");
  display.println(" ");
  display.println("    :-)   ");
  display.display();
}

void loop() {
  
  /////DHT 11 lectura de sensor//////////
  // Recuerda que el sensor toma la lectura cada 250 milisegundos
  // Es un sensor algo lento por lo que si pretendes velocidades de lectura más rápida busca otro sensor que cumpla con esas características
  float h = dht.readHumidity(); //asignar la variable para lectura de húmedad
  float t = dht.readTemperature(); //asignar la variable para lectura de temperatura en grados centígrados
  float f = dht.readTemperature(true); //asignar variable para la lectura de temperatura en grados farenheit

  // Revisar si algunas de las lecturas fallaron
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("No se logró conseguir la lectura del sensor!"));
    return;
  }

  //Indices de calor en grados centígrados y farenheit
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humedad: "));
  Serial.print(h);
  Serial.print(F("%  Temperatura: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Indice de calor: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  display.display();
  delay(2000); // Pause for 2 seconds

  //Limpiar Buffer de pantalla
  display.clearDisplay();

  display.setTextSize(2); //Tamaño de texto
  display.setTextColor(WHITE); //Configuración de color de texto
  display.setCursor(0,10); //Coordenada de escritura inicial
  //Display Static Text
  display.print("T: "); //Agregar lectura
  display.print(t); // de temperatura en grados centígrados
  display.setTextSize(1);
  display.print((char)247);
  display.setTextSize(2);
  display.println(" "); 
  display.print("H: "); //Agregar lectura
  display.print(h); //de húmedad
  display.print("%"); //como porcentaje relativo
  display.display();
  
}
