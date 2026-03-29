#include "SkyboxRenderer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ForgexCore.h>

namespace Forgex::Graphics::Renderers
{
    void SkyboxRenderer::Render(const Resources::RenderFrameData& renderView, const Components::Renderable& renderable)
    {

        int width, height;
        glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
        glViewport(0, 0, width, height);

        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);
        glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDepthMask(GL_FALSE);
        glUseProgram(renderable.m_MaterialAsset->GetShaderID());

        const int ProjectionLoc = glGetUniformLocation(renderable.m_MaterialAsset->GetShaderID(), "projection");
        if(ProjectionLoc != -1)
            glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, &renderView.m_ProjectionMatrix[0][0]);
        else LOG_CORE(Debug::Error, "Failed to find uniform location 'Projection'");

        const int ViewLoc = glGetUniformLocation(renderable.m_MaterialAsset->GetShaderID(), "view");
        if(ViewLoc != -1)
        {
            glm::mat4 skyboxView = glm::mat4(glm::mat3(renderView.m_ViewMatrix));
            glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, &skyboxView[0][0]);
        }
        else LOG_CORE(Debug::Error, "Failed to find uniform location 'View'");

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, renderable.m_MeshAsset->GetVertexBuffer());
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        auto& textureHandle = std::get<Assets::AssetHandle<TextureAsset>>(renderable.m_MaterialAsset->GetProperties().at("albedoMap").m_Property);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureHandle->GetTextureID());
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDisableVertexAttribArray(0);
        glUseProgram(0);
        glDepthMask(GL_TRUE);
    }
}
