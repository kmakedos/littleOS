//
// Created by kostas on 15/10/20.
//

#ifndef OS_FROM_SCRATCH_SCREEN_H

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLUMNS 80
#define WHITE_ON_BLACK 0x0F
#define RED_ON_WHITE 0xF4

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void clear_screen();
void kprint_at(char *message, int col, int row);

void kprint(char* message);

#define OS_FROM_SCRATCH_SCREEN_H

#endif //OS_FROM_SCRATCH_SCREEN_H
