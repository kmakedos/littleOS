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
#define FB_COMMAND_PORT         0x3D4 
#define FB_DATA_PORT            0x3D5
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/*
 * outb:
 * Sends the given date to the given I/O port. Defined in io.s
 *
 * @param port      The I/O port to send the data to
 * @parma data      The data to send to the I/O port
 */
void outb(unsigned short port, unsigned char data);


/*
 * inb:
 * Read a byte from the I/O port:
 *
 * @param   port        The address of the I/O port
 * @return              The read byte
 */

unsigned char inb(unsigned short port);

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
    fb[2 * i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F); // We mask with & 0xF to restrict num to 1 byte
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

/*
 * Implementation of a framebuffer write command which uses
 * fb_write_cell and fb_move_cursor
 *
 * @param   buf     A char array to be printed 
 * @param   len     Length of buf in bytes
 */
void fb_write(char *buf, unsigned int len){
   for (unsigned int i = 0; i < len; i++){
       fb_write_cell(i, buf[i],  0, 7);
       fb_move_cursor(i+1);
    }
}


void serial_write(char *buf, unsigned int len){

}

#endif /*  INCLUDE_IO_H  */
