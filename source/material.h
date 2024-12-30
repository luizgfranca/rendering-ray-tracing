#pragma once

#include "common.h"
#include "color.h"
#include "hit-record.h"
#include "hit-record.h"
#include "ray.h"
#include <optional>

class HitRecord;

typedef struct scattering {
    Color attenuation;
    Ray scattered;
} scattering;

class Material {
public:
    virtual ~Material() = default;
    
    virtual std::optional<scattering> scatter(
        const Ray& input_ray, 
        const HitRecord& record
    ) const { return std::nullopt; }
};