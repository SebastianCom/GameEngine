#pragma once

namespace fw {

class Texture
{
public:
    Texture();
    Texture(const char* filename);
    Texture(const char r1, const char g1, const char b1, const char a1, const char r2, const char g2, const char b2, const char a2);
    virtual ~Texture();

    // Getters.
    GLuint GetTextureID() { return m_TextureID; }

protected:
    GLuint m_TextureID = 0;
};

} // namespace fw
