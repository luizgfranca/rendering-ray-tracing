#pragma once
#include "ray.h"
#include <optional>
#include "hit-record.h"
class Hittable {
    public:
        virtual ~Hittable() = default;
        virtual std::optional<HitRecord> hit(
            const Ray& ray,
            double ray_tmin,
            double ray_tmax
        ) const = 0;
};