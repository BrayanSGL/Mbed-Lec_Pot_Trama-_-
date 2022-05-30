/*
Title: Primera Entrega
Description: Lectura de un un potenciómetro por el ADC del microcontrolador, haciendo la conversión del rango de 0V a 3.3V al rango de -250 a 250 para una realizar graficación en la próxima entrega.
Made by: Brayan Snader Galeano Lara - 2019 257 3049
@author: https://github.com/BrayanSGL
*/

#include "mbed.h"
#include "platform/mbed_thread.h"

#define measurementTime 50

RawSerial pc(USBTX, USBRX);
DigitalOut green(D7);
DigitalOut red(D6);
AnalogIn pot(A5);

float value = 0;
void dataReceived();

int main()
{
    pc.attach(&dataReceived);
    pc.baud(115200);
    pc.printf("**************************\n");

    while (true)
    {
        value = ((pot.read_u16()) / (65535 / 500)) - 250;
        pc.printf("@%d# \n\r", value);
        thread_sleep_for(measurementTime);
    }
}

void dataReceived()
{
    int received = pc.getc();
    switch (received)
    {
    case 'a':
        red = 1;
        break;
    case 'b':
        green = 1;
        break;
    case 'c':
        green = 0;
        red = 0;
        break;
    default:
        pc.printf("Comando no reconocido");
        break;
    }
}