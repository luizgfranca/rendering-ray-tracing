#pragma once
#include "common.h"

#include "hit-record.h"
#include "hittable.h"
#include "interval.h"
#include "point3.h"
#include "ray.h"
#include "vec3.h"
#include <memory>

class Sphere : public Hittable {
    public:
        Sphere(Point3 center, double radius, std::shared_ptr<Material> material): 
            m_center(center), 
            m_radius(radius),
            m_material(material) {};

        std::optional<HitRecord> hit(
            const Ray& ray,
            Interval interval
        ) const override{
            auto diff_origin_center = m_center - ray.origin();
            
            auto a = ray.direction().length_squared();
            
            // auto b = -2 * Vec3::dot(ray.direction(), diff_origin_center);
            // b = -2h -> h = b / -2 -> d * (C - Q)
            auto h = Vec3::dot(ray.direction(), diff_origin_center);

            auto c = diff_origin_center.length_squared() - (m_radius * m_radius);

            // auto discriminator = (b * b) - (4 * a * c);
            // h = -2b so
            auto discriminant = (h * h) - (a * c);
            if(discriminant <= 0) {
                return std::nullopt;
            }
            
            auto discriminant_sqrt = std::sqrt(discriminant );
            auto root = ( h - discriminant_sqrt ) / a;

            if(!interval.contains(root)) {
                root = ( h + discriminant_sqrt ) / a;
                if(!interval.contains(root)) {
                    return std::nullopt;
                }
            }

            HitRecord hit_record(
                root, 
                ray.at(root),
                m_material
            );

            hit_record.set_face_normal(ray, (hit_record.point() - m_center) / m_radius);

            return hit_record;
        }
    private:
        Point3 m_center;
        double m_radius;
        std::shared_ptr<Material> m_material;
};