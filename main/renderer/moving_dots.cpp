#include "freertos/FreeRTOS.h"
#include "led_strip.h"
#include "led_cube.h"
#include "moving_dots.h"

MovingDot MovingDot::random(){
    MovingDot m;
    m.x=rand()%32;
    m.y=rand()%16-8;
    m.counter=m.move_after=rand()%100;
    m.r=rand()%50;
    m.g=rand()%50;
    m.b=rand()%50;
    m.xdir=rand()%3-1;
    m.ydir=rand()%3-1;
    return m;
}

DotManager::DotManager(const LedCube &led_cube):led_cube_{led_cube}{};

bool DotManager::add_dot(const MovingDot &m){
    if (this->num_dots>=this->MAX_DOTS){
        return false;
    }
    this->dots[this->num_dots]=m;
    this->num_dots++;
    return true;
}

bool DotManager::add_dot(){
    return this->add_dot(MovingDot::random());
}

void DotManager::update(TickType_t dt){
    for(int i=0;i<this->num_dots;i++){
        MovingDot& m=this->dots[i];        
        m.counter-=dt;
        if (m.counter<=0){
            m.counter+=m.move_after;
            this->led_cube_.set_pixel(Pos{m.x,m.y},0,0,0);
            m.x+=m.xdir;
            m.y+=m.ydir;
        }
        Pos new_pos=this->led_cube_.set_pixel(Pos{m.x, m.y}, m.r, m.g, m.b);
        m.x=new_pos.x;
        m.y=new_pos.y;
    }
}