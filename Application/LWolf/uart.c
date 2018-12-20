#include "uart.h"


/*void UART_Init(uint32_t baudrate) {
	GPIO_InitTypeDef PORT;

	// U(S)ART init
#if _UART_PORT == 1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
#elif _UART_PORT == 2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
#elif _UART_PORT == 3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
#elif _UART_PORT == 4
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
#elif _UART_PORT == 5
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
#endif

	PORT.GPIO_Pin = UART_TX_PIN;
	PORT.GPIO_Speed = GPIO_Speed_50MHz;
	PORT.GPIO_Mode = GPIO_Mode_AF_PP; // TX as AF with Push-Pull
	GPIO_Init(UART_GPIO_PORT_TX,&PORT);
	PORT.GPIO_Pin = UART_RX_PIN;
	PORT.GPIO_Speed = GPIO_Speed_50MHz;
	PORT.GPIO_Mode = GPIO_Mode_IN_FLOATING; // RX as in without pull-up
	GPIO_Init(UART_GPIO_PORT_RX,&PORT);

	USART_InitTypeDef UART;
	UART.USART_BaudRate = baudrate;
	UART.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // No flow control
	UART.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // RX+TX mode
	UART.USART_WordLength = USART_WordLength_8b; // 8-bit frame
	UART.USART_Parity = USART_Parity_No; // No parity check
	UART.USART_StopBits = USART_StopBits_1; // 1 stop bit
	USART_Init(UART_PORT,&UART);
	USART_Cmd(UART_PORT,ENABLE);
}*/

void UART_SendChar(char ch) {

	HAL_UART_Transmit(get_huart1(), (uint8_t*) &ch, 1, 500);

	//while (!USART_GetFlagStatus(UART_PORT,USART_FLAG_TC)); // wait for "Transmission Complete" flag cleared
	//USART_SendData(UART_PORT,ch);
}

void UART_SendInt(int32_t num) {
	char str[10]; // 10 chars max for INT32_MAX
	int i = 0;
	if (num < 0) {
		UART_SendChar('-');
		num *= -1;
	}
	do str[i++] = num % 10 + '0'; while ((num /= 10) > 0);
	for (i--; i >= 0; i--) UART_SendChar(str[i]);
}

void UART_SendInt0(int32_t num) {
	char str[10]; // 10 chars max for INT32_MAX
	int i = 0;
	if (num < 0) {
		UART_SendChar('-');
		num *= -1;
	}
	if ((num < 10) && (num >= 0)) UART_SendChar('0');
	do str[i++] = num % 10 + '0'; while ((num /= 10) > 0);
	for (i--; i >= 0; i--) UART_SendChar(str[i]);
}

void UART_SendHex8(uint16_t num) {
	UART_SendChar(HEX_CHARS[(num >> 4)   % 0x10]);
	UART_SendChar(HEX_CHARS[(num & 0x0f) % 0x10]);
}

void UART_SendHex16(uint16_t num) {
	uint8_t i;
	for (i = 12; i > 0; i -= 4) UART_SendChar(HEX_CHARS[(num >> i) % 0x10]);
	UART_SendChar(HEX_CHARS[(num & 0x0f) % 0x10]);
}

void UART_SendHex32(uint32_t num) {
	uint8_t i;
	for (i = 28; i > 0; i -= 4)	UART_SendChar(HEX_CHARS[(num >> i) % 0x10]);
	UART_SendChar(HEX_CHARS[(num & 0x0f) % 0x10]);
}

void UART_SendStr(char *str) {
	while (*str) UART_SendChar(*str++);
}

void UART_SendBuf(char *buf, uint16_t bufsize) {
	uint16_t i;
	for (i = 0; i < bufsize; i++) UART_SendChar(*buf++);
}

void UART_SendBufPrintable(char *buf, uint16_t bufsize, char subst) {
	uint16_t i;
	char ch;
	for (i = 0; i < bufsize; i++) {
		ch = *buf++;
		UART_SendChar(ch > 32 ? ch : subst);
	}
}

