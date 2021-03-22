/////////////////////////////////////////////////////////////////////////////
/*
 * Author: HRSI IoT
 * Práctica 2 Identificando redes WiFi ESP32
 */
/////////////////////////////////////////////////////////////////////////////
#include "WiFi.h" //Agregando librería para WiFi

void setup()
{
    Serial.begin(115200); //Configuración para ver la velocidad de carga y visualización en el visor serial
    WiFi.mode(WIFI_STA); //Inicialización del módulo WiFi
    WiFi.disconnect();
    delay(100);
    Serial.println("Configuración realizada exitosamente!!!!");
}

void loop()
{
    Serial.println("Verificación de redes inalámbricas WiFi");
    int i = WiFi.scanNetworks(); //Contador para identificar cuantas redes se detectaron mediante el método scanNetowrks
    Serial.println("Escaneo completado");
    if (i == 0) {
        Serial.println("No se detectaron redes inalámbricas");
    } else {
        Serial.print(i);
        Serial.println(" redes inalámbricas se detectaron");
        for (int m = 0; m < i; ++m) { //Iterar en las redes encontradas
            Serial.print(m + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(m));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(m));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(5000);
        }
    }
    Serial.println("");
    delay(5000);
}
