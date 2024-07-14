#include <SDL2/SDL_render.h>
#include <SDL_events.h>
#include <SDL_surface.h>
#include <SDL_video.h>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <SDL2/SDL.h>
#include <memory>
#include <sys/types.h>
#include "color.h"
#include "hittable-list.h"
#include "hittable.h"
#include "point3.h"
#include "sphere.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"

constexpr double ASPECT_RATIO = 16.0 / 9.0;
constexpr u_int IMAGE_WIDTH = 800;
constexpr double VIEWPORT_HEIGHT = 2;
constexpr u_int SAMPLES_PER_PIXEL = 25;

const Point3 CAMERA_CENTER(0, 0, 0);
constexpr double FOCAL_LENGTH = 1;


const std::shared_ptr<Sphere> SIMPLE_SPHERE = std::make_shared<Sphere>(
    Point3(0, 0, -1),
    0.5
);

const std::shared_ptr<Sphere> ANOTHER_SPHERE = std::make_shared<Sphere>(
    Point3(0.2, 0, -0.8),
    0.5
);


const std::shared_ptr<Sphere> PLATFORM_SPHERE = std::make_shared<Sphere>(
    Point3(0, -100.5, -1),
    100
);



HittableList g_environment = HittableList();

int main() {
    g_environment.add(static_cast<std::shared_ptr<Hittable>>(SIMPLE_SPHERE.get()));
    g_environment.add(static_cast<std::shared_ptr<Hittable>>(PLATFORM_SPHERE.get()));

    auto camera = new Camera(
        IMAGE_WIDTH,
        ASPECT_RATIO,
        VIEWPORT_HEIGHT,
        SAMPLES_PER_PIXEL,
        FOCAL_LENGTH,
        CAMERA_CENTER
    );

    camera->render_and_wait(g_environment);

    return 0;
}