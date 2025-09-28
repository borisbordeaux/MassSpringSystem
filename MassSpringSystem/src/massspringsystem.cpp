#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "massspringsystem/massspringsystem.h"

namespace mss {
MassSpringSystem::MassSpringSystem(std::size_t dim) : m_dim(dim) {}

void MassSpringSystem::addMass(float damping) {
    m_masses.emplace_back(m_dim, damping);
}

void MassSpringSystem::addMass(Vector const& pos) {
    m_masses.emplace_back(pos);
}

void MassSpringSystem::addSpring(std::size_t indexMass1, std::size_t indexMass2, float k, float length) {
    if (indexMass1 < m_masses.size() && indexMass2 < m_masses.size() && indexMass1 != indexMass2) {
        m_springs.emplace_back(m_masses[indexMass1], m_masses[indexMass2], k, length);
        m_springIndices.emplace_back(indexMass1, indexMass2);
    }
}

void MassSpringSystem::update() {
    for (Spring& s: m_springs)
        s.applyForces();

    for (Mass& m: m_masses)
        m.update();
}

void MassSpringSystem::clearSprings() {
    m_springs.clear();
    m_springIndices.clear();
}

void MassSpringSystem::clearMasses() {
    m_masses.clear();
}

void MassSpringSystem::clear(std::size_t newDim) {
    m_dim = newDim;
    this->clearSprings();
    this->clearMasses();
}

bool MassSpringSystem::loadFromDescription(std::istream& description) {
    std::string line;
    enum class LineType {
        ERROR, DIM, FIXED_MASS, RANDOM_MASS, SPRING
    };
    this->clear();
    while (std::getline(description, line)) {
        LineType type = LineType::ERROR;
        std::size_t wordIndex = 1; // the first word gives the type, so we initialize it to the second word
        // for fixed masses
        std::vector<float> coordinates;
        if (m_dim != 0) coordinates.reserve(m_dim);
        // for random masses
        int numberOfRandomMasses = 0;
        // for springs
        std::size_t indexM1 = 0;
        std::size_t indexM2 = 0;
        float k = 0.0f;

        std::istringstream iss(line);
        std::string word;
        while (std::getline(iss, word, ' ') && word != "#") {
            // update type of line
            if (word == "d") {
                type = LineType::DIM;
            } else if (word == "m") {
                type = LineType::FIXED_MASS;
                continue;
            } else if (word == "n") {
                type = LineType::RANDOM_MASS;
                continue;
            } else if (word == "s") {
                type = LineType::SPRING;
                continue;
            } else {
                // make sure first line type is dimension
                if (m_dim == 0 && type != LineType::DIM) {
                    return false;
                }
                // process words depending on the type of line
                try {
                    switch (type) {
                        case LineType::ERROR:
                            this->clear();
                            return false;
                        case LineType::DIM: {
                            int d = std::stoi(word);
                            if (d > 1) {
                                m_dim = static_cast<std::size_t>(d);
                            } else {
                                this->clear();
                                return false;
                            }
                            break;
                        }
                        case LineType::FIXED_MASS: {
                            coordinates.push_back(std::stof(word));
                            if (wordIndex == m_dim) { // damping parameter
                                this->addMass(mss::Vector(coordinates));
                            }
                            break;
                        }
                        case LineType::RANDOM_MASS: {
                            if (wordIndex == 1) { // number of random masses
                                numberOfRandomMasses = std::stoi(word);
                            } else if (wordIndex == 2) {
                                float damping = std::stof(word);
                                for (int i = 0; i < numberOfRandomMasses; i++)
                                    this->addMass(damping);
                            }
                            break;
                        }
                        case LineType::SPRING: {
                            switch (wordIndex) {
                                case 1: {
                                    int index1 = std::stoi(word);
                                    if (index1 >= 0) {
                                        indexM1 = static_cast<std::size_t>(index1);
                                    }
                                    break;
                                }
                                case 2: {
                                    int index2 = std::stoi(word);
                                    if (index2 >= 0) {
                                        indexM2 = static_cast<std::size_t>(index2);
                                    }
                                    break;
                                }
                                case 3: {
                                    k = std::stof(word);
                                    break;
                                }
                                case 4: {
                                    float l = std::stof(word);
                                    this->addSpring(indexM1, indexM2, k, l);
                                    break;
                                }
                                default: {
                                    this->clear();
                                    return false;
                                }
                            }
                        }
                    }
                }
                catch (std::exception const& ex) {
                    std::cout << "#1: " << ex.what() << '\n';
                    this->clear();
                    return false;
                }
            }
            wordIndex++;
        }
    }

    return true;
}

bool MassSpringSystem::loadFromFile(std::string const& filepath) {
    std::ifstream ifs(filepath.c_str());
    if (ifs.is_open()) {
        return this->loadFromDescription(ifs);
    } else {
        return false;
    }
}

bool MassSpringSystem::loadFromString(std::string const& description) {
    std::istringstream iss(description);
    return this->loadFromDescription(iss);
}

std::string MassSpringSystem::toString() const {
    std::string res;
    res = "d " + std::to_string(m_dim);
    for (mss::Mass const& m: m_masses) {
        if (m.fixed()) {
            res += "\nm";
            for (std::size_t i = 0; i < m_dim; i++) {
                res += " " + MassSpringSystem::toString(m.position().at(i));
            }
        } else {
            res += "\nn 1 " + MassSpringSystem::toString(m.damping());
        }
    }
    for (std::size_t i = 0; i < m_springs.size(); i++) {
        res += "\ns ";
        res += std::to_string(m_springIndices[i].first);
        res += " " + std::to_string(m_springIndices[i].second);
        res += " " + MassSpringSystem::toString(m_springs[i].k());
        res += " " + MassSpringSystem::toString(m_springs[i].length());
    }
    return res;
}

std::string MassSpringSystem::toString(float value) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(4) << value;
    std::string res = stream.str();
    std::replace(res.begin(), res.end(), ',', '.');
    return res;
}
} // mss