#include "SceneRenderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <ForgexCore.h>

namespace Forgex::Graphics::Renderers
{
    void SceneRenderer::Render(const Resources::RenderView* renderView, std::vector<Components::Renderable>* renderInfos)
    {
        int width, height;
        glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
        glViewport(0, 0, width, height);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);
        glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (const Components::Renderable& info : *renderInfos)
        {
            glUseProgram(info.m_ShaderAsset->GetShaderID());

            const int modelLoc = glGetUniformLocation(info.m_ShaderAsset->GetShaderID(), "model");
            const int viewLoc = glGetUniformLocation(info.m_ShaderAsset->GetShaderID(), "view");
            const int projectionLoc = glGetUniformLocation(info.m_ShaderAsset->GetShaderID(), "projection");
            const int TextureLoc = glGetUniformLocation(info.m_ShaderAsset->GetShaderID(), "textureSampler");

            if(modelLoc != -1) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &info.m_ModelMatrix[0][0]);
            if(viewLoc != -1) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &renderView->m_ViewMatrix[0][0]);
            if(projectionLoc != -1) glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &renderView->m_ProjectionMatrix[0][0]);

            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after binding uniforms: ", error);
            }

            if(TextureLoc != -1)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, info.m_TextureAsset->GetTextureID());
                glUniform1i(TextureLoc, 0);
            }

            error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after binding texture: ", error);
            }

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, info.m_VertexBufferID);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

            error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after binding vertex buffer: ", error);
            }

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.m_IndexBufferID);

            error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after binding index buffer: ", error);
            }

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, info.m_VertexBufferID);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

            error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after binding uv buffer: ", error);
            }

            glDrawElements(GL_TRIANGLES, info.m_IndexSize, GL_UNSIGNED_INT, (void*)0);
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);

            error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after drawing: ", error);
            }
        }
    }

    void SceneRenderer::RenderMap(const Resources::RenderView* renderView, std::vector<Components::Renderable>* renderInfos)
    {
        int width, height;
        glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
        glViewport(0, 0, width, height);

        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_CULL_FACE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDepthFunc(GL_LESS);
        glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(const Components::Renderable& info : *renderInfos)
        {
            glUseProgram(info.m_ShaderAsset->GetShaderID());

            const int modelLoc = glGetUniformLocation(info.m_ShaderAsset->GetShaderID(), "model");
            const int viewLoc = glGetUniformLocation(info.m_ShaderAsset->GetShaderID(), "view");
            const int projectionLoc = glGetUniformLocation(info.m_ShaderAsset->GetShaderID(), "projection");

            if(modelLoc != -1) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &info.m_ModelMatrix[0][0]);
            if(viewLoc != -1) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &renderView->m_ViewMatrix[0][0]);
            if(projectionLoc != -1) glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &renderView->m_ProjectionMatrix[0][0]);

            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after binding uniforms: ", error);
            }

            glBindBuffer(GL_ARRAY_BUFFER, info.m_VertexBufferID);

            int stride = 6 * sizeof(float);

            glEnableVertexAttribArray(0); // Vertices
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);

            glEnableVertexAttribArray(1); // Normals
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, info.m_IndexBufferID);

            glDrawElements(GL_TRIANGLES, info.m_IndexSize, GL_UNSIGNED_INT, (void*)0);
            //glDrawArrays(GL_TRIANGLES, 0, info.m_IndexCount);
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
        }
    }
}
