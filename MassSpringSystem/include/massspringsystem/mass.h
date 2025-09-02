#ifndef MASSSPRINGSYSTEM_MASS_H
#define MASSSPRINGSYSTEM_MASS_H

#include "massspringsystem/vector.h"

namespace mss {

class Mass {
public:
    explicit Mass(std::size_t dim, float damping);
    Mass(Vector const& pos, bool fixed, float damping);

    void applyForce(Vector const& force);
    void update();

    [[nodiscard]] inline Vector const& position() const { return m_pos; }

    [[nodiscard]] inline bool fixed() const { return m_fixed; }

private:
    Vector m_pos;
    bool m_fixed;
    Vector m_velocity;
    Vector m_acceleration;
    float m_damping;
};

} // mss

#endif //MASSSPRINGSYSTEM_MASS_H
