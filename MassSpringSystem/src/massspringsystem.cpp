#include "massspringsystem/massspringsystem.h"

namespace mss {
MassSpringSystem::MassSpringSystem(std::size_t dim, float damping) : m_dim(dim), m_damping(damping) {}

void MassSpringSystem::addMass() {
    m_masses.emplace_back(m_dim, m_damping);
}

void MassSpringSystem::addMass(Vector const& pos, bool fixed) {
    m_masses.emplace_back(pos, fixed, m_damping);
}

void MassSpringSystem::addSpring(std::size_t indexMass1, std::size_t indexMass2, float k, float length) {
    if (indexMass1 < m_masses.size() && indexMass2 < m_masses.size() && indexMass1 != indexMass2)
        m_springs.emplace_back(m_masses[indexMass1], m_masses[indexMass2], k, length);
}

void MassSpringSystem::update() {
    for (Spring& s: m_springs)
        s.applyForces();

    for (Mass& m: m_masses)
        m.update();
}

void MassSpringSystem::clearSprings() {
    m_springs.clear();
}

void MassSpringSystem::clearMasses() {
    m_masses.clear();
}

void MassSpringSystem::clear() {
    this->clearSprings();
    this->clearMasses();
}

void MassSpringSystem::setDamping(float damping) {
    m_damping = damping;
}
} // mss