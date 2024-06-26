#pragma once
#include "common.h"

#include "interval.h"
#include "ray.h"
#include "hit-record.h"
class Hittable {
    public:
        virtual ~Hittable() = default;
        virtual std::optional<HitRecord> hit(
            const Ray& ray,
            Interval t_interval
        ) const = 0;
};