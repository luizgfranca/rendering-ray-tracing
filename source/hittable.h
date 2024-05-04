#pragma once
#include "point3.h"
#include "ray.h"
#include "vec3.h"
#include <optional>

struct HitRecord {
    double t;
    Point3 point;
    Vec3 normal;
};

class Hittable {
    public:
        virtual ~Hittable() = default;
        virtual std::optional<HitRecord> hit(
            const Ray& ray,
            double ray_tmin,
            double ray_tmax
        ) const = 0;
};