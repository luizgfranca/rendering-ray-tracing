#include <SDL2/SDL_render.h>
#include <SDL_events.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <SDL2/SDL.h>
#include <sys/types.h>

typedef struct pixel {
    u_int8_t red;
    u_int8_t green;
    u_int8_t blue;
} pixel;

void render_test_image(int width, int height, std::function<void(pixel, size_t, size_t)> pixel_render_fn) {
    // std::cout << "P3\n" << width << " " << height << "\n255\n";

    for(int line = 0; line < height; line ++) {
        for(int column = 0; column < width; column ++) {
           auto red = double(line) / (width - 1);
           auto green = double(column) / (height - 1);
           auto blue = 1.0 - red - green;

           if(blue < 0) {
                blue = 0;
           }

           pixel px = {
                .red = u_int8_t(255.999 * red),
                .green = u_int8_t(255.999 * green),
                .blue = u_int8_t(255.999 * blue)
           };

        //    int px_red = int(255.999 * red);
        //    int px_green = int(255.999 * green);
        //    int px_blue = int(255.999 * blue);

        //    std::cout << px_red << " " << px_green << " " << px_blue << "\n";
            pixel_render_fn(px, column, line);
        }
    }
}

void render_pixel(SDL_Renderer* renderer, size_t x, size_t y, pixel px) {
    SDL_SetRenderDrawColor(
        renderer, 
        px.red, 
        px.green, 
        px.blue, 
        255
    );

    SDL_RenderDrawPoint(renderer, x, y);
}

int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;

    SDL_Event event;

    window = SDL_CreateWindow(
        "rendering", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        800, 
        800, 
        SDL_WINDOW_SHOWN
    );

    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateSoftwareRenderer(surface);

    render_test_image(
        800, 
        800, 
        [&renderer, &window, &event](pixel px, size_t x, size_t y) {
            if( SDL_PollEvent(&event) && event.type == SDL_QUIT ) {
                exit(0);
            }

            render_pixel(renderer, x, y, px);

            if(x == 0 && y % 2 == 0) {
                SDL_UpdateWindowSurface(window);
            }
        }
    );

    // SDL_UpdateWindowSurface(window);

    while (true) {
        if( SDL_PollEvent(&event) && event.type == SDL_QUIT ) {
            SDL_Quit();
            return 0;
        }       
    }

    return 0;
}