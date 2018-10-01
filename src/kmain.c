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

/*
 * kmain:
 * Function to be called from assembly code when boot system starts.
 * 
 */
void kmain(){
    char buf[6] = "kostas";
    fb_write(buf, 6);
}
