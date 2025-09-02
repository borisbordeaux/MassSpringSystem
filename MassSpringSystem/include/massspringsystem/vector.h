#ifndef MASSSPRINGSYSTEM_VECTOR_H
#define MASSSPRINGSYSTEM_VECTOR_H

#include <vector>

namespace mss {

class Vector {
public:
    explicit Vector(std::size_t dim);

    Vector(std::initializer_list<float> values);

    void mult(float k);
    void add(Vector const& other);
    [[nodiscard]] float length() const;
    void normalize();

    [[nodiscard]] float at(std::size_t i) const;

    [[nodiscard]] inline std::size_t dim() const { return m_coordinates.size(); }

public:
    static Vector vectorFromPoints(Vector const& p1, Vector const& p2);

private:
    std::vector<float> m_coordinates;
};

} // mss

#endif //MASSSPRINGSYSTEM_VECTOR_H
