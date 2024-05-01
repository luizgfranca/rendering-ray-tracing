#include <SDL2/SDL_render.h>
#include <SDL_events.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <SDL2/SDL.h>
#include <sys/types.h>
#include "color.h"
#include "point3.h"
#include "sphere.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"

constexpr double ASPECT_RATIO = 16.0 / 9.0;
constexpr u_int IMAGE_WIDTH = 800;
constexpr double VIEWPORT_HEIGHT = 2;

consteval u_int IMAGE_HEIGHT() {
    auto height = u_int(IMAGE_WIDTH / ASPECT_RATIO);
    height = height < 1 ? 1 : height;
    return height;
}

consteval double VIEWPORT_WIDTH() {
    return VIEWPORT_HEIGHT * double(IMAGE_WIDTH) / double(IMAGE_HEIGHT());
}

const Point3 CAMERA_CENTER(0, 0, 0);
constexpr double FOCAL_LENGTH = 1;

const Vec3 VIEWPORT_HORIZONTAL_VEC(VIEWPORT_WIDTH(), 0, 0);
const Vec3 VIEWPORT_VERTICAL_VEC(0, -VIEWPORT_HEIGHT, 0);
const Vec3 PIXEL_DELTA_HORIZONTAL = VIEWPORT_HORIZONTAL_VEC / IMAGE_WIDTH;
const Vec3 PIXEL_DELTA_VERTICAL = VIEWPORT_VERTICAL_VEC / IMAGE_HEIGHT();


Point3 VIEWPORT_UPPER_LEFT = *static_cast<Point3*>(
    new Vec3(
        CAMERA_CENTER 
        - Vec3(0, 0, FOCAL_LENGTH) 
        - (VIEWPORT_HORIZONTAL_VEC / 2)
        - (VIEWPORT_VERTICAL_VEC / 2)
    )
);

const Point3 PIXEL_0X0_PROJECTED_LOCATION = *static_cast<Point3*>(
    new Vec3(
        VIEWPORT_UPPER_LEFT
        + (0.5 * (PIXEL_DELTA_HORIZONTAL + PIXEL_DELTA_VERTICAL))
    )
);


const sphere SIMPLE_SPHERE = {
    .center = Point3(0, 0, -1),
    .radius = 0.5
};


auto linear_interpolation(auto start_value, auto end_value, double a) {
    return ((1 - a) * start_value) + (a * end_value);
}

Color blank_ray_color(const Ray& ray) {
    return Color();
}

Color gradient_ray_color(const Ray& ray) {
    auto unit_direction = vec_op::unit_vector(ray.direction());
    auto a = 0.5 * (unit_direction.y() + 1);
    auto blended = linear_interpolation(
        Color(1, 1, 1), 
        Color(0.2, 0.5, 1), 
        a
    );

    return *static_cast<Color*>(&blended);
}

Color simple_circle_color_fn(const Ray& ray) {
    auto unit_direction = vec_op::unit_vector(ray.direction());
    
    double ray_hit_position = sphere_op::hit_sphere(SIMPLE_SPHERE, ray);
    if(ray_hit_position > 0) {
        auto surface_normal_vector = vec_op::unit_vector(ray.at(ray_hit_position) - Vec3(0, 0, -1));
        
        return Color::from(0.5 * Vec3(
            surface_normal_vector.x() + 1,
            surface_normal_vector.y() + 1,
            surface_normal_vector.z() + 1
        ));
    }
    
    auto a = 0.5 * (unit_direction.y() + 1);
    auto blended = linear_interpolation(
        Color(1, 1, 1), 
        Color(0.2, 0.5, 1), 
        a
    );

    return *static_cast<Color*>(&blended);
}

void render_pixel(
    SDL_Window* window, 
    SDL_Renderer* renderer, 
    u_int x, 
    u_int y, 
    const Color& color
) {
    color.set_render_color(renderer);
    SDL_RenderDrawPoint(renderer, x, y);

    if(x == 0 && y % 2 == 0) {
        SDL_Event e;
        if( SDL_PollEvent(&e) && e.type == SDL_QUIT ) {
            exit(0);
        }
        
        SDL_UpdateWindowSurface(window);
    }
}

void render_camera_image(
    SDL_Window* window,
    SDL_Renderer* renderer, 
    std::function<const Color& (const Ray& ray)> calculate_ray_color
) {
    for(u_int image_y = 0; image_y < IMAGE_HEIGHT(); image_y ++) {
        for(u_int image_x = 0; image_x < IMAGE_WIDTH; image_x ++) {
            auto projected_pixel = PIXEL_0X0_PROJECTED_LOCATION 
                + (image_x * PIXEL_DELTA_HORIZONTAL)
                + (image_y * PIXEL_DELTA_VERTICAL);

            auto ray_direction = projected_pixel - CAMERA_CENTER;
            auto color = calculate_ray_color(Ray(CAMERA_CENTER, ray_direction));
            render_pixel(window, renderer, image_x, image_y, color);
        }
    }
}


int main() {
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;

    SDL_Event event;
    std::cout << "VIEWPORT" << "\n";
    std::cout << "WIDTH: " << VIEWPORT_WIDTH() << "\n";
    std::cout << "HEIGHT: " << VIEWPORT_HEIGHT << "\n";
    std::cout << "HORIZONTAL VECTOR: " << VIEWPORT_HORIZONTAL_VEC << "\n";
    std::cout << "VERTICAL VECTOR: " << VIEWPORT_VERTICAL_VEC << "\n";

    std::cout << "\n";
    std::cout << "PIXEL DELTA: (" << PIXEL_DELTA_HORIZONTAL << ", " << PIXEL_DELTA_VERTICAL << ")\n";

    window = SDL_CreateWindow(
        "rendering", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        IMAGE_WIDTH, 
        IMAGE_HEIGHT(), 
        SDL_WINDOW_SHOWN
    );

    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateSoftwareRenderer(surface);

    render_camera_image(
        window,
        renderer,
        simple_circle_color_fn
    );

    u_int counter = 0;
    while (true) {
        if(counter % 1000) {
            SDL_UpdateWindowSurface(window);
        }

        if( SDL_PollEvent(&event) && event.type == SDL_QUIT ) {
            SDL_Quit();
            return 0;
        }       

        counter ++;
    }

    return 0;
}