#ifndef MASSSPRINGSYSTEM_SYSTEM_H
#define MASSSPRINGSYSTEM_SYSTEM_H

#include <vector>

#include "massspringsystem/mass.h"
#include "massspringsystem/spring.h"

namespace mss {

class Vector;

class MassSpringSystem {
public:
    MassSpringSystem(std::size_t dim, float damping);

    void addMass();
    void addMass(Vector const& pos, bool fixed = false);
    void addSpring(std::size_t indexMass1, std::size_t indexMass2, float k, float length);
    void update();
    void clearSprings();
    void clearMasses();
    void clear();
    void setDamping(float damping);

    inline std::vector<Mass> const& masses() const { return m_masses; }

    inline std::vector<Mass>& masses() { return m_masses; }

    inline std::vector<Spring> const& springs() const { return m_springs; }

    inline std::vector<Spring>& springs() { return m_springs; }

private:
    std::vector<Mass> m_masses;
    std::vector<Spring> m_springs;
    std::size_t m_dim;
    float m_damping;
};

} // mss

#endif //MASSSPRINGSYSTEM_SYSTEM_H