void UART_SendBufHex(char *buf, uint16_t bufsize) {
	uint16_t i;
	char ch;
	for (i = 0; i < bufsize; i++) {
		ch = *buf++;
		UART_SendChar(HEX_CHARS[(ch >> 4)   % 0x10]);
		UART_SendChar(HEX_CHARS[(ch & 0x0f) % 0x10]);
	}
}

void UART_SendBufHexFancy(char *buf, uint16_t bufsize, uint8_t column_width, char subst) {
	uint16_t i = 0,len,pos;
	char buffer[column_width];

	while (i < bufsize) {
		// Line number
		UART_SendHex16(i);
		UART_SendChar(':'); UART_SendChar(' '); // Faster and less code than UART_SendStr(": ");

		// Copy one line
		if (i+column_width >= bufsize) len = bufsize - i; else len = column_width;
		memcpy(buffer,&buf[i],len);

		// Hex data
		pos = 0;
		while (pos < len) UART_SendHex8(buffer[pos++]);
		UART_SendChar(' ');

		// Raw data
		pos = 0;
		do UART_SendChar(buffer[pos] > 32 ? buffer[pos] : subst); while (++pos < len);
		UART_SendChar('\n');

		i += len;
	}
}

#if (USART_USE_PRINTF)

#include <stdarg.h>
// Transmit formatted string via USART
// input:
//   USARTx - pointer to the USART port handler (hUSART1, hUART4, etc.)
//   fmt - format string
//   ... - optional arguments
// return: number of transmitted characters
// note:
//   supported sub-set of standard format:
//     type:
//       i, d - signed integer
//       u    - unsinged integer
//       b    - binary
//       o    - octal
//       x    - hexadecimal in lowercase
//       X    - hexadecimal in uppercase
//       c    - character
//       s    - string
//     flag:
//       0    - add zero padding
//       -    - left justify field
//       .X   - add a decimal point (on 'X' place must be a single digit
//              determining number of digits after the decimal point)
// examples:
//   ("%d", 1234)     --> "1234"
//   ("%-5d", 123)    --> "123  "
//   ("%5d", 123)     --> "  123"
//   ("%05d", 123)    --> "00123"
//   ("%2s", "USART") --> "US"
//   ("%.3u", 123456) --> "123.456"
//   ("%-8.2u", 1234) --> "12.34   "
int USART_printf(USART_TypeDef *USARTx, const char *fmt, ...) {
	va_list ap;        // arguments pointer
	uint8_t flag;      // field flag
	uint8_t width;     // specified field width
	uint8_t prec;      // specified precision
	uint8_t len = 0;   // actual field length
	uint8_t radix;     // value conversion radix
	uint32_t num;      // value to convert
	char str[33];      // maximal width of 32-bit binary + string terminating symbol
	char *pstr, *tstr; // pointers for various string manipulations
	char chr;          // to hold a single character from format string

	// Initialize an arguments pointer
	va_start(ap, fmt);

	// Process format string
	while (1) {
		// Get character from the format string
		chr = *fmt++;

		// String termination?
		if (!chr) { break; }

		// Non escape character
		if (chr != '%') {
			//USART_SendChar(USARTx, chr);
			UART_SendChar(chr);
			continue;
		}

		// Next after an escape character
		chr = *fmt++;

		// Flag?
		flag = 0x00;
		if (chr == '0') {
			// Flag '0' --> padding
			flag = 0x01;
			chr = *fmt++;
		} else if (chr == '-') {
			// Flag '-' --> left justified
			flag = 0x02;
			chr = *fmt++;
		}

		// Width?
		width = 0;
		while ((chr > '0' - 1) && (chr < '9' + 1)) {
			width *= 10;
			width += chr - '0';
			chr = *fmt++;
		}

		// Precision?
		prec = 0;
		if (chr == '.') {
			chr = *fmt++;
			if ((chr > '0' - 1) && (chr < '9' + 1)) {
				// Flag '.' --> number with decimal point
				prec = chr - '0';
				if (prec) { flag |= 0x08; }
				chr = *fmt++;
			}
		}

		// Ensure a string is not terminated yet
		if (!chr) { break; }

		// A type is...
		// (chr | 0x20) --> convert character to lower case
		switch (chr | 0x20) {
			case 's':
				// String

				// Calculate string length
				len = 0;
				tstr = pstr = va_arg(ap, char*);
				while (*pstr++) { len++; }

				// Transmit leading spaces if string length is less than field width
				if (!(flag & 0x02) && (len < width)) {
					while (len++ < width) {
						UART_SendChar(' ');
					}
				}

				// Transmit string
				pstr = tstr;
				if (width) len = width;
				while (*pstr) {
					UART_SendChar(*pstr++);
					if (!(--len)) { break; }
				}

				// Transmit trailing spaces in case of left justified field
				if (flag & 0x02) {
					while (len--) {
						UART_SendChar(' ');
					}
				}

				continue;
			case 'c':
				// Character
				UART_SendChar((char)va_arg(ap, int));
				continue;
			case 'b':
				// Binary
				num = (uint32_t)va_arg(ap, uint32_t);
				radix = 2;
				break;
			case 'o':
				// Octal
				num = (uint32_t)va_arg(ap, uint32_t);
				radix = 8;
				break;
			case 'i':
			case 'd':
				// Signed decimal
				num = (int32_t)va_arg(ap, int32_t);
				if (num & 0x80000000) {
					num = 0 - num;
					flag |= 0x04;
				}
				radix = 10;
				break;
			case 'u':
				// Unsigned decimal
				num = (uint32_t)va_arg(ap, uint32_t);
				radix = 10;
				break;
			case 'x':
				// Hexadecimal
				num = (uint32_t)va_arg(ap, uint32_t);
				radix = 16;
				break;
			default:
				// Unknown: just pass
				UART_SendChar(chr);
				continue;
		}

		// Convert value to characters
		pstr = str;
		*pstr++ = '\0';
		len = 0;
		if (num) {
			// Value is not a zero
			do {
				*pstr = (num % radix);
				if (*pstr > 9) {
					*pstr += (chr == 'x') ? 0x27 : 0x07;
				}
				*pstr++ += '0';
				len++;
				if (flag & 0x08) {
					if (len == prec) {
						*pstr++ = '.';
						len++;
					}
				}
			} while (num /= radix);

			// In case of format with decimal point the leading zeroes must be added if
			// current length of the number is less than a specified precision
			if (flag & 0x08) {
				if (len == prec + 1) {
					*pstr++ = '0';
					len++;
				} else if (len <= prec) {
					while (len < prec) {
						*pstr++ = '0';
						len++;
					}
					*pstr++ = '.';
					*pstr++ = '0';
					len += 2;
				}
			}

			// Add negative symbol
			if (flag & 0x04) {
				*pstr++ = '-';
				len++;
			}
		} else {
			// Little optimization for a zero value
			if (flag & 0x08) {
				while (len++ < prec) { *pstr++ = '0'; }
				*pstr++ = '.';
				len++;
			} else len++;
			*pstr++ = '0';
		}

		// Add leading zeroes or spaces
		prec += (flag & 0x08) ? (width - prec) : width;
		if (!(flag & 0x02) && (len < prec)) {
			while (len++ < prec) {
				*pstr++ = (flag & 0x01) ? '0' : ' ';
			}
		}

		// Transmit value as text
		while (*--pstr) {
			UART_SendChar(*pstr);
		}

		// Transmit trailing spaces
		if (flag & 0x02) {
			while (len++ < width) {
				UART_SendChar(' ');
			}
		}
	}

	// Cleanup for an arguments pointer
	va_end(ap);

	// TODO: USART: return an actual length of the transmitted data
	return 0;
}

#endif // USART_USE_PRINTF

