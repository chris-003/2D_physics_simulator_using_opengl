#pragma once
#include "ShaderProgram.h"

namespace engine {
namespace Resource {
ShaderProgram &ShaderProgram_copy();
ShaderProgram &ShaderProgram_mix_color();
ShaderProgram &ShaderProgram_color();
namespace renderText {
ShaderProgram &shaderProgram();
} // namespace renderText
} // namespace Resource
} // namespace engine