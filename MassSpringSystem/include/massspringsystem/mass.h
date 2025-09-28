#ifndef MASSSPRINGSYSTEM_MASS_H
#define MASSSPRINGSYSTEM_MASS_H

#include "massspringsystem/vector.h"

namespace mss {

class Mass {
public:
    explicit Mass(std::size_t dim, float damping);
    explicit Mass(Vector const& pos);

    void applyForce(Vector const& force);
    void update();

    void setFixed(bool fixed) { m_fixed = fixed; }

    [[nodiscard]] inline Vector const& position() const { return m_pos; }

    [[nodiscard]] inline Vector& position() { return m_pos; }

    [[nodiscard]] inline bool fixed() const { return m_fixed; }

    [[nodiscard]] inline float damping() const { return m_damping; }

private:
    Vector m_pos;
    bool m_fixed;
    Vector m_velocity;
    Vector m_acceleration;
    float m_damping;
};

} // mss

#endif //MASSSPRINGSYSTEM_MASS_H
