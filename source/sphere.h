#pragma once
#include "common.h"

#include "hit-record.h"
#include "hittable.h"
#include "point3.h"
#include "ray.h"
#include "vec3.h"

class Sphere : public Hittable {
    public:
        Sphere(Point3 center, double radius): m_center(center), m_radius(radius) {};

        std::optional<HitRecord> hit(
            const Ray& ray,
            double ray_tmin,
            double ray_tmax
        ) const override{
            auto diff_origin_center = m_center - ray.origin();
            
            auto a = vec_op::dot(ray.direction(), ray.direction());
            
            // auto b = -2 * vec_op::dot(ray.direction(), diff_origin_center);
            // b = -2h -> h = b / -2 -> d * (C - Q)
            auto h = vec_op::dot(ray.direction(), diff_origin_center);

            auto c = vec_op::dot(diff_origin_center, diff_origin_center) - (m_radius * m_radius);

            // auto discriminator = (b * b) - (4 * a * c);
            // h = -2b so
            auto discriminant = (h * h) - (a * c);
            if(discriminant < 0) {
                return std::nullopt;
            }
            
            auto discriminant_sqrt = std::sqrt(discriminant );
            auto root = ( h - discriminant_sqrt ) / a;
            if(root <= ray_tmin || root >= ray_tmax) {
                root = ( h + discriminant_sqrt ) / a;
                if(root <= ray_tmin || root >= ray_tmax) {
                    return std::nullopt;
                }
            }

            HitRecord hit_record(
                root, 
                ray.at(root)
            );

            hit_record.set_face_normal(ray, diff_origin_center / m_radius);

            return hit_record;
        }
    private:
        Point3 m_center;
        double m_radius;
};