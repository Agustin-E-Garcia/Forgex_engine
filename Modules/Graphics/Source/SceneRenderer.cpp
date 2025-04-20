#include "SceneRenderer.h"
#include "SceneRenderProxy.h"
#include "Resources/RenderView.h"
#include "Resources/RenderConstants.h"

#include <gl/glew.h>
#include <ForgexDebugTools.h>

namespace Forgex::Graphics
{
    using namespace Resources::Constants;
    
    void RenderSkybox(const Resources::RenderView* renderView)
    {
        Skybox::InitResources();
        
        glDepthMask(GL_FALSE);
        glUseProgram(Skybox::g_ShaderID);
        
        const int ProjectionLoc = glGetUniformLocation(Skybox::g_ShaderID, "projection");
        if(ProjectionLoc != -1)
            glUniformMatrix4fv(ProjectionLoc, 1, GL_FALSE, renderView->m_ProjectionMatrix.Ptr());
        else LOG_CORE(Debug::Error, "Failed to find uniform location 'Projection'");

        const int ViewLoc = glGetUniformLocation(Skybox::g_ShaderID, "view");
        if(ViewLoc != -1)
            glUniformMatrix4fv(ViewLoc, 1, GL_FALSE, Math::GetRotationOnly(renderView->m_ViewMatrix).Ptr());
        else LOG_CORE(Debug::Error, "Failed to find uniform location 'View'");
        
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, Skybox::g_VertexBufferID);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        
        glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox::g_DefaultTextureID);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDisableVertexAttribArray(0);
        glUseProgram(0);
        glDepthMask(GL_TRUE);
    }
    
    void SceneRenderer::Render(const Resources::RenderView* renderView, const SceneRenderProxy* renderProxy)
    {
        glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
        glEnable(GL_DEPTH_TEST);
        //glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        RenderObjects::InitResources();
        
        RenderSkybox(renderView);
        
        for (const RenderObjectInfo& info : *renderProxy->GetRenderObjectCollection())
        {
            glUseProgram(info.m_ShaderID);

            const int modelLoc = glGetUniformLocation(info.m_ShaderID, "model");
            const int viewLoc = glGetUniformLocation(info.m_ShaderID, "view");
            const int projectionLoc = glGetUniformLocation(info.m_ShaderID, "projection");
            const int TextureLoc = glGetUniformLocation(info.m_ShaderID, "textureSampler");
            
            if(modelLoc != -1) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, info.m_ModelMatrix.Ptr());
            if(viewLoc != -1) glUniformMatrix4fv(viewLoc, 1, GL_FALSE, renderView->m_ViewMatrix.Ptr());
            if(projectionLoc != -1) glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, renderView->m_ProjectionMatrix.Ptr());

            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after binding uniforms: ", error);
            }
            
            if(TextureLoc != -1)
            {
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, info.m_TextureID);
                glUniform1i(TextureLoc, 0);
            }

            error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after binding texture: ", error);
            }
            
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, renderProxy->GetVertexBufferID());
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

            error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after binding vertex buffer: ", error);
            }
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderProxy->GetIndexBufferID());

            error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after binding index buffer: ", error);
            }
            
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, renderProxy->GetUVBufferID());
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

            error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after binding uv buffer: ", error);
            }
            
            glDrawElements(GL_TRIANGLES, info.m_IndexCount, GL_UNSIGNED_INT, (void*)0);
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);

            error = glGetError();
            if (error != GL_NO_ERROR) {
                LOG_CORE(Debug::Error, "Error after drawing: ", error);
            }
        }
    }
}
