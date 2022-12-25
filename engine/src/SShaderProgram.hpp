#pragma once

namespace engine {
template<typename... T>
requires(std::is_convertible_v<T, SShader> &&...)
    SShaderProgram::SShaderProgram(const T &...shaders) {
    m_program = glCreateProgram();
    attach(shaders...);
    // glAttachShader(m_program, vert.shader());
    // glAttachShader(m_program, frag.shader());
    glLinkProgram(m_program);
}

template<typename T, size_t _size>
requires(in_type_list_v<T, float, int, double, unsigned int> && 1 <= _size &&
         _size <= 4) void SShaderProgram::setUniform(GLint location,
                                                     std::array<T, _size> &&v) {
    if constexpr (std::is_same_v<T, float>) {
        if constexpr (_size == 1) {
            glUniform1f(location, v[0]);
        }
        if constexpr (_size == 2) {
            glUniform2f(location, v[0], v[1]);
        }
        if constexpr (_size == 3) {
            glUniform3f(location, v[0], v[1], v[2]);
        }
        if constexpr (_size == 4) {
            glUniform4f(location, v[0], v[1], v[2], v[3]);
        }
    }
    if constexpr (std::is_same_v<T, int>) {
        if constexpr (_size == 1) {
            glUniform1i(location, v[0]);
        }
        if constexpr (_size == 2) {
            glUniform2i(location, v[0], v[1]);
        }
        if constexpr (_size == 3) {
            glUniform3i(location, v[0], v[1], v[2]);
        }
        if constexpr (_size == 4) {
            glUniform4i(location, v[0], v[1], v[2], v[3]);
        }
    }
    if constexpr (std::is_same_v<T, double>) {
        if constexpr (_size == 1) {
            glUniform1d(location, v[0]);
        }
        if constexpr (_size == 2) {
            glUniform2d(location, v[0], v[1]);
        }
        if constexpr (_size == 3) {
            glUniform3d(location, v[0], v[1], v[2]);
        }
        if constexpr (_size == 4) {
            glUniform4d(location, v[0], v[1], v[2], v[3]);
        }
    }
    if constexpr (std::is_same_v<T, unsigned int>) {
        if constexpr (_size == 1) {
            glUniform1ui(location, v[0]);
        }
        if constexpr (_size == 2) {
            glUniform2ui(location, v[0], v[1]);
        }
        if constexpr (_size == 3) {
            glUniform3ui(location, v[0], v[1], v[2]);
        }
        if constexpr (_size == 4) {
            glUniform4ui(location, v[0], v[1], v[2], v[3]);
        }
    }
}

template<typename T, typename... Args>
requires(in_type_list_v<T, float, int, double, unsigned int> &&
         1 <= sizeof...(Args) && sizeof...(Args) <= 4 &&
         (std::is_convertible_v<Args, T> &&
          ...)) void SShaderProgram::setUniform(GLint location,
                                                Args &&...args) {
    static constexpr size_t _size = sizeof...(Args);
    if constexpr (std::is_same_v<T, float>) {
        if constexpr (_size == 1) {
            glUniform1f(location, args...);
        }
        if constexpr (_size == 2) {
            glUniform2f(location, args...);
        }
        if constexpr (_size == 3) {
            glUniform3f(location, args...);
        }
        if constexpr (_size == 4) {
            glUniform4f(location, args...);
        }
    }
    if constexpr (std::is_same_v<T, int>) {
        if constexpr (_size == 1) {
            glUniform1i(location, args...);
        }
        if constexpr (_size == 2) {
            glUniform2i(location, args...);
        }
        if constexpr (_size == 3) {
            glUniform3i(location, args...);
        }
        if constexpr (_size == 4) {
            glUniform4i(location, args...);
        }
    }
    if constexpr (std::is_same_v<T, double>) {
        if constexpr (_size == 1) {
            glUniform1d(location, args...);
        }
        if constexpr (_size == 2) {
            glUniform2d(location, args...);
        }
        if constexpr (_size == 3) {
            glUniform3d(location, args...);
        }
        if constexpr (_size == 4) {
            glUniform4d(location, args...);
        }
    }
    if constexpr (std::is_same_v<T, unsigned int>) {
        if constexpr (_size == 1) {
            glUniform1ui(location, args...);
        }
        if constexpr (_size == 2) {
            glUniform2ui(location, args...);
        }
        if constexpr (_size == 3) {
            glUniform3ui(location, args...);
        }
        if constexpr (_size == 4) {
            glUniform4ui(location, args...);
        }
    }
}

template<typename... T>
requires(std::is_convertible_v<T, SShader> &&...) void SShaderProgram::attach(
    const T &...shaders) {
    // auto _attach = [](const SShader &shader) {

    // };
    (glAttachShader(m_program, shaders.shader()), ...);
    return;
}

} // namespace engine