
#include <iostream>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#pragma comment(lib, "freetype.lib")

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <Engine/EntityComponent/UIComponents/Font.h>

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

struct Font::Internal
{
    FT_Library ft;
    FT_Face face;

    std::map<char, Character> Characters;
};

Font::Font(const char* path)
    : m_font(new Internal())
{
    if (FT_Init_FreeType(&m_font->ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    if (FT_New_Face(m_font->ft, path, 0, &m_font->face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(m_font->face, 0, 48);
    LoadAllCharacter();
}

void Font::LoadAllCharacter()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(m_font->face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            m_font->face->glyph->bitmap.width,
            m_font->face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            m_font->face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(m_font->face->glyph->bitmap.width, m_font->face->glyph->bitmap.rows),
            glm::ivec2(m_font->face->glyph->bitmap_left,  m_font->face->glyph->bitmap_top),
            m_font->face->glyph->advance.x
        };
        m_font->Characters.insert(std::pair<char, Character>(c, character));
    }
}
