#pragma once

#include "common.h"

#include "hit-record.h"
#include "hittable.h"


class HittableList : public Hittable {
    public:
        void clear() { m_objects.clear(); }
        void add(std::shared_ptr<Hittable> object) {
            m_objects.push_back(object);
        }

        std::optional<HitRecord> hit(
            const Ray& ray,
            double ray_tmin,
            double ray_tmax
        ) const override{
            std::optional<HitRecord> result = std::nullopt;
            bool has_hit_anything = false;
            double closest_hit_t = ray_tmax;

            for(const auto& object : m_objects) {
                auto maybe_hit = object->hit(ray, ray_tmin, closest_hit_t);
                if(maybe_hit.has_value()) {
                    has_hit_anything = true;
                    closest_hit_t = maybe_hit->t();
                    result = maybe_hit;
                }
            }

            return result;
        }
    private:
        std::vector<std::shared_ptr<Hittable>> m_objects;
};