
#include <me/Core/Render/Texture/Texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include <Image/stb_image.h>

#include <GL/glew.h>
#include <iostream>

using namespace me::core::render;

Texture::Texture(const char* path)
{
    LoadTexture(path);
}

void Texture::BindTexture(unsigned int id)
{
    if (texture) {

        glActiveTexture(id);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}

void Texture::LoadTexture(const char* path)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // load and generate the texture
    //stbi_set_flip_vertically_on_load(true);
    data = stbi_load(path, &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
