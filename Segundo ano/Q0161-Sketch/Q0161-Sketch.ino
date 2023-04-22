#include <SoftwareSerial.h>
#include <TinyGPS.h>                                                                                                                              

SoftwareSerial serial1(10, 11); // RX, TX
SoftwareSerial serialGSM(9, 8); // RX, T

TinyGPS gps1;

  void enviaSMS(String telefone, String mensagem);
  void configuraGSM();
  String telefoneSMS;
  String mensagemSMS;
  long latitude, longitude;
  unsigned long idadeInfo;
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
  pinMode(3, OUTPUT);
   Serial.println("Módulo GPS buscando sinal dos satelites...");
}

void loop() {
  int cont = 0;

  int buttonState;
  digitalWrite (5, HIGH);
  digitalWrite (3, HIGH);
  digitalWrite (6, LOW);
  
  bool recebido = false;

  while (serial1.available()) {
     char cIn = serial1.read();
     recebido = gps1.encode(cIn);
  }
  buttonState = digitalRead(4);
 
  if(buttonState == HIGH) {
      enviaSMS("992558278", "olá");
    }
  if (recebido) {
    
     Serial.println("----------------------------------------");
     digitalWrite (7, HIGH);
          while (cont <= 3) {
              buttonState = digitalRead(4);
              if (buttonState == HIGH) {
                  cont++;
              }
      if (cont == 1) {
        
        latEscolhida = latPadrao1;
        longEscolhida = longPadrao1;
        digitalWrite (6, HIGH);
        tone(6, 2000, 10);
        delay (2000);
        digitalWrite (6, LOW);
        
       
        Serial.println("Cordenada 1");
            Serial.println("----------------------------------------");
            
            //Latitude e Longitude
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

         float bearing = gps1.course_to(latitude, longitude, latEscolhida, longEscolhida);
        if (abs(bearing) > 2) { // Se o ângulo for maior que 2 graus, aciona o bip
          Serial.println(bearing);
          digitalWrite(6, HIGH);
          tone(6, 1000, 500);
          digitalWrite(6, LOW);
        }
 
        buttonState = digitalRead(4);
            if (buttonState == HIGH) {
                cont++;
            }
       
  while (serial1.available()) {
     char cIn = serial1.read();
     recebido = gps1.encode(cIn);
  }
      } if (cont == 2) {
        
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
        
        Serial.println("Cordenada 2");
            Serial.println("----------------------------------------");
            
            //Latitude e Longitude
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

         float bearing = gps1.course_to(latitude, longitude, latEscolhida, longEscolhida);
        if (abs(bearing) > 2) { // Se o ângulo for maior que 2 graus, aciona o bip
          Serial.println(bearing);
          digitalWrite(6, HIGH);
          tone(6, 1000, 500);
          digitalWrite(6, LOW);
        }
        
             
        buttonState = digitalRead(4);
            if (buttonState == HIGH) {
                cont++;
            }
      
  while (serial1.available()) {
     char cIn = serial1.read();
     recebido = gps1.encode(cIn);
  }
      } if (cont == 3) {
        
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

      float bearing = gps1.course_to(latitude, longitude, latEscolhida, longEscolhida);
         
           if (abs(bearing) > 2) { // Se o ângulo for maior que 2 graus, aciona o bip
          Serial.println(bearing);
          digitalWrite(6, HIGH);
          tone(6, 1000, 500);
          digitalWrite(6, LOW);
        }
        Serial.println("Cordenadas 3");
     Serial.println("----------------------------------------");
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
    
  while (serial1.available()) {
     char cIn = serial1.read();
     recebido = gps1.encode(cIn);
  }
      }
      }
     digitalWrite (7, LOW);
    }
    if(cont>3){
      cont=0;
    }
  }
void enviaSMS(String telefone, String mensagem) {
  serialGSM.print("AT+CMGS=\"" + telefone + "\"\n");
  serialGSM.print(mensagem + "\n");
  serialGSM.print((char)26); 
}


void configuraGSM() {
   serialGSM.print("AT+CMGF=1\n;AT+CNMI=2,2,0,0,0\n;ATX4\n;AT+COLP=1\n"); 
}
