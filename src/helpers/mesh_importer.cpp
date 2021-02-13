#include <fstream>
#include <helpers/mesh_importer.h>
#include <iostream>
#include <sstream>
#include <stdio.h>

namespace Brick3D
{

Mesh *MeshImporter::ImportMesh(std::string path)
{
    Mesh *mesh = new Mesh();
    std::cout << "Loading component from path " << path << std::endl;
    std::ifstream stream(path);
    std::string line;
    if (!stream.is_open())
    {

        throw "ERROR::OBJConverter::Could not open file";
    }

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    std::stringstream ss;
    std::string prefix = "";

    while (getline(stream, line))
    {
        ss.clear();
        ss.str(line);
        ss >> prefix;

        // Vertex positions
        if (prefix == "v")
        {
            glm::vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;
            temp_vertices.push_back(vertex);
        }
        else if (prefix == "vt")
        {
            glm::vec2 uv;
            ss >> uv.x >> uv.y;
            temp_uvs.push_back(uv);
        }
        // Normal values
        else if (prefix == "vn")
        {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        // Face values
        else if (prefix == "f")
        {
            int currentIndex = 0;
            int counter = 0;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            unsigned int val;
            while (ss >> val)
            {

                if (counter == 0)
                    vertexIndex[currentIndex] = val - 1;
                else if (counter == 1)
                    uvIndex[currentIndex] = val - 1;
                else if (counter == 2)
                    normalIndex[currentIndex] = val - 1;

                if (ss.peek() == '/')
                {
                    ++counter;
                    ss.ignore(1, '/');
                }
                else if (ss.peek() == ' ')
                {
                    ++counter;
                    ss.ignore(1, ' ');
                }

                if (counter > 2)
                {
                    counter = 0;
                    ++currentIndex;
                }
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }
    std::vector<glm::vec3> temp_out_vertices;
    std::vector<glm::vec2> temp_out_uvs;
    std::vector<glm::vec3> temp_out_normals;
    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i];
        glm::vec3 vertex = temp_vertices[vertexIndex];
        temp_out_vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < uvIndices.size(); i++)
    {
        unsigned int uvIndex = uvIndices[i];
        glm::vec2 uv = temp_uvs[uvIndex];
        temp_out_uvs.push_back(uv);
    }
    for (unsigned int i = 0; i < normalIndices.size(); i++)
    {
        unsigned int normalIndex = normalIndices[i];
        glm::vec3 normal = temp_normals[normalIndex];
        temp_out_normals.push_back(normal);
    }

    std::vector<glm::vec3> out_vertices;
    std::vector<glm::vec2> out_uvs;
    std::vector<glm::vec3> out_normals;
    std::vector<unsigned short> out_index_buffer;

    IndexVBO(temp_out_vertices, temp_out_uvs, temp_out_normals, out_index_buffer,
             out_vertices, out_uvs, out_normals);
    mesh->Init(out_vertices, out_uvs, out_normals, out_index_buffer);
    return mesh;
}

void MeshImporter::IndexVBO(std::vector<glm::vec3> &in_vertices,
                            std::vector<glm::vec2> &in_uvs,
                            std::vector<glm::vec3> &in_normals,
                            std::vector<unsigned short> &out_indices,
                            std::vector<glm::vec3> &out_vertices,
                            std::vector<glm::vec2> &out_uvs,
                            std::vector<glm::vec3> &out_normals)
{
    std::map<Vertex, unsigned short> VertexToOutIndex;

    for (unsigned int i = 0; i < in_vertices.size(); i++)
    {
        Vertex vertex = Vertex(in_vertices[i], in_normals[i], in_uvs[i]);

        // Find another version of the vertex in out
        // Requires that position, uv, and normal are all matching
        unsigned short index;
        bool found = GetSimilarVertexIndex(vertex, VertexToOutIndex, index);

        if (found)
        {
            out_indices.push_back(index);
        }
        else
        {
            // If it does not already exist, we want to add all the vertex properties
            // to the out vectors
            out_vertices.push_back(in_vertices[i]);
            out_uvs.push_back(in_uvs[i]);
            out_normals.push_back(in_normals[i]);

            // We need to get the index for this new vertex
            unsigned short new_index = (unsigned short)out_vertices.size() - 1;

            // Then add it to the index buffer
            out_indices.push_back(new_index);

            VertexToOutIndex[vertex] = new_index;
        }
    }
}

bool MeshImporter::GetSimilarVertexIndex(
    Vertex &vertex, std::map<Vertex, unsigned short> &VertexToOutIndex,
    unsigned short &result)
{
    std::map<Vertex, unsigned short>::iterator it = VertexToOutIndex.find(vertex);
    // If we find nothing
    if (it == VertexToOutIndex.end())
    {
        return false;
    }
    else
    {
        // Iterator returns std::pair of Vertex to index
        // We need to only get the index, and then we assign that to the result
        result = it->second;
        return true;
    }
}

} // namespace Brick3D