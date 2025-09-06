#ifndef MASSSPRINGSYSTEM_VECTOR_H
#define MASSSPRINGSYSTEM_VECTOR_H

#include <vector>
#include <random>

namespace mss {

class Vector {
public:
    explicit Vector(std::size_t dim, bool randomize = false);
    Vector(std::initializer_list<float> values);
    explicit Vector(std::vector<float> const& values);

    void mult(float k);
    void add(Vector const& other);
    [[nodiscard]] float length() const;
    void normalize();

    [[nodiscard]] inline float at(std::size_t i) const { return m_coordinates[i]; }

    [[nodiscard]] inline float& at(std::size_t i) { return m_coordinates[i]; }

    [[nodiscard]] inline std::size_t dim() const { return m_coordinates.size(); }

public:
    static Vector vectorFromPoints(Vector const& p1, Vector const& p2);

private:
    std::vector<float> m_coordinates;

private:
    static std::random_device rd;
    static std::mt19937 generator;
    static std::uniform_real_distribution<float> distribution;
};

} // mss

#endif //MASSSPRINGSYSTEM_VECTOR_H
