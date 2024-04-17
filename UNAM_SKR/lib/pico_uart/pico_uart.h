#ifndef __PICO_UART_H__
#define __PICO_UART_H__

class PICO_UART
{

private:
    int uart_id;
    int baud_rate;

    int temp;
    int speed;

public:
    void sendNEMA(float speed);
    void sendValues(float temp, float mm_per_min);
    void receiveData();
};

#endif