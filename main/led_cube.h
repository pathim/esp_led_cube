#ifndef LED_CUBE_H
#define LED_CUBE_H

#include "led_strip.h"

#include <cstdint>

struct Pos{
    int32_t x;
    int32_t y;
};

class LedCube{
    public:
        LedCube(const led_strip_handle_t led_strip, const int32_t side_length);
        Pos set_pixel(Pos pos, const uint32_t r, const uint32_t g, const uint32_t b) const;
        void set_pixel_raw(uint32_t pos, const uint32_t r, const uint32_t g, const uint32_t b) const;
        void clear() const;
        void refresh() const;
    private:
        const led_strip_handle_t led_strip_;
        const int32_t side_length_;
        uint32_t transform_to_side(const int32_t x, const int32_t y) const;
};

#endif