/*
 * =====================================================================================
 *
 *       Filename:  kmain.c
 *
 *    Description:  
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
    fb[i] = c;
    fb[i+1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

void kmain(){
    fb_write_cell(0, 'A', 2, 8);
}
