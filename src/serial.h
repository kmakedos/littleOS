/*
 * =====================================================================================
 *
 *       Filename:  serial.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/10/18 10:34:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kostas Makedos (KM), kostas.makedos@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "io.h"

/* The I/O ports 
 * All the I/O ports are calculated relative to the data port. This is because
 * all serial ports (COM1, COM2, COM3, COM4) have their ports in the same order, but they start
 * at different values
 */



#define SERIAL_DATA_PORT(base)              (base)
#define SERIAL_FIFO_COMMAND_PORT(base)      (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)      (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base)     (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)       (base + 5)


/* The I/O port commands 


 *  SERIAL_LINE_ENABLE_DLAB:
 *  Tells the serial port to expect first the highest 8 bits on the data port, 
 *  then the lowest 8 bits will follow */
#define SERIAL_LINE_ENABLE_DLAB             0x80


/* SERIAL_CONFIGURE_BAUD_RATE:
 * Sets the speed of the data being sent. The default speed of a serial 
 * port is 115200 bits/s The argument is a divisor of that number,hence the resulting
 * speed becomes (115200/divisor) bits/s 
 *
 * @param com           The COM port to configure
 * @param divisor       The divisor 
 * */

void serial_configure_baud_rate(unsigned short com, unsigned short divisor){
    outb(SERIAL_LINE_COMMAND_PORT(com),
            SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), 
            (divisor >> 8) & 0x00FF);  // Get highest 8 bits and mask to 2 bytes max
    outb(SERIAL_DATA_PORT(com),
            divisor & 0x00FF);
}


/* Configuring Serial Port */
/*
 * Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
 * Content: | d | b | prty  | s | dl  |
 *
 * d: Enables (d=1) or disables (d=0) DLAB
 * b: if break control is enabled (b=1)
 * prty: Number of parity bits to use
 * s: Number of stop bits to use (s=0 equals 1, s=1 equals 1.5 or 2)
 * dl: Length of data
 * Standard value: 0x03 -> length 8 bits, no parity, one stop and break control disabled.
 */


/*  SERIAL_CONFIGURE_LINE:
 *  Configures the line of the given serial port. The port is set to have a data length
 *  of 8 bits, no parity bits, one stop bit and break control disabled
 *
 *  @param  con         The serial port to configure
 *  */

void serial_configure_line(unsigned short com){
 /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
  * Content: | d | b | prty  | s | dl  |
  */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}



/* Configure Buffers:
 * When data is transmitted via serial is placed on FIFO buffers.
 * Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 | 
 * Content: | lvl | bs | r | dma | clt | clr | e |
 *
 * lvl: How many bytes should be stored in FIFO buffers
 * bs:  If the buffers should be 16 or 64 bytes large
 * r:   Reserved
 * dma: How the serial port data should be accessed
 * clt: Clear the transmission FIFO buffer
 * clr: Clear the receiver FIFO buffer
 * e: If the FIFO buffer should be enabled or not
 *
 *  */
void serial_configure_buffers(unsigned short com){
    /*  We send 0xC7 == 11000111 that:
     *  - Enables FIFO
     *  - Clear both receiver and transmission FIFO queues
     *  - Use 14 bytes as size of queue
     *  */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}


/*  Configure Modem:
 *  The modem control register is used with very simple hardware flow control with 
 *  Ready To Transmit (RTS) and Data Terminal Ready (DTR) pins.
 *  When configuring the serial port we need RTS and DTR to be 1.
 *
 *  Bit:        | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
 *  Content:    | r | r | af | lb | ao2 | ao1 | rts | dtr |
 *
 *  r:      reserved
 *  af:     Autoflow control enabled
 *  lb:     Loopback mode (used for debugging serial ports)
 *  ao2:    Auxilliary output 2 (used for receiving interrupts)
 *  ao1:    Auxilliary output 1
 *  rts:    Ready To Transmit
 *  dtr:    Data Terminal Ready
 *  */

void serial_configure_modem(unsigned short com){
    /*
     * We do not use interrupts, as we won't handle any receiving data.
     * Value 0x03 = 00000011 (RTS=1, DTR=1)
     */
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}


/*
 * SERIAL_IS_TRANSMIT_FIFO_EMPTY:
 * Checks whether the transmit FIFO queue is empty or not for the given
 * COM port.
 *
 * @param   com         The COM port
 * @return  0           if the transmit FIFO is not empty
 *          1           if transmit FIFO is empty
 */

int serial_is_transmit_fifo_empty(unsigned int com){
    /*  0x20 -- 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

/* SERIAL_RECEIVED:
 * Returns a byte if it is received from serial line.
 * 
 * @return byte     The byte it was sent through serial
 */

int serial_received(unsigned short com){
    return inb(SERIAL_LINE_STATUS_PORT(com) & 1);
}


/*
 * INIT_SERIAL:
 * Initialises serial port's baud_rate, line and modem characteristics
 * Uses functions defined above.
 *
 * @param com           The com port to use (defined like #define com 03xf8)
 * @param divisor       The divisor to divide the modem speed 115200/divisor to calc. effective speed
 *
 */
void init_serial(unsigned short com, unsigned short divisor){
     serial_configure_baud_rate(com, divisor);  
     serial_configure_line(com);
     serial_configure_modem(com);
}


/*
 * SERIAL_WRITE:
 * Writes a byte to serial port
 *
 * @param com   Serial COM port to use for outgoing data
 * @param data  Data byte to send in serial port
 */
void serial_write(unsigned short com, int data){
    if (serial_is_transmit_fifo_empty(com)){
            outb(com, data);
    }
}

void serial_printf(unsigned short com, char* data){
    while (serial_is_transmit_fifo_empty(com) && (*data != '\0')) {
        outb(com, *data++);
    }
}

/*
 * READ_SERIAL:
 * Reads a byte from serial port
 *
 * @param com       Serial COM port to read byte from 
 * @return byte     Byte read
 */

char read_serial(unsigned short com){
    while(serial_received(com) == 0);
    return inb(com);
}

typedef enum Severity{
    INFO,
    WARN,
    ERROR,
    DEBUG
}Severity;


