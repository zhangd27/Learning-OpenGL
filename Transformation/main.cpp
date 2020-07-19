//
// main
//
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include "stb_image.h"
#include "../Shader/MyShader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float mixValue = 0.2f;

int main() {
    // initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    // window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "transformation", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    // create shader program
    // -------------------------
    Shader myShader("./vShader.txt",
                    "./fShader.txt");
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        0.5f, 0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   1.0f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };
    // texture
    // -------
    unsigned int texture1, texture2;
    glad_glGenTextures(1, &texture1);
    glad_glBindTexture(GL_TEXTURE_2D, texture1);
    // set-up
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("Path/to/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glad_glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glad_glGenTextures(1, &texture2);
    glad_glBindTexture(GL_TEXTURE_2D, texture2);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glad_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    data = stbi_load("Path/to/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glad_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glad_glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int VBO, VAO, EBO;
    glad_glGenBuffers(1, &EBO);
    glad_glGenVertexArrays(1, &VAO);
    glad_glGenBuffers(1, &VBO);
    glad_glBindVertexArray(VAO);
    glad_glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glad_glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glad_glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glad_glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
    glad_glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
    glad_glEnableVertexAttribArray(0);
    glad_glEnableVertexAttribArray(1);
    glad_glEnableVertexAttribArray(2);
    //glad_glBindVertexArray(0);
    
    myShader.use();
    myShader.setInt("texture1", 0);
    myShader.setInt("texture2", 1);
    
    unsigned int transformLoc = glad_glGetUniformLocation(myShader.ID, "transform");
    
    
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);
        // render
        // ------
        glad_glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glad_glClear(GL_COLOR_BUFFER_BIT);
        // draw triangle
        // -------------
        glad_glActiveTexture(GL_TEXTURE0);
        glad_glBindTexture(GL_TEXTURE_2D, texture1);
        glad_glActiveTexture(GL_TEXTURE1);
        glad_glBindTexture(GL_TEXTURE_2D, texture2);
        glm::mat4 trans(1.0f);
        trans= glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        glad_glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
        myShader.setFloat("mixValue", mixValue);
        myShader.use();
        glad_glBindVertexArray(VAO);
        glad_glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glm::mat4 trans1(1.0f);
        trans1= glm::translate(trans1, glm::vec3(-0.5f, 0.5f, 0.0f));
        trans1 = glm::scale(trans1, glm::vec3(1.0f, 1.0f, 1.0f) * abs(sin((float)glfwGetTime())));
        glad_glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans1));
        glad_glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        mixValue += 0.005f;
        if (mixValue > 1.0f) mixValue = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        mixValue -= 0.005f;
        if (mixValue < 0.0f) mixValue = 0.0f;
    }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glad_glViewport(0, 0, width, height);
}
