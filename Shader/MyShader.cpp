//
//  MyShader.cpp
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MyShader.h"


Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    // retrieve source code from filepath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    //
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open file
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file into stream
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file
        vShaderFile.close();
        fShaderFile.close();
        // convert stream to string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    // compile shader
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];
    // vertex shader
    vertex = glad_glCreateShader(GL_VERTEX_SHADER);
    glad_glShaderSource(vertex, 1, &vShaderCode, NULL);
    glad_glCompileShader(vertex);
    // print error message
    glad_glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glad_glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    fragment = glad_glCreateShader(GL_FRAGMENT_SHADER);
    glad_glShaderSource(fragment, 1, &fShaderCode, NULL);
    glad_glCompileShader(fragment);
    glad_glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glad_glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // shader program
    ID = glad_glCreateProgram();
    glad_glAttachShader(ID, vertex);
    glad_glAttachShader(ID, fragment);
    glad_glLinkProgram(ID);
    //
    glad_glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glad_glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    // delete shaders
    glad_glDeleteShader(vertex);
    glad_glDeleteShader(fragment);
}


void Shader::use() {
    glad_glUseProgram(ID);
}


void Shader::setBool(const std::string &name, bool value) const {
    glad_glUniform1i(glad_glGetUniformLocation(ID, name.c_str()), (int)value);
}


void Shader::setInt(const std::string &name, int value) const {
    glad_glUniform1i(glad_glGetUniformLocation(ID, name.c_str()), value);
}


void Shader::setFloat(const std::string &name, float value) const {
    glad_glUniform1f(glad_glGetUniformLocation(ID, name.c_str()), value);
}


void Shader::setVec3(const std::string &name, glm::vec3 value) const {
    glad_glUniform3f(glad_glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}


void Shader::setMat4(const std::string &name, glm::mat4 value) const {
    glad_glUniformMatrix4fv(glad_glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}


