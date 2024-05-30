#pragma once
#include "color.h"
#include "common.h"
#include "point3.h"
#include "ray.h"
#include "vec3.h"
#include <cmath>
#include <sys/types.h>


class Camera {
    public:
        Camera(
            SDL_Window* window,
            SDL_Renderer* renderer,
            u_int image_width, 
            double aspect_ratio, 
            double viewport_height,
            double focal_length,
            const Point3& camera_center
        ):
            m_window(window),
            m_renderer(renderer),
            m_image_width(image_width),
            m_aspect_ratio(aspect_ratio),
            m_viewport_height(viewport_height),
            m_focal_length(focal_length),
            m_camera_center(camera_center)
        {
            initialize();
        }

        void render(const Hittable& environment) const {
            for(u_int image_y = 0; image_y < m_image_height; image_y ++) {
                for(u_int image_x = 0; image_x < m_image_width; image_x ++) {
                    auto projected_pixel = m_0x0_pixel_location 
                        + (image_x * m_horizontal_pixel_delta)
                        + (image_y * m_vertical_pixel_delta);

                    auto ray_direction = projected_pixel - m_camera_center;
                    auto color = get_calculated_ray_color(
                        Ray(m_camera_center, ray_direction), 
                        environment
                    );

                    render_pixel(image_x, image_y, color);
                }
            }
        }

    private:
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;

        // provided
        double m_aspect_ratio;
        u_int m_image_width;
        double m_viewport_height;
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

        void initialize() {
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

        Color get_calculated_ray_color(const Ray& ray, const Hittable& environment) const {
            auto unit_direction = vec_op::unit_vector(ray.direction());
            
            auto hit_interval = Interval(0, INFINITY);
            auto maybe_ray_hit = environment.hit(ray, hit_interval);
            if(maybe_ray_hit.has_value()) {
                auto hit = maybe_ray_hit.value();
                return Color::from(0.5 * (hit.normal() + Vec3(1,1,1)));
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
};