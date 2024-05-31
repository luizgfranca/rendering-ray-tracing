#pragma once

#include <sys/types.h>


#include <SDL_render.h>
#include <SDL_events.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include <cmath>
#include <iostream>
#include <optional>
#include <memory>
#include <vector>

constexpr double PI = 3.1415926535897932385;


auto linear_interpolation(auto start_value, auto end_value, double a) {
    return ((1 - a) * start_value) + (a * end_value);
}