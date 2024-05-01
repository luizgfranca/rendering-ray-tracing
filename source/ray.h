#pragma once

#include "point3.h"

class Ray {
public:
    Ray(const Point3& origin, const Vec3& direction): 
        m_origin(origin), 
        m_direction(direction) {};

    const Point3& origin() const { return m_origin; }
    const Vec3& direction() const { return m_direction; }

    Point3 at(double t) const {
        auto result = m_origin + (t * m_direction);
        return *static_cast<Point3*>(&result);
    }
private:
    Point3 m_origin;
    Vec3 m_direction;
};