#include "ShaderLoader.h"
#include <GL/glew.h>
#include <string>
#include <vector>

#include <ForgexCore.h>
#include <ForgexFiles.h>

namespace Forgex::Graphics::Utils
{
    bool CheckShaderOK(const unsigned int shaderID)
    {
        int result = 0;
        int infoLogLenght;

        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLenght);
        if (infoLogLenght > 0)
        {
            std::vector<char> ShaderErrorMessage(infoLogLenght + 1);
            glGetShaderInfoLog(shaderID, infoLogLenght, NULL, ShaderErrorMessage.data());
            LOG_CORE(Debug::Error, ShaderErrorMessage.data());
            return false;
        }

        return true;
    }

    int ShaderLoader::LoadShader(const char* vertexShader, const char* fragmentShader)
    {
        unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vertexShaderCode;
        if(!Files::ReadFile(vertexShader, vertexShaderCode))
        {
            LOG_CORE(Debug::Error, "Impossible to open '{0}'. File could be missing, check directory", vertexShader);
            return -1;
        }

        std::string fragmentShaderCode;
        if(!Files::ReadFile(fragmentShader, fragmentShaderCode))
        {
            LOG_CORE(Debug::Error, "Impossible to open '{0}'. File could be missing, check directory", fragmentShader);
            return -1;
        }

        LOG_CORE(Debug::Info, "Compiling Shader: '{0}'", vertexShader);
        char const* vertexSourcePointer = vertexShaderCode.c_str();
        glShaderSource(vertexShaderID, 1, &vertexSourcePointer, NULL);
        glCompileShader(vertexShaderID);

        if(!CheckShaderOK(vertexShaderID)) return -1;

        LOG_CORE(Debug::Info, "Compiling Shader: '{0}'", fragmentShader);
        char const* fragmentSourcePointer = fragmentShaderCode.c_str();
        glShaderSource(fragmentShaderID, 1, &fragmentSourcePointer, NULL);
        glCompileShader(fragmentShaderID);

        if (!CheckShaderOK(fragmentShaderID)) return -1;

        LOG_CORE(Debug::Info, "Linking program");
        unsigned int programID = glCreateProgram();
        glAttachShader(programID, vertexShaderID);
        glAttachShader(programID, fragmentShaderID);
        glLinkProgram(programID);

        int result = 0;
        int infoLogLenght;

        glGetProgramiv(programID, GL_LINK_STATUS, &result);
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLenght);
        if (infoLogLenght > 0) 
        {
            std::vector<char> programErrorMessage(infoLogLenght + 1);
            glGetProgramInfoLog(programID, infoLogLenght, NULL, programErrorMessage.data());
            LOG_CORE(Debug::Error, programErrorMessage.data());
            return -1;
        }

        glDetachShader(programID, vertexShaderID);
        glDetachShader(programID, fragmentShaderID);

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);

        return programID;
    }

    void ShaderLoader::UnloadShader(unsigned int shaderID)
    {
        glDeleteProgram(shaderID);
    }
}
