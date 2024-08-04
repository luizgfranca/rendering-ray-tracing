#pragma once

#include "point3.h"
#include "ray.h"
#include "vec3.h"
#include <memory>

class Material;

class HitRecord {
    public:
        HitRecord(
            double t,
            Point3 point,
            Vec3 normal,
            std::shared_ptr<Material> material
        ): 
            m_t(t),
            m_point(point),
            m_normal(normal),
            m_material(material)
        {}

        HitRecord(
            double t,
            Point3 point,
            Vec3 normal
        ): 
            m_t(t),
            m_point(point),
            m_normal(normal)
        {}

        HitRecord(
            double t,
            Point3 point,
            std::shared_ptr<Material> material
        ): m_t(t), m_point(point), m_material(material) {}

        HitRecord(
            double t,
            Point3 point
        ): m_t(t), m_point(point) {}

    double t() const { return m_t; }
    const Point3& point() const { return m_point; } 
    const Vec3& normal() const { return m_normal; } 
    std::shared_ptr<Material> material() const { return m_material; }


    void set_face_normal(const Ray& ray, const Vec3& outward_normal) {
        m_front_face = Vec3::dot(ray.direction(), outward_normal) < 0;
        m_normal = m_front_face ? outward_normal : -outward_normal;
    }

    private:    
        double m_t;
        Point3 m_point;
        Vec3 m_normal;
        bool m_front_face;
        std::shared_ptr<Material> m_material;
};