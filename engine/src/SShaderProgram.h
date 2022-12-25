#pragma once
#include "SShader.h"
#include "concepts.h"
#include <string>

namespace engine {
class SShaderProgram {
public:
    template<typename... T>
    requires(std::is_convertible_v<T, SShader> &&...)
        SShaderProgram(const T &...shaders);
    // SShaderProgram(const std::string &vert, const std::string &frag);
    ~SShaderProgram();
    void bind() const;
    template<typename T, size_t _size>
    requires(in_type_list_v<T, float, int, double, unsigned int> &&
             1 <= _size &&
             _size <= 4) void setUniform(GLint                  location,
                                         std::array<T, _size> &&v);
    template<typename T, typename... Args>
    requires(in_type_list_v<T, float, int, double, unsigned int> &&
             1 <= sizeof...(Args) && sizeof...(Args) <= 4 &&
             (std::is_convertible_v<Args, T> &&
              ...)) void setUniform(GLint location, Args &&...args);

private:
    // void attach();
    // void attach(const SShader &first);
    // void attach(const SShader &first, const SShader &shaders...);
    template<typename... T>
    requires(std::is_convertible_v<T, SShader> &&...) void attach(
        const T &...shaders);

public:
    unsigned int m_program;
};
} // namespace engine

#include "SShaderProgram.hpp"