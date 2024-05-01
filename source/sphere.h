#pragma once

#include <cmath>

#include "point3.h"
#include "ray.h"
#include "vec3.h"


typedef struct sphere {
    Point3 center;
    double radius;
} sphere;


namespace sphere_op {
    inline double hit_sphere(const sphere& s, const Ray& ray) {
        auto diff_origin_center = s.center - ray.origin();
        
        auto a = vec_op::dot(ray.direction(), ray.direction());
        
        // auto b = -2 * vec_op::dot(ray.direction(), diff_origin_center);
        // b = -2h -> h = b / -2 -> d * (C - Q)
        auto h = vec_op::dot(ray.direction(), diff_origin_center);

        auto c = vec_op::dot(diff_origin_center, diff_origin_center) - (s.radius * s.radius);

        // auto discriminator = (b * b) - (4 * a * c);
        // h = -2b so
        auto discriminator = (h * h) - (a * c);
        
        if(discriminator < 0) {
            return -1;
        }
        
        return ( h - std::sqrt(discriminator ) ) / a;
    }
}
