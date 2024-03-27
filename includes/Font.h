#ifndef FONT_H
#define FONT_H

#include <map>
#include <string>
#include <iostream>

#include <ft2build.h>
#include FT_FREETYPE_H  

#include "Vector2f.h"
#include "Texture.h"
#include "Vao.h"
#include "ShaderProgram.h"
#include "ColourRGBA.h"
#include "OpenGlUtils.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class FontCharacter 
{
public:
    unsigned int TextureID;  // ID handle of the glyph texture
    Vector2f*   Size;       // Size of glyph
    Vector2f*   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};

class FontRenderer {
public:
    std::map<char, FontCharacter*>* Characters;
    FT_Face* face;
    FT_Library* ft;
    ShaderProgram* program;
    //Texture* spriteTexture;
    Vao* vaoSprite;
    std::vector<unsigned int>* indicies;
    unsigned int VAO, VBO;

    Vector3f* position;
    Vector2f* sprite_size;
    Vector3f* scale;
    Vector3f* iscale;
    float x = 0;
    float y = 0;

    FontRenderer();
    ~FontRenderer();
    void Render(sf::RenderWindow* window, std::string* text_string, ColourRGBA* text_colour);
};

#endif