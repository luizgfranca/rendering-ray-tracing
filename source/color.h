#pragma once
#include "common.h"
#include "vec3.h"
#include <cmath>


constexpr u_int color_value_to_uint(double value) {
    return u_int(255.999 * value);
}

constexpr double linear_to_gama_space(double color_component) {
    return color_component > 0 ? sqrt(color_component) : 0;
}

class Color : public Vec3 {
public:
    Color(): Vec3() {};
    Color(double red, double green, double blue): Vec3(red, green, blue) {};
    Color(Vec3& v): Vec3(v) {};
    
    u_int red() const { return color_value_to_uint(data[0]); }
    u_int green() const { return color_value_to_uint(data[1]); }
    u_int blue() const { return color_value_to_uint(data[2]); }

    u_int gamma_corrected_red() const { return color_value_to_uint(linear_to_gama_space(data[0])); }
    u_int gamma_corrected_green() const { return color_value_to_uint(linear_to_gama_space(data[1])); }
    u_int gamma_corrected_blue() const { return color_value_to_uint(linear_to_gama_space(data[2])); }

    void set_render_color(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(
            renderer,
            gamma_corrected_red(),
            gamma_corrected_green(),
            gamma_corrected_blue(),
            255
        );
    }

    static Color& from(Vec3& v) { return static_cast<Color&>(v); }
    static Color& from(Vec3 v) { 
        Vec3* ref = &v;
        return static_cast<Color&>(*ref); 
    }
};