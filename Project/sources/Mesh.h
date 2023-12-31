//
// This code is based on the tutorial from https://learnopengl.com
//

#ifndef VR_PROJECT_MESH_H
#define VR_PROJECT_MESH_H

#include <string>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "Shader.h"

#define MAX_BONE_INFLUENCE 5
/**
 * Vertex data structure
 */
struct Vertex {
    glm::vec3 Position;     // position in the 3D space
    glm::vec3 Normal;       // normal vector (should point outside and be normalized)
    glm::vec2 TexCoords;    // indicates which part of the texture should be mapped to this vertex
    glm::vec3 Tangents;
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};


/**
 * Texture data structure
 */
struct Texture {
    unsigned int id;    // id of the texture
    std::string type;   // type of the texture (diffuse, specular, etc)
    std::string path;   // path to the texture file
};


/**
 * Mesh class
 */
class Mesh {

private:
    //  render data
    unsigned int VAO, VBO, EBO;
    void setupMesh();

public:
    // mesh data
    std::vector<Vertex>       vertices; // vertices of the mesh
    std::vector<unsigned int> indices;  // the indices, taken 3 by 3, define the triangles
    std::vector<Texture>      textures; // textures of the mesh

    /**
     * Constructor of a Mesh
     * @param vertices of the mesh
     * @param indices list of indices defining the triangular faces
     * @param textures of the mesh
     */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    /**
     * Draw the mesh in the scene
     * @param shader used shader to draw the mesh
     */

    void Draw(Shader& shader, int apply);
    void setTransform(float posX, float posY, float posZ, float rotW, float rotX, float rotY, float rotZ);
};


#endif //VR_PROJECT_MESH_H