#include "Particle.h"
#include "analogEC.h"

analogEC::analogEC(int pin){
    _pin = pin;
    begin();
}

void analogEC::begin(){
    pinMode(_pin, INPUT);
}

float analogEC::getEC(float temp){
    EC_Vo = (analogRead(_pin)*3.3)/4096.0;
    EC_val_no_temp = (EC_Vo*1.386)/0.345;
    EC_val_with_temp = calibrate(EC_val_no_temp, temp);

    return EC_val_with_temp;
}

float analogEC::calibrate(float ecVal, float temp){
    Compensation_Coefficient = 1.0+0.02*(25.0-temp);
    temperature_compensation = ecVal / Compensation_Coefficient;     //temperature compensation
    return temperature_compensation;

}

