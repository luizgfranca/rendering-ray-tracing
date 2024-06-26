#pragma once
#include "common.h"
#include "color.h"
#include "point3.h"
#include "ray.h"
#include "vec3.h"
#include "hittable.h"
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_surface.h>
#include <cstdlib>
#include <sys/types.h>

constexpr u_int MAX_DEPTH = 5;

class Camera {
    public:
        Camera(
            u_int image_width, 
            double aspect_ratio, 
            double viewport_height,
            double samples_per_pixel,
            double focal_length,
            const Point3& camera_center
        ):
            m_image_width(image_width),
            m_aspect_ratio(aspect_ratio),
            m_viewport_height(viewport_height),
            m_samples_per_pixel(samples_per_pixel),
            m_focal_length(focal_length),
            m_camera_center(camera_center)
        {
            initialize_properties();
            initialize_sdl();
        }

        ~Camera() {
            free(m_window);
            free(m_surface);
            free(m_renderer);

            SDL_Quit();
        }

        void render_and_wait(const Hittable& environment) const {
            for(u_int image_y = 0; image_y < m_image_height; image_y ++) {
                for(u_int image_x = 0; image_x < m_image_width; image_x ++) {
                    auto projected_center = m_0x0_pixel_location 
                        + (image_x * m_horizontal_pixel_delta)
                        + (image_y * m_vertical_pixel_delta);
                    
                    Vec3 sample_total;
                    for(auto sample = 0; sample < m_samples_per_pixel; sample ++) {
                        auto ray = get_random_ray_close_to_projection(projected_center);

                        auto sample_color = get_calculated_ray_color(
                            ray, 
                            environment
                        );

                        sample_total += sample_color;
                    }

                    sample_total = sample_total / m_samples_per_pixel;
                    auto calculated_color = Color(sample_total);
                    render_pixel(image_x, image_y, calculated_color);
                }
            }

            u_int counter = 0;
            SDL_Event e;
            while (true) {
                if(counter % 1000) {
                    SDL_UpdateWindowSurface(m_window);
                }

                if( SDL_PollEvent(&e) && e.type == SDL_QUIT ) {
                    return;
                }       

                counter ++;
            }
        }

    private:
        // SDL stuff
        SDL_Window* m_window;
        SDL_Surface* m_surface;
        SDL_Renderer* m_renderer;
        
        // provided
        double m_aspect_ratio;
        u_int m_image_width;
        double m_viewport_height;
        const u_int m_samples_per_pixel;
        double m_focal_length;
        const Point3& m_camera_center;

        // calculated
        u_int m_image_height;
        double m_viewport_width;

        Vec3 m_viewport_horizontal_axis;
        Vec3 m_viewport_vertical_axis;
        Vec3 m_horizontal_pixel_delta;
        Vec3 m_vertical_pixel_delta;

        Point3 m_viewport_upper_left;
        
        Point3 m_0x0_pixel_location;

        void initialize_properties() {
            auto height = u_int(m_image_width / m_aspect_ratio);
            m_image_height = height < 1 ? 1 : height;
            
            m_viewport_width = m_viewport_height * (double(m_image_width) / double(m_image_height));

            m_viewport_horizontal_axis = Vec3(m_viewport_width, 0, 0);
            m_viewport_vertical_axis = Vec3(0, -m_viewport_height, 0);

            m_horizontal_pixel_delta = m_viewport_horizontal_axis / m_image_width;
            m_vertical_pixel_delta = m_viewport_vertical_axis / m_image_height;

            m_viewport_upper_left =  *static_cast<Point3*>(
                new Vec3(
                    m_camera_center 
                    - Vec3(0, 0, m_focal_length) 
                    - (m_viewport_horizontal_axis / 2)
                    - (m_viewport_vertical_axis / 2)
                )
            );

            m_0x0_pixel_location = *static_cast<Point3*>(
                new Vec3(
                    m_viewport_upper_left
                    + (0.5 * (m_horizontal_pixel_delta + m_vertical_pixel_delta))
                )
            );
        }

        void initialize_sdl() {
            SDL_Init(SDL_INIT_EVERYTHING);

            m_window = SDL_CreateWindow(
                "rendering", 
                SDL_WINDOWPOS_UNDEFINED, 
                SDL_WINDOWPOS_UNDEFINED, 
                m_image_width, 
                m_image_height, 
                SDL_WINDOW_SHOWN
            );      

            m_surface = SDL_GetWindowSurface(m_window);
            m_renderer = SDL_CreateSoftwareRenderer(m_surface);
        }

        Color get_calculated_ray_color(const Ray& ray, const Hittable& environment, u_int depth = 0) const {
            auto unit_direction = Vec3::unit_vector(ray.direction());
            
            auto hit_interval = Interval(0, INFINITY);
            auto maybe_ray_hit = environment.hit(ray, hit_interval);
            if(maybe_ray_hit.has_value() && depth <= MAX_DEPTH) {
                auto hit = maybe_ray_hit.value();

                auto reflection_direction = Vec3::unit_random_in_another_vector_hemisphere(hit.normal());
                auto reflection_ray = Ray(hit.point(), reflection_direction);

                auto reflection_color = get_calculated_ray_color(reflection_ray, environment, ++depth);
                return Color::from(0.7 * reflection_color);
            }

            auto a = 0.5 * (unit_direction.y() + 1);
            auto blended = linear_interpolation(
                Color(1, 1, 1), 
                Color(0.2, 0.5, 1), 
                a
            );

            return *static_cast<Color*>(&blended);
        }

        void render_pixel(u_int x, u_int y, const Color& color) const {
            color.set_render_color(m_renderer);
            SDL_RenderDrawPoint(m_renderer, x, y);

            if(x == 0 && y % 2 == 0) {
                SDL_Event e;
                if( SDL_PollEvent(&e) && e.type == SDL_QUIT ) {
                    exit(0);
                }
                
                SDL_UpdateWindowSurface(m_window);
            }
        }

        Ray get_random_ray_close_to_projection(Vec3 deviation_center) const {
            auto max_horizontal_deviation = m_horizontal_pixel_delta * 0.5;
            auto max_vertical_deviation = m_vertical_pixel_delta * 0.5;
            
            auto random_deviation = (m_horizontal_pixel_delta * get_random(-0.5, 0.5))
                + (m_vertical_pixel_delta * get_random(-0.5, 0.5));
            
            return Ray(
                m_camera_center,
                (deviation_center + random_deviation) - m_camera_center
            );
        }
};