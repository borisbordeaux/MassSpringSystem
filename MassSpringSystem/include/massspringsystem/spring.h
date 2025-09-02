#ifndef MASSSPRINGSYSTEM_SPRING_H
#define MASSSPRINGSYSTEM_SPRING_H

namespace mss {

class Mass;

class Spring {
public:
    Spring(Mass& m1, Mass& m2, float k, float length);

    void applyForces();

    inline Mass const& m1() const { return m_m1; }

    inline Mass const& m2() const { return m_m2; }

private:
    Mass& m_m1;
    Mass& m_m2;
    float m_k;
    float m_length;
};

} // mss

#endif //MASSSPRINGSYSTEM_SPRING_H
