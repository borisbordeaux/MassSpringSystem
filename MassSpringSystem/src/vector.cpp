#include <complex>
#include "massspringsystem/vector.h"

namespace mss {

std::random_device Vector::rd;
std::mt19937 Vector::generator(rd());
std::uniform_real_distribution<float> Vector::distribution(0.0f, 0.25f);

Vector::Vector(std::size_t dim, bool randomize) : m_coordinates(dim) {
    if (randomize) {
        m_coordinates[dim - 1] = 1.0f;
        for (std::size_t i = 0; i < dim - 1; i++) {
            m_coordinates[i] = distribution(generator);
            m_coordinates[dim - 1] -= m_coordinates[i];
        }
    }
}

Vector::Vector(std::initializer_list<float> values) : m_coordinates(values) {}

Vector::Vector(std::vector<float> const& values) : m_coordinates(values) {}

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

Vector Vector::vectorFromPoints(Vector const& p1, Vector const& p2) {
    Vector res(p1.m_coordinates.size());

    for (std::size_t i = 0; i < p1.m_coordinates.size(); i++)
        res.m_coordinates[i] = p2.m_coordinates[i] - p1.m_coordinates[i];

    return res;
}
} // mss