#pragma once

#include <string>

#include <glm/glm.hpp>
#include <bandit/assertion_frameworks/snowhouse/snowhouse/stringize.h>

#include "tostring.h"

// adds vec3 support to bandit

bool operator>=(const glm::vec3 &a, const glm::vec3 &b);

bool operator<=(const glm::vec3 &a, const glm::vec3 &b);

namespace snowhouse {
    template<>
    struct snowhouse::Stringizer<glm::vec3>
    {
        static std::string ToString(const glm::vec3& value) {
            return toString(value);
        }
    };
}
