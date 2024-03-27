#include "Font.h"

#define WIDTH   128
#define HEIGHT  128


/* origin is the upper left corner */
unsigned char image[HEIGHT][WIDTH];

void draw_bitmap(FT_Bitmap* bitmap,
    FT_Int      x,
    FT_Int      y)
{
    FT_Int  i, j, p, q;
    FT_Int  x_max = x + bitmap->width;
    FT_Int  y_max = y + bitmap->rows;


    /* for simplicity, we assume that `bitmap->pixel_mode' */
    /* is `FT_PIXEL_MODE_GRAY' (i.e., not a bitmap font)   */

    for (i = x, p = 0; i < x_max; i++, p++)
    {
        for (j = y, q = 0; j < y_max; j++, q++)
        {
            if (i < 0 || j < 0 ||
                i >= WIDTH || j >= HEIGHT)
                continue;

            image[j][i] |= bitmap->buffer[q * bitmap->width + p];
        }
    }
}

void show_image(void)
{
    int  i, j;


    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
            putchar(image[i][j] == 0 ? ' '
                : image[i][j] < 128 ? '#'
                : '*');
        putchar('\n');
    }
}

FontRenderer::FontRenderer()
{
    program = new ShaderProgram("Shaders/screenFont_vs.glsl","Shaders/screenFont_fs.glsl");

    std::vector<GLfloat>* vertices = new std::vector<GLfloat>();
    GLfloat v = 0.0f;
    GLfloat v2 = 1.0f;

    vertices->push_back(v);
    vertices->push_back(v);
    vertices->push_back(v);

    vertices->push_back(v2);
    vertices->push_back(v);
    vertices->push_back(v);
    vertices->push_back(v2);
    vertices->push_back(v2);
    vertices->push_back(v);

    vertices->push_back(v);
    vertices->push_back(v2);
    vertices->push_back(v);

    std::vector<GLfloat>* texCoords = new std::vector<GLfloat>();
    GLfloat f = 0.0f;
    GLfloat f2 = 1.0f;

    texCoords->push_back(f);
    texCoords->push_back(f2);
    texCoords->push_back(f);
    texCoords->push_back(f);
    texCoords->push_back(f2);
    texCoords->push_back(f2);
    texCoords->push_back(f);
    texCoords->push_back(f2);

    indicies = new std::vector<unsigned int>();
    unsigned int i = 0;
    unsigned int i2 = 1;
    unsigned int i3 = 2;
    unsigned int i4 = 3;

    indicies->push_back(i);
    indicies->push_back(i2);
    indicies->push_back(i3);
    indicies->push_back(i4);

    vaoSprite = Vao::create();
    vaoSprite->bind();
    vaoSprite->createIndexBuffer(indicies);
    vaoSprite->createAttribute(0, vertices, 3);
    vaoSprite->createAttribute(1, texCoords, 2);
    vaoSprite->unbind();

    FT_Library  library;   /* handle to library     */
    FT_Face     face;      /* handle to face object */

    FT_GlyphSlot  slot;
    FT_Matrix     matrix;                 /* transformation matrix */
    FT_Vector     pen;                    /* untransformed origin  */
    FT_Error      error;

    std::string filename = "Assets/fonts/consola.ttf";
    //char* text;

    double        angle;
    int           target_height;
    int           n, num_chars;

    if (FT_Init_FreeType(&library))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    }

    if (FT_New_Face(library, "Assets/fonts/consola.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font 'Assets/fonts/consola.ttf'" << std::endl;
    }

    error = FT_Set_Pixel_Sizes(face, 0, 48);
    if (error)
    {
        std::cout << "ERROR::FREETYPE: Failed to set pixel size using font 'Assets/fonts/consola.ttf'" << std::endl;
    }

    error = FT_Set_Char_Size(face, 50 * 64, 0, 100, 0);                /* set character size */
    if (error) 
    {
        std::cout << "ERROR::FREETYPE: Failed to set char size using font 'Assets/fonts/consola.ttf'" << std::endl;
    }

    slot = face->glyph;
    target_height = HEIGHT;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    Characters = new std::map<char, FontCharacter*>();

    for (unsigned char c = 32; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            unsigned char cs;

            if (c > 13) 
            {
                cs = c;
            }
            else 
            {
                cs = 32;
            }
            std::cout << "ERROR::FREETYPE: Failed to load Glyph '" << cs << "' using 'Assets/fonts/consola.ttf'" << std::endl;
            continue;
        }

        /* now, draw to our target surface (convert position) */
        //draw_bitmap(&slot->bitmap, slot->bitmap_left, target_height - slot->bitmap_top);

        //show_image();

        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        FontCharacter* character = new FontCharacter();
        character->TextureID = texture;

        Vector2f* size = new Vector2f((float)(face->glyph->bitmap.width), (float)(face->glyph->bitmap.rows));
        Vector2f* bearing = new Vector2f((float)(face->glyph->bitmap_left), (float)(face->glyph->bitmap_top));

        character->Size = size;
        character->Bearing = bearing;
        character->Advance = face->glyph->advance.x;
        Characters->insert(std::pair<char, FontCharacter*>(c, character));
    }
    std::cout << "Loaded glyphs which make up the font from 'Assets/fonts/consola.ttf'" << std::endl;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
