/*
 * =====================================================================================
 *
 *       Filename:  io.h
 *
 *    Description:  Wrapper for io functions in assembly that cannot be called directly
 *    from C code
 *
 *        Version:  1.0
 *        Created:  30/09/2018 01:58:56 πμ
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kostas Makedos (KM), kostas.makedos@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/*
 * outb:
 * Sends the given date to the given I/O port. Defined in io.s
 *
 * @param port      The I/O port to send the data to
 * @parma data      The data to send to the I/O port
 */
void outb(unsigned short port, unsigned char data);

#endif /*  INCLUDE_IO_H  */
