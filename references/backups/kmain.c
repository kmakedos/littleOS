/*
 * =====================================================================================
 *
 *       Filename:  kmain.c
 *
 *    Description: A basic c file to be called from assembly machine code.
 *    
 *
 *        Version:  1.0
 *        Created:  30/09/2018 01:08:04 πμ
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Kostas Makedos (KM), kostas.makedos@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include "io.h"
#include "serial.h"

#define COM1_BASE    0x3F8   /*  COM1 BASE PORT */
/*
 * kmain:
 * Function to be called from assembly code when boot system starts.
 * 
 */


void kmain(){
    struct gdt f;
    f.address = 0x0;
    f.size = 0x8;
    load_gdt(&f);
    char buf[6] = "kostas";
    fb_write(buf, 6);
    char buf2[10] = "Address:";
    buf2[9] = f.address;
    fb_write(buf2, 10);

    init_serial(COM1_BASE, 1);
    serial_printf(COM1_BASE, buf);
}
