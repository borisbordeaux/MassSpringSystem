#include "massspringsystem/spring.h"
#include "massspringsystem/vector.h"
#include "massspringsystem/mass.h"

namespace mss {
Spring::Spring(Mass& m1, Mass& m2, float k, float length) : m_m1(m1), m_m2(m2), m_k(k), m_length(length) {}

void Spring::applyForces() {
    Vector direction = Vector::vectorFromPoints(m_m1.position(), m_m2.position());
    float x = direction.length() - m_length;
    direction.normalize();
    direction.mult(m_k * x);
    m_m1.applyForce(direction);
    direction.mult(-1.f);
    m_m2.applyForce(direction);
}
} // mss