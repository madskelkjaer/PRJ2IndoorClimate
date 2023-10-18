/*
 * UART.h
 *
 * Created: 16-10-2023 13:43:02
 *  Author: madse
 */ 


#ifndef UART_H_
#define UART_H_

class UART
{
public:
UART();
void transmit(unsigned char data);
void transmitString(const char *str);
unsigned char recieve();
void recieveString(char* buffer, int length);
private:
};



#endif /* UART_H_ */