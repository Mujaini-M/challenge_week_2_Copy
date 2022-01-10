#ifndef analogEC_h
#define analogEC_h

#include "Particle.h"

class analogEC {
    public:
       analogEC(int pin);
       void begin();
       float getEC(float temp);
       float calibrate(float ecVal, float temp);

    private:
       int _pin;
       float EC_Vo;
       float EC_val_no_temp;
       float EC_val_with_temp;
       float Compensation_Coefficient;
       float temperature_compensation;

};
#endif