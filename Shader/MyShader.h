//
//  MyShader.h
//

#ifndef MyShader_h
#define MyShader_h

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    // shader program id
    unsigned int ID;
    
    // read and build shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif /* MyShader_h */
