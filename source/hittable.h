#pragma once
#include "common.h"

#include "ray.h"
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