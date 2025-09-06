#include "massspringsystem/mass.h"

namespace mss {
Mass::Mass(std::size_t dim, float damping) : m_pos(dim, true), m_fixed(false), m_velocity(dim), m_acceleration(dim), m_damping(damping) {}

Mass::Mass(Vector const& pos) : m_pos(pos), m_fixed(true), m_velocity(pos.dim()), m_acceleration(pos.dim()), m_damping(0.0f) {}

void Mass::applyForce(Vector const& force) {
    if (!m_fixed)
        m_acceleration.add(force);
}

void Mass::update() {
    if (!m_fixed) {
        m_velocity.mult(m_damping); // damping system
        m_velocity.add(m_acceleration);
        m_pos.add(m_velocity);
        m_acceleration.mult(0.f);
    }
}
} // mss