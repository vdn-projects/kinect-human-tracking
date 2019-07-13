#ifndef _UART_H_
#define	_UART_H_

#ifndef _XTAL_FREQ
#define _XTAL_FREQ	4000000
#endif

#define	BAUD	19200
#define	TX_TRIS	TRISC6
#define	RX_TRIS	TRISC7

void uart_init();
void uart_putc(char c);
void uart_puts(const char *s);
char uart_data_ready();
char uart_getc();
void uart_gets(char *s);
#endif