#include <complex>
#include "massspringsystem/vector.h"

namespace mss {
Vector::Vector(std::size_t dim) : m_coordinates(dim) {}

Vector::Vector(std::initializer_list<float> values) : m_coordinates(values) {}

void Vector::mult(float k) {
    for (float& coordinate: m_coordinates)
        coordinate *= k;
}

void Vector::add(Vector const& other) {
    for (std::size_t i = 0; i < m_coordinates.size(); i++)
        m_coordinates[i] += other.m_coordinates[i];
}

float Vector::length() const {
    float squaredLength = 0.f;

    for (float coordinate: m_coordinates)
        squaredLength += coordinate * coordinate;

    return std::sqrt(squaredLength);
}

void Vector::normalize() {
    float length = this->length();
    if (length < 0.0001f) return;
    this->mult(1.0f / length);
}

float Vector::at(std::size_t i) const {
    return m_coordinates[i];
}

Vector Vector::vectorFromPoints(Vector const& p1, Vector const& p2) {
    Vector res(p1.m_coordinates.size());

    for (std::size_t i = 0; i < p1.m_coordinates.size(); i++)
        res.m_coordinates[i] = p2.m_coordinates[i] - p1.m_coordinates[i];

    return res;
}
} // mss