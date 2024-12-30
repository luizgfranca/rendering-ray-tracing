

#include "color.h"
#include "hit-record.h"
#include "material.h"
#include "ray.h"
#include "vec3.h"
class Lambertian : public Material {

public:
    Lambertian(const Color& albedo) : m_albedo(albedo) {}

    virtual std::optional<scattering> scatter(
        const Ray& input_ray, 
        const HitRecord& record
    ) const { 
        auto direction = record.normal() + Vec3::unit_random();
        if(direction.is_practical_zero()) {
            direction = record.normal();
        }
        
        auto scattered = Ray(record.point(), direction);
        return scattering{
            m_albedo,
            scattered
        };
    }

private:
    Color m_albedo;
};