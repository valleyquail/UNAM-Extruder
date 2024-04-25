#include <Arduino.h>

#include "pico_uart.h"


int uart_id;
int baud_rate;

int temp;
int speed;

bool initPicoUART(){
    Serial.begin(115200);
    long start_time = millis();
    while (!Serial && millis() - start_time < 5000){

    }
    if (!Serial){
        return false;
    }
return true;
}

void sendNEMA(float speed){
    Serial.print("M");
    Serial.println(speed);
}
void sendValues(float temp, float mm_per_min){

}
void receiveData(){}