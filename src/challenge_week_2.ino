#include "OneWire.h"
#include "spark-dallas-temperature.h"
#include "analogEC.h"

#include <Ubidots.h>           
const char *WEBHOOK_NAME = "temp_ec";//webhook name
Ubidots ubidots("webhook", UBI_PARTICLE); //standard

analogEC EC_sensor(A1);

double ec = 0.0;

OneWire oneWire( D2 );
DallasTemperature dallas(&oneWire);
double tempC = 0.0;

//=================functions activated from ubidots=====================
int led = D7;
int switchBuiltinLed(String command) {
// look for the matching argument "ON"
    if (command == "ON") {
        digitalWrite(led, HIGH);
        return 1;
    }
    // look for the matching argument "OFF"
    else if (command == "OFF") {
        digitalWrite(led, LOW);
        return 1;
    }
    return -1;
}
//========================================================================
void setup()
{
  Serial.begin(9600);
  Particle.function("Switch", switchBuiltinLed);
  pinMode(led, OUTPUT);
  dallas.begin();
}

void loop()
{
   delay(2000);
//=========================get temp================================

   dallas.requestTemperatures();
   tempC = dallas.getTempCByIndex(0);

//=========================get EC==================================

   ec = EC_sensor.getEC(tempC);

//==================send data to ubidots===========================
   ubidots.add("temp", tempC);
   ubidots.add("ec",ec);
   bool bufferSent = false;
   bufferSent = ubidots.send(WEBHOOK_NAME, PUBLIC);

   if (bufferSent){
        // Do something if values were sent properly
        Serial.println("Values sent by the device");
    }
//=================print on terminal===============================

   Serial.println("temp = "+String(tempC)+" C");
   Serial.println("EC val = "+String(ec)+" ms/cm");

//===============wait for 10 sec====================================

   delay(8000);
}