#define F_CPU 8000000UL         /* 8 MHz crystal clock */

#include <avr/io.h> 
#include <avr/pgmspace.h>

#define COMMAND_HELLO 0x01

/**
 *  Initialize the AVR USART
 *
 *  Uses macro helpers for baud rate calculation from
 *  http://www.nongnu.org/avr-libc/user-manual/group__util__setbaud.html
 *  Make sure define BAUD matches baud rate specified in hello.py
 *
 *  The USART frame is not set because the default 8n1 is what we want.
 */
static void USART_init() 
{
    #undef BAUD  
    #define BAUD 9600               
    #include <util/setbaud.h>

    UBRRH = UBRRH_VALUE;
    UBRRL = UBRRL_VALUE;
    #if USE_2X
    UCSRA |= (1 << U2X);
    #else
    UCSRA &= ~(1 << U2X);
    #endif

    /* enable rx and tx */
    UCSRB = (1<<RXEN) | (1<<TXEN);
}

/**
 *  Get a byte from the USART (rx)
 */
uint8_t USART_get_char()
{
    while(!(UCSRA & (1<<RXC))) 
        ;
    
    return UDR;
}

/**
 *  Send a byte from the USART (tx)
 */
void USART_send_char(uint8_t data)
{
    while(!(UCSRA & (1<<UDRE)))
        ;

    UDR = data;
}

/**
 *  Send a string located in program memory (flash) from the USART (tx)
 *
 *  The string can either be an anonymous string (PSTR) or defined with the
 *  PROGMEM attribute. See 
 *  http://www.nongnu.org/avr-libc/user-manual/group__avr__pgmspace.html
 */
void USART_send_str_P(const char *data)
{
    while (pgm_read_byte(data) != 0x00) 
    {
        USART_send_char((uint8_t)pgm_read_byte(data++));
    }
}

int
main (void)
{
    uint8_t command;
    
    USART_init();
    
    while (1)   /* infinite loop */           
    {
        command = USART_get_char();

        if (command == COMMAND_HELLO)
        {
            USART_send_str_P(PSTR("Hello Python!"));
        }
    }
    return (0);
}

