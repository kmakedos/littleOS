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

#define FB_COMMAND_PORT         0x3D4 
#define FB_DATA_PORT            0x3D5
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15
/* 
 * fb_write_cell:
 * Writes a character with the given foreground and background to position i
 * in the framebuffer
 * @param i     The location in the framebuffer
 * @param c     The character
 * @param fg    Foreground color
 * @param bg    Background color
 * */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg){
    char *fb = (char *) 0x000B8000;
    fb[2 * i ] = c;
    fb[2 * i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

/*
 * fb_move_cursor:
 * Moves the cursor of the framebuffer to the given position
 *
 * @param pos   The new position of the cursor
 */
void fb_move_cursor(unsigned short pos){
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (( pos >> 8 ) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT, pos & 0x00FF);
}


void write(char *buf, unsigned int len){
   for (unsigned int i = 0; i < len; i++){
       fb_write_cell(i, buf[i],  0, 7);
       fb_move_cursor(i+1);
    }
}

/*
 * kmain:
 * Function to be called from assembly code when boot system starts.
 * 
 */
void kmain(){
    char buf[3] = "012";
    write(buf, 3);
}
