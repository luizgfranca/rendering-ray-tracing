#pragma once
#include "common.h"
#include "vec3.h"


constexpr u_int color_value_to_uint(double value) {
    return u_int(255.999 * value);
}

class Color : public Vec3 {
public:
    Color(): Vec3() {};
    Color(double red, double green, double blue): Vec3(red, green, blue) {};
    Color(Vec3& v): Vec3(v) {};
    
    u_int red() const { return color_value_to_uint(data[0]); }
    u_int green() const { return color_value_to_uint(data[1]); }
    u_int blue() const { return color_value_to_uint(data[2]); }

    void set_render_color(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(
            renderer,
            red(),
            green(),
            blue(),
            255
        );
    }

    static Color& from(Vec3& v) { return static_cast<Color&>(v); }
    static Color& from(Vec3 v) { 
        Vec3* ref = &v;
        return static_cast<Color&>(*ref); 
    }
};