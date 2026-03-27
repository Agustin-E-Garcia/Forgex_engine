#include "SceneRenderer.h"
#include <GL/glew.h>

#include <ForgexCore.h>
#include <GL/glu.h>
#include <glm/gtc/type_ptr.hpp>
#include <type_traits>

namespace Forgex::Graphics::Renderers
{
    void PrintGLError(std::string errorMsg)
    {
        GLenum error = glGetError();
        if (error != GL_NO_ERROR) 
        {
            LOG_CORE(Debug::LogLevel::Error, "{0}: {1}", errorMsg, (const char*)gluErrorString(error));
        }
    }

    void SceneRenderer::Render(const Resources::RenderView* renderView, std::vector<Components::Renderable>* renderInfos)
    {
        for (const Components::Renderable& info : *renderInfos)
        {
            glUseProgram(info.m_MaterialAsset->GetShaderID());

            const int modelLoc = glGetUniformLocation(info.m_MaterialAsset->GetShaderID(), "model");
            const int viewLoc = glGetUniformLocation(info.m_MaterialAsset->GetShaderID(), "view");
            const int projectionLoc = glGetUniformLocation(info.m_MaterialAsset->GetShaderID(), "projection");

            if(modelLoc != -1) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &info.m_ModelMatrix[0][0]);
            if(viewLoc != -1) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &renderView->m_ViewMatrix[0][0]);
            if(projectionLoc != -1) glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &renderView->m_ProjectionMatrix[0][0]);

            for(const auto& [name, value] : info.m_MaterialAsset->GetProperties())
            {
                int loc = glGetUniformLocation(info.m_MaterialAsset->GetShaderID(), name.c_str());
                if(loc == -1)
                {
                    LOG_CORE(Debug::Error, "Unable to find loc '{0}'", name);
                }

                std::visit([&](auto&& v)
                {
                    using T = std::decay_t<decltype(v)>;
                    if      constexpr (std::is_same_v<T, float>)     glUniform1f(loc, v);
                    else if constexpr (std::is_same_v<T, int>)       glUniform1i(loc, v);
                    else if constexpr (std::is_same_v<T, bool>)      glUniform1i(loc, (int)v);
                    else if constexpr (std::is_same_v<T, glm::vec3>) glUniform3fv(loc, 1, glm::value_ptr(v));
                    else if constexpr (std::is_same_v<T, glm::vec4>) glUniform4fv(loc, 1, glm::value_ptr(v));
                    else if constexpr (std::is_same_v<T, Assets::AssetHandle<TextureAsset>>)
                    {
                        Assets::AssetHandle<TextureAsset> textureHandle = v;
                        glActiveTexture(GL_TEXTURE0);
                        glBindTexture(GL_TEXTURE_2D, textureHandle->GetTextureID());
                        glUniform1i(loc, 0);
                    }
                }, value);
            }

            PrintGLError("Error after binding uniforms");

            int stride = 8 * sizeof(float);
            glBindBuffer(GL_ARRAY_BUFFER, info.m_MeshAsset->GetVertexBuffer());

            glEnableVertexAttribArray(0); // Vertices
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

            PrintGLError("Error after binding vertex buffer");

            glEnableVertexAttribArray(1); // Normals
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));

            PrintGLError("Error after binding normal buffer");

            glEnableVertexAttribArray(2); // UVs
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

            PrintGLError("Error after binding UV buffer");

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.m_MeshAsset->GetIndexBuffer());

            PrintGLError("Error after binding index buffer");

            glDrawElements(GL_TRIANGLES, info.m_MeshAsset->GetIndexBufferCount(), GL_UNSIGNED_INT, (void*)0);
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(2);

            PrintGLError("Error after drawing");
        }
    }
}
