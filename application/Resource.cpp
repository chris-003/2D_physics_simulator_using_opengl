#include "Resource.h"

#define DEFINE_RESOURCE(name, path) __asm__(".section .rodata\n" \
    "_" #name ":\n" \
    ".incbin" " \"" path "\"\n" \
    ".byte 0\n" \
    ".text\n"); \
    extern char *_##name; \
    m_##name = _##name

Resource::Resource() {
    DEFINE_RESOURCE(basic_vert, "./Resource/basic.vert");
    DEFINE_RESOURCE(basic_frag, "./Resource/basic.frag");
    DEFINE_RESOURCE(copy_texutre_vert, "./Resource/copy_texture.vert"); 
    DEFINE_RESOURCE(copy_texture_frag, "./Resource/copy_texture.frag");
    DEFINE_RESOURCE(blur7_pingpong_h_vert, "./Resource/blur7_pingpong_h.vert");
    DEFINE_RESOURCE(blur7_pingpong_h_frag, "./Resource/blur7_pingpong_h.frag");
    DEFINE_RESOURCE(blur7_pingpong_v_vert, "./Resource/blur7_pingpong_v.vert");
    DEFINE_RESOURCE(blur7_pingpong_v_frag, "./Resource/blur7_pingpong_v.frag");
    DEFINE_RESOURCE(blurN_pingpong_h_vert, "./Resource/blurN_pingpong_h.vert");
    DEFINE_RESOURCE(blurN_pingpong_h_frag, "./Resource/blurN_pingpong_h.frag");
    DEFINE_RESOURCE(blurN_pingpong_v_vert, "./Resource/blurN_pingpong_v.vert");
    DEFINE_RESOURCE(blurN_pingpong_v_frag, "./Resource/blurN_pingpong_v.frag");
}

Resource::~Resource() {
}

Resource &Resource::getInstance() {
    static Resource instance;
    return instance;
}