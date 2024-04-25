#ifndef __PICO_UART_H__
#define __PICO_UART_H__


bool initPicoUART();
void sendNEMA(float speed);
void sendValues(float temp, float mm_per_min);
void receiveData();

#endif