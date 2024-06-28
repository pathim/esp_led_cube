#include "led_cube.h"

LedCube::LedCube(const led_strip_handle_t led_strip,const int32_t side_length):led_strip_{led_strip},side_length_{side_length}{}

Pos LedCube::set_pixel(Pos pos, const uint32_t r, const uint32_t g, const uint32_t b) const{
    int32_t x=pos.x;
    int32_t y=pos.y;
    while(x>=4*this->side_length_){x-=4*this->side_length_;}
    while(x<0){x+=4*this->side_length_;}
    while(y>=this->side_length_){y-=this->side_length_;}
    while(y<-2*this->side_length_){y+=this->side_length_;}
    int lin_pos=this->transform_to_side(x,y);
    led_strip_set_pixel(this->led_strip_, lin_pos, r, g, b);
    return Pos{.x=x,.y=y};
}

void LedCube::set_pixel_raw(uint32_t pos, const uint32_t r, const uint32_t g, const uint32_t b) const{
    led_strip_set_pixel(this->led_strip_, pos, r, g, b);
}

void LedCube::clear() const{
    led_strip_clear(this->led_strip_);
}

void LedCube::refresh() const{
    led_strip_refresh(this->led_strip_);
}

uint32_t LedCube::transform_to_side(const int32_t x, const int32_t y) const{
    int panel=0;
    int panel_x=0;
    int panel_y=y;
    if (y>=0){
        panel=1+x/this->side_length_;
        panel_x=x%this->side_length_;
    } else if (y>=-this->side_length_){
        if (x<this->side_length_){
            panel_x=this->side_length_-1-x;
            panel_y=-y-1;
        } else if (x<this->side_length_*2){
            panel_x=-y-1;
            panel_y=x-this->side_length_;
        }else if (x<this->side_length_*3){
            panel_x=x-this->side_length_*2;
            panel_y=this->side_length_+y;
        }else{
            panel_x=this->side_length_+y;
            panel_y=this->side_length_-1-(x-this->side_length_*3);
        }
    } else {
        panel_y=-y-this->side_length_-1;
        panel_x=this->side_length_-1-x%this->side_length_;
        panel=1+x/this->side_length_+2;
        if (panel>4){
            panel-=4;
        }
    }
    return this->side_length_*this->side_length_*panel+this->side_length_*panel_y+panel_x;
}