FontRenderer::~FontRenderer() 
{
    FT_Done_Face(*face);
    FT_Done_FreeType(*ft);
    delete face;
    delete ft;
    delete Characters;
}
void FontRenderer::Render(sf::RenderWindow* window, std::string* text_string, ColourRGBA* text_colour)
{
    x = 0;
    y = 0;
    for (int index = 0; index < text_string->length(); index++)
    {
        unsigned char c = text_string->at(index);

        if (Characters->size() > 0)
        {
            FontCharacter* character = Characters->at(c);

            //Vector2f* spriteSize = new Vector2f(64, 64); // size of the sprite in pixels
            Vector2i* screenSpacePosition = new Vector2i(this->position->x + (160 * 0), this->position->y - 8); // 160 * index
            Vector2f* screenSize = new Vector2f((float)window->getSize().x, (float)window->getSize().y);
            //Vector3f* position = ScreenSpaceToOrthographic(mouse, screenSize, cursorSize);
            Vector3f* position2 = new Vector3f(
                ((float)screenSpacePosition->x / screenSize->x) - 0.05f,
                (1.0f - ((float)screenSpacePosition->y / screenSize->y)) - 0.05f,
                -2.0f
            );
            Matrix4* model = Matrix4::Identity();

            float sizeX = ((this->sprite_size->x / (float)window->getSize().x));
            float sizeY = ((this->sprite_size->y / (float)window->getSize().y));
            //this->scale->x = 0.01f;
            //this->scale->y = 0.01f;
            //this->scale->z = 1.0f;
            Matrix4* scalarMatrix = Matrix4::Scale(this->scale->x, this->scale->y, this->scale->z);

            model = Matrix4::Multiply(model, scalarMatrix);
            model->Translate(position2);

            Matrix4* quadModelView = model;
            Matrix4* quadView;
            quadView = Matrix4::Identity(); // Dont use camera transform local matrix since the sprite is meant to follow the user interface on screen as the player moves.
            Matrix4* quadProj;
            quadProj = Matrix4::Orthographic(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 1000.0f); // Stick to using screen space transform for 2D user interface and 2D sprites.

            Matrix4* MVP = Matrix4::Multiply(Matrix4::Multiply(quadProj, quadView), quadModelView);

            float* arrMVP = MVP->ToArray();
            float* arrP = quadProj->ToArray();
            float* arrV = quadView->ToArray();
            float* arrM = quadModelView->ToArray();

            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            OpenGlUtils::EnableAlphaBlending(); // EnableAlphaBlending
            OpenGlUtils::EnableDepthTesting(false);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glUseProgram(program->programID);
            glUniformMatrix4fv(glGetUniformLocation(program->programID, "MVP"), 1, GL_FALSE, arrMVP);
            glUniformMatrix4fv(glGetUniformLocation(program->programID, "projectionMatrix"), 1, GL_FALSE, arrP);
            glUniformMatrix4fv(glGetUniformLocation(program->programID, "viewMatrix"), 1, GL_FALSE, arrV);
            glUniformMatrix4fv(glGetUniformLocation(program->programID, "modelMatrix"), 1, GL_FALSE, arrM);
            // glUniform2f(glGetUniformLocation(program->programID, "textureSize2"), sprite_size->x, sprite_size->y);
            glUniform1i(glGetUniformLocation(program->programID, "text"), 0);
            glUniform3f(glGetUniformLocation(program->programID, "textColor"), text_colour->r, text_colour->g, text_colour->b);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, character->TextureID);



            //if (vaoSprite != nullptr)
            //{
            //    vaoSprite->bind();
            //    vaoSprite->binder(0, 1);
            //    glDrawElements(GL_QUADS, indicies->size(), GL_UNSIGNED_INT, nullptr);
            //    vaoSprite->unbinder(0, 1);
            //    vaoSprite->unbind();
            //    glUseProgram(0);
            //}

            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(VAO);

            float xpos = x + character->Bearing->x * iscale->x;
            float ypos = y - (character->Size->y - character->Bearing->y) * iscale->y;

            float w = character->Size->x * iscale->x;
            float h = character->Size->y * iscale->y;
            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, character->TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (character->Advance >> 6) * iscale->x; // bitshift by 6 to get value in pixels (2^6 = 64)
            //x += 16;
            //if (x >= WIDTH) 
            //{
            //    x = 0;
            //}
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);

            delete[] arrMVP;
            delete[] arrP;
            delete[] arrV;
            delete[] arrM;
            delete MVP;
            delete quadProj;
            delete quadView;
            delete quadModelView;
            delete scalarMatrix;
        }

        //delete position;
        //delete screenSize;
        //delete screenSpacePosition;

        //delete vaoSprite;
        //delete model;
    }
}