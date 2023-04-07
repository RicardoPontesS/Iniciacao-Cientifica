#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serial1(10, 11); // RX, TX
TinyGPS gps1;

void setup() {
  serial1.begin(9600);
  Serial.begin(9600);

  Serial.println("GPS buscando o sinal dos satelites...");
  pinMode (7, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, INPUT);

}

void loop() {
  float latPadrao1 = -21.761480;
  float longPadrao1 = -41.291248;

  float latPadrao2 = -21.762023;
  float longPadrao2 = -41.290881;

  float latPadrao3 = -21.762785;
  float longPadrao3 = -41.290492;

  float latEscolhida = 0;
  float longEscolhida = 0;

  int cont = 0;

  int buttonState;

  digitalWrite (5, HIGH);

  digitalWrite (6, LOW);

  bool recebido = false;

  while (serial1.available()) {
    char cIn = serial1.read();
    recebido = gps1.encode(cIn);
  }

  while (cont <= 3) {
    buttonState = digitalRead(4);
    if (buttonState == HIGH) {
      cont++;
      if (cont == 1) {
        latEscolhida = latPadrao1;
        longEscolhida = longPadrao1;
        digitalWrite (6, HIGH);
        tone(6, 2000, 10);
        delay (2000);
        digitalWrite (6, LOW);
        Serial.println("Cordenadas 1");
        dados();
      } else if (cont == 2) {
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
        dados();
      } else if (cont == 3) {
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
        dados();
      }
    }

  }

  void dados() {
    if (recebido) {
      Serial.println("----------------------------------------");
      digitalWrite (7, HIGH);

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

      if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
        Serial.print("Idade da Informacao (ms): ");
        Serial.println(idadeInfo);
      }

      float sentido_para;
      sentido_para = gps1.course_to(latitude, longitude, latEscolhida, longEscolhida);
      Serial.print("Sentido para a localização desejada: ");
      Serial.println(sentido_para);

      if (sentido_para != 0) {
        digitalWrite (6, HIGH);
        tone(6, 2000, 10);
        delay (100);
        digitalWrite (6, LOW);
      }


      //sentito (em centesima de graus)
      unsigned long sentido;
      sentido = gps1.course();

      Serial.print("Sentido (grau): ");
      Serial.println(float(sentido) / 100, 2);


      //satelites e precisão
      unsigned short satelites;
      unsigned long precisao;
      satelites = gps1.satellites();
      precisao =  gps1.hdop();

      if (satelites != TinyGPS::GPS_INVALID_SATELLITES) {
        Serial.print("Satelites: ");
        Serial.println(satelites);
      }

      if (precisao != TinyGPS::GPS_INVALID_HDOP) {
        Serial.print("Precisao (centesimos de segundo): ");
        Serial.println(precisao);
      }


      //float distancia_entre;
      //distancia_entre = gps1.distance_between(lat1, long1, lat2, long2);

    }
    digitalWrite(7, LOW);
  }
}
