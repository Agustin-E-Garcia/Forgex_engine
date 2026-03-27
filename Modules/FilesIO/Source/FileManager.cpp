#include "FileManager.h"
#include <exception>
#include <fstream>
#include <sstream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

using json = nlohmann::json;

namespace Forgex::Files
{
    TextureData::TextureData() {}
    TextureData::~TextureData() { stbi_image_free(m_Image); }

    bool WriteFile(const char* filePath, nlohmann::json& data)
    {
        return true;
    }

    bool ReadFile(const char* filePath, nlohmann::json& data, std::string& err)
    {
        try
        {
            std::ifstream file(filePath);
            data = json::parse(file);
            return true;
        }
        catch (const std::exception& e)
        {
            err = e.what();
            return false;
        }
    }

    bool ReadMeshFile(const char* filePath, nlohmann::json& data)
    {
        tinyobj::ObjReader reader;

        if(!reader.ParseFromFile(std::string(filePath))) return false;

        const tinyobj::attrib_t& attrib = reader.GetAttrib();
        const std::vector<tinyobj::shape_t>& shapes = reader.GetShapes();

        std::vector<float> vertices;
        std::vector<int> indices;
        for(int s = 0; s < shapes.size(); s++)
        {
            // Loop over faces(polygon)
            int vertexIndexOffset = 0;
            for (int f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {
                int FaceVertexCount = int(shapes[s].mesh.num_face_vertices[f]);

                // Loop over vertices in the face.
                for (int v = 0; v < FaceVertexCount; v++)
                {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[vertexIndexOffset + v];

                    // Push index
                    indices.push_back(vertices.size() / 8); // 3 floats for vertex, 3 for normal and 2 for UV

                    // Push vertex
                    vertices.push_back(attrib.vertices[3*int(idx.vertex_index)+0]);
                    vertices.push_back(attrib.vertices[3*int(idx.vertex_index)+1]);
                    vertices.push_back(attrib.vertices[3*int(idx.vertex_index)+2]);

                    // Push normal
                    vertices.push_back(attrib.normals[3*int(idx.normal_index)+0]);
                    vertices.push_back(attrib.normals[3*int(idx.normal_index)+1]);
                    vertices.push_back(attrib.normals[3*int(idx.normal_index)+2]);

                    // Push UV
                    vertices.push_back(attrib.texcoords[2*int(idx.texcoord_index)+0]);
                    vertices.push_back(attrib.texcoords[2*int(idx.texcoord_index)+1]);
                }
                vertexIndexOffset += FaceVertexCount;

                // per-face material
                //shapes[s].mesh.material_ids[f];
            }
        }

        data["vertices"] = vertices;
        data["vertexCount"] = vertices.size();
        data["indices"] = indices;
        data["indexCount"] = indices.size();

        return true;
    }

    bool ReadFile(const char* filePath, std::string& buffer)
    {
        std::ifstream fileStream(filePath, std::ios::in);
        if (!fileStream.is_open()) return false;

        std::stringstream sstr;
        sstr << fileStream.rdbuf();
        buffer = sstr.str();
        fileStream.close();
        return true;
    }

    bool ReadFile(const char* filePath, std::vector<std::string>& buffers)
    {
        std::ifstream fileStream(filePath, std::ios::in);
        if (!fileStream.is_open()) return false;

        std::string line;
        while (std::getline(fileStream, line, ','))
        {
            while (!line.empty() && (line.back() == '\n' || line.back() == '\r' || line.back() == ' '))
                line.pop_back();

            if (!line.empty())
                buffers.push_back(line);
        }

        return !buffers.empty();
    }

    bool ReadFile(const char* filePath, TextureData& textureData, bool flip)
    {
        stbi_set_flip_vertically_on_load(flip);

        int width, height, nrChannels;
        unsigned char* image = stbi_load(filePath, &width, &height, &nrChannels, 0);

        if(!image) return false;

        textureData.m_Image = image;
        textureData.m_Width = width;
        textureData.m_Height = height;
        textureData.m_Channels = nrChannels;

        return true;
    }

}
