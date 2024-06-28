#ifndef MOVING_DOTS_H
#define MOVING_DOTS_H

#include <cstdint>

#include "freertos/FreeRTOS.h"

#include "../led_cube.h"

struct MovingDot{
    int32_t x;
    int32_t y;
    int32_t r;
    int32_t g;
    int32_t b;
    int32_t xdir;
    int32_t ydir;
    TickType_t counter;
    TickType_t move_after;
    static MovingDot random();
};

class DotManager{
    public:
        static const unsigned char MAX_DOTS=25;
        DotManager(const LedCube &led_cube);
        void update(TickType_t dt);
        bool add_dot(const MovingDot &m);
        bool add_dot();
    private:
        const LedCube &led_cube_;
        MovingDot dots[MAX_DOTS];
        unsigned char num_dots=0;        
};

#endif