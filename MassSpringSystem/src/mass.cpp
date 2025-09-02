#include "massspringsystem/mass.h"

namespace mss {
Mass::Mass(std::size_t dim, float damping) : m_pos(dim), m_fixed(false), m_velocity(dim), m_acceleration(dim), m_damping(damping) {}

Mass::Mass(Vector const& pos, bool fixed, float damping) : m_pos(pos), m_fixed(fixed), m_velocity(pos.dim()), m_acceleration(pos.dim()), m_damping(damping) {}

void Mass::applyForce(Vector const& force) {
    if (!m_fixed)
        m_acceleration.add(force);
}

void Mass::update() {
    m_velocity.mult(m_damping); // damping system
    m_velocity.add(m_acceleration);
    m_pos.add(m_velocity);
    m_acceleration.mult(0.f);
}
} // mss