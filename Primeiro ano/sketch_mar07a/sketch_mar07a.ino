#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serial1(10, 11); // RX, TX
TinyGPS gps1;

  float latPadrao1 = -21.761480;
  float longPadrao1 = -41.291248;

  float latPadrao2 = -21.762023;
  float longPadrao2 = -41.290881;

  float latPadrao3 = -21.762785;
  float longPadrao3 = -41.290492;

  float latEscolhida = 0;
  float longEscolhida = 0;

void setup() {
   serial1.begin(9600);
   Serial.begin(9600);

  pinMode (7, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, INPUT);
   Serial.println("Módulo GPS buscando sinal dos satelites...");
}

void loop() {
  int cont = 0;

  int buttonState;

  digitalWrite (5, HIGH);

  digitalWrite (6, LOW);
  
  bool recebido = false;

  while (serial1.available()) {
     char cIn = serial1.read();
     recebido = gps1.encode(cIn);
  }

  if (recebido) {
     Serial.println("----------------------------------------");
  while (cont <= 3) {
    buttonState = digitalRead(4);
    if (buttonState == HIGH) {
      cont++;
    }
      while (cont == 1) {
        
        latEscolhida = latPadrao1;
        longEscolhida = longPadrao1;
        digitalWrite (6, HIGH);
        tone(6, 2000, 10);
        delay (2000);
        digitalWrite (6, LOW);
        Serial.println("Cordenada 1");
            Serial.println("----------------------------------------");
            //Latitude e Longitude
            long latitude, longitude;
            unsigned long idadeInfo;
            gps1.get_position(&latitude, &longitude, &idadeInfo);     

             if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
                Serial.print("Latitude: ");
                Serial.println(float(latitude) / 100000, 6);
             }

             if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
                  Serial.print("Longitude: ");
                  Serial.println(float(longitude) / 100000, 6);
             }
        buttonState = digitalRead(4);
        if (buttonState == HIGH) {
      cont++;
      }
      } while (cont == 2) {
        
        latEscolhida = latPadrao2;
        longEscolhida = longPadrao2;
        digitalWrite (6, HIGH);
        tone(6, 2000, 10);
        delay (500);
        digitalWrite (6, LOW);
        digitalWrite (6, HIGH);
        tone(6, 2000, 10);
        delay (500);
        digitalWrite (6, LOW);
        delay(2000);
        Serial.println("Cordenadas 2");
        if (recebido) {
      Serial.println("----------------------------------------");
     
     //Latitude e Longitude
     long latitude, longitude;
     unsigned long idadeInfo;
     gps1.get_position(&latitude, &longitude, &idadeInfo);     

     if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 6);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }
        }
        buttonState = digitalRead(4);
        if (buttonState == HIGH) {
      cont++;
    }
      } while (cont == 3) {
        
        latEscolhida = latPadrao3;
        longEscolhida = longPadrao3;
        digitalWrite (6, HIGH);
        tone(6, 2000, 10);
        delay (500);
        digitalWrite (6, LOW);
        digitalWrite (6, HIGH);
        tone(6, 2000, 10);
        delay (500);
        digitalWrite (6, LOW);
        digitalWrite (6, HIGH);
        tone(6, 2000, 10);
        delay (500);
        digitalWrite (6, LOW);
        delay(2000);
        Serial.println("Cordenadas 3");
     Serial.println("----------------------------------------");
     
     //Latitude e Longitude
     long latitude, longitude;
     unsigned long idadeInfo;
     gps1.get_position(&latitude, &longitude, &idadeInfo);     

     if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Latitude: ");
        Serial.println(float(latitude) / 100000, 6);
     }

     if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
        Serial.print("Longitude: ");
        Serial.println(float(longitude) / 100000, 6);
     }
     buttonState = digitalRead(4);
     if (buttonState == HIGH) {
      cont++;
    }
      }
      }
    }
  }
     float sentido_para;
//     sentido_para = gps1.course_to(latitude, longitude, latEscolhida, longEscolhida);
  
