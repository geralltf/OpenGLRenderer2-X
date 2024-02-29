#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include "Vector2f.h"
#include "Vector3f.h"
#include "ColourRGBA.h"
#include "Vector2i.h"
#include "Texture.h"

#include <GL\glew.h>
//#define GLFW_DLL
#include "GLFW\glfw3.h"

class Model
{
public:
    std::vector<Vector3f*>* verts;     // array of vertices
    std::vector<Vector3f*>* tex_coord; // per-vertex array of tex coords
    std::vector<Vector3f*>* norms;     // per-vertex array of normal vectors
    std::vector<int>* facet_verts;
    std::vector<int>* facet_texcoords;  // per-triangle indices in the above arrays
    std::vector<int>* facet_normals;
    std::vector<std::vector<Vector3f*>*>* faces_indicies; // Vec3i attention, this Vec3i means vertex/uv/normal
    //std::vector<std::vector<Vector3> > faces_; // Vec3i attention, this Vec3i means vertex/uv/normal

    std::vector<unsigned int>* face_indicies;
    std::vector<Vector3f*>* face_verts;
    std::vector<Vector3f*>* tex_coordA;
    std::vector<Vector3f*>* face_normals;
    std::vector<Vector3f*>* face_tangents;
    std::vector<Vector3f*>* face_bitangents;

    Texture* diffusemap_;
    Texture* normalmap_;
    Texture* specularmap_;
    Texture* glowmap_;
    Texture* load_texture(std::string* filename, std::string* suffix);
public:
    std::string* file_name;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int normalsBuffer;
    unsigned int texcoordsBuffer;
    unsigned int tangentsBuffer;
    unsigned int bitangentsBuffer;
    unsigned int EBO;
    bool has_init = false;
    Model(std::string* filename);
    void parse(std::string* _file_name);
    void tangent_bitangent_compute(Vector3f* vert_pos0, Vector3f* vert_pos1, Vector3f* vert_pos2, Vector3f* uv0, Vector3f* uv1, Vector3f* uv2);
    //Vector3f* uv(const int iface, const int nthvert) const;
    inline Vector3f* uv(const int iface, const int nthvert) const {
        return (*tex_coord)[(*facet_texcoords)[iface * 3 + nthvert]];
    }
    inline Vector3f* normal(int iface, int nthvert)
    {
        int face_ind = facet_verts->at(iface);
        std::vector<Vector3f*>* face = ((*faces_indicies)[iface]);
        Vector3f* vertex = (*face)[nthvert];
        int normalIndex = (int)vertex->y;
        return (*face_normals)[normalIndex]->Normalised();
    }
    //Vector3f* normal(int iface, int nthvert);
    Vector3f* normal(Vector2f* uv);
    Vector3f* vert(int i);
    Vector3f* vert(int iface, int nthvert);
    //Vector2f* uv(int iface, int nthvert);
    ColourRGBA* diffuse(Vector2f* uv);
    float specular(Vector2f* uv);
    ColourRGBA* emissiveness(Vector2f* uvf);
    std::vector<int>* face(int idx);
    int verts_count() const;
    int faces_count() const;
    void init();
    void bind();
};

#endif