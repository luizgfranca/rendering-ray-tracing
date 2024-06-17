#include "vec3.h"

double Vec3::length_squared() const {
    return data[0]*data[0] + data[1]*data[1] + data[2]*data[2];
}
double Vec3::length() const {
    return std::sqrt(length_squared());
}

double Vec3::dot(const Vec3& v, const Vec3& u) {
    return v[0] * u[0] + v[1] * u[1] + v[2] * u[2];
}

Vec3 Vec3::cross(const Vec3& v, const Vec3& u) {
    return Vec3(
        v[1] * u[2] - v[2] * u[1],
        v[0] * u[2] - v[2] * u[0],
        v[0] * u[1] - v[1] * u[0]
    );
}

Vec3 Vec3::unit_vector(const Vec3& v) {
    return v / v.length();
}

Vec3 Vec3::random() { return Vec3(get_random(), get_random(), get_random()); }

Vec3 Vec3::random(double min, double max) { 
    return Vec3(
        get_random(min, max), 
        get_random(min, max), 
        get_random(min, max)
    ); 
}

Vec3 Vec3::unit_sphere_random() {
    Vec3 candidate;

    do {
        candidate = Vec3::random(-1, 1);
    } while(candidate.length_squared() >= 1);

    return candidate;
}

Vec3 Vec3::unit_random() {
    return Vec3::unit_vector(unit_sphere_random());
}