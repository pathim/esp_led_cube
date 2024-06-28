#include "font8x8_basic.h"
#include "led_cube.h"

static void show_char_raw(const LedCube &led_cube, int c, int fg, int bg, int pos0){
    char *font=font8x8_basic[c];
    char fg_b=fg&0xff;
    char fg_g=(fg>>8)&0xff;
    char fg_r=(fg>>16)&0xff;
    
    char bg_b=bg&0xff;
    char bg_g=(bg>>8)&0xff;
    char bg_r=(bg>>16)&0xff;

    int pos=pos0;

    for(int i=0;i<8;i++){
        char line=font[i];
        for(int bit=0;bit<8;bit++){
            if(line&1){
                led_cube.set_pixel_raw(pos, fg_r, fg_g, fg_b);
            } else {
                led_cube.set_pixel_raw(pos, bg_r, bg_g, bg_b);
            }
            line>>=1;
            pos++;
        }
    }
}

void show_char(const LedCube &led_cube, int c, int fg, int bg, int side){
    show_char_raw(led_cube, c, fg, bg, side*64);
}