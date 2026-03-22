#include "SkyboxRenderer.h"
#include <GL/glew.h>

namespace Forgex::Graphics::Renderers
{
    void SkyboxRenderer::Render(const Resources::RenderView& renderView, const Components::Renderable& renderable)
    {
        glDepthMask(GL_FALSE);
        glUseProgram(renderable.m_ShaderAsset->GetShaderID());

        const int ProjectionLoc = glGetUniformLocation(renderable.m_ShaderAsset->GetShaderID(), "projection");
        if(ProjectionLoc != -1)
            glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, &renderView.m_ProjectionMatrix[0][0]);
        else LOG_CORE(Debug::Error, "Failed to find uniform location 'Projection'");

        const int ViewLoc = glGetUniformLocation(renderable.m_ShaderAsset->GetShaderID(), "view");
        if(ViewLoc != -1)
        {
            glm::mat4 skyboxView = glm::mat4(glm::mat3(renderView.m_ViewMatrix));
            glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, &skyboxView[0][0]);
        }
        else LOG_CORE(Debug::Error, "Failed to find uniform location 'View'");

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, renderable.m_VertexBufferID);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glBindTexture(GL_TEXTURE_CUBE_MAP, renderable.m_TextureAsset->GetTextureID());
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDisableVertexAttribArray(0);
        glUseProgram(0);
        glDepthMask(GL_TRUE);
    }
}
