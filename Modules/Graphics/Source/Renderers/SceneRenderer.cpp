#include "SceneRenderer.h"

#ifdef _WIN32
    #include <Windows.h>
#endif

#include <GL/glew.h>

#include <ForgexCore.h>
#include <GL/glu.h>

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

    void SceneRenderer::Render(const Resources::RenderFrameData& renderFrameData, const std::vector<Components::Renderable>& renderInfos)
    {
        for (const Components::Renderable& info : renderInfos)
        {
            glUseProgram(info.m_MaterialAsset->GetShaderID());

            const int modelLoc = info.m_MaterialAsset->GetModelMatrixLocation();
            if(modelLoc != -1) glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &info.m_ModelMatrix[0][0]);

            info.m_MaterialAsset->SetupProperties();

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
