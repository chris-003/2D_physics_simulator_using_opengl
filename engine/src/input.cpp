#include "input.h"

namespace engine {
Modifier::Modifier(unsigned int mods) : flags(mods) {
}

bool Modifier::shift() const {
    return flags & GLFW_MOD_SHIFT != 0;
}

bool Modifier::control() const {
    return flags & GLFW_MOD_CONTROL != 0;
}

bool Modifier::alt() const {
    return flags & GLFW_MOD_ALT != 0;
}

bool Modifier::super() const {
    return flags & GLFW_MOD_SUPER != 0;
}

bool Modifier::capsLock() const {
    return flags & GLFW_MOD_CAPS_LOCK != 0;
}

bool Modifier::numLock() const {
    return flags & GLFW_MOD_NUM_LOCK != 0;
}
} // namespace engine