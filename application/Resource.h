#pragma once
#include <string>

#define DECLARE_RESOURCE(type, name)                                           \
public:                                                                        \
    const type &name() const {                                                 \
        return m_##name;                                                       \
    }                                                                          \
                                                                               \
protected:                                                                     \
    type m_##name

class Resource {
private:
    Resource();

public:
    ~Resource();
    static Resource &getInstance();
    DECLARE_RESOURCE(std::string, basic_vert);
    DECLARE_RESOURCE(std::string, basic_frag);
    DECLARE_RESOURCE(std::string, copy_texutre_vert);
    DECLARE_RESOURCE(std::string, copy_texture_frag);
    DECLARE_RESOURCE(std::string, blur7_pingpong_h_vert);
    DECLARE_RESOURCE(std::string, blur7_pingpong_h_frag);
    DECLARE_RESOURCE(std::string, blur7_pingpong_v_vert);
    DECLARE_RESOURCE(std::string, blur7_pingpong_v_frag);
    DECLARE_RESOURCE(std::string, blurN_pingpong_h_vert);
    DECLARE_RESOURCE(std::string, blurN_pingpong_h_frag);
    DECLARE_RESOURCE(std::string, blurN_pingpong_v_vert);
    DECLARE_RESOURCE(std::string, blurN_pingpong_v_frag);
};

#undef DECLARE_RESOURCE