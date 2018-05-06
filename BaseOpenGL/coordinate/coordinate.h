//
// Created by 张瑞 on 2018/5/6.
// Copyright (c) 2018 emery. All rights reserved.
//

#ifndef BASEOPENGL_COORDINATE_H
#define BASEOPENGL_COORDINATE_H

#include "glm/glm.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "SOIL2.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


int coordinate_main(){

    const GLuint WIDTH=800,HEIGHT=600;
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "learn coordinate", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    glewInit();



    Shader shader("/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/coordinate/coordinate.vs",
            "/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/coordinate/coordinate.frag");


    GLfloat vertexes[] = {
            // Positions          // Colors           // Texture Coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
    };

    GLuint indices[] = {
            0, 1, 3, // First Triangle
            1, 2, 3  // Second Triangle
    };

    GLuint VAO,VBO,EBO;

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes),vertexes,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8* sizeof(GLfloat),(GLfloat*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8* sizeof(GLfloat),(GLfloat*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8* sizeof(GLfloat),(GLfloat*)(6* sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);


    GLuint  texture1,texture2;

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    int width;
    int height;
    unsigned char* image = SOIL_load_image("/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/res/image/timg.jpeg",
            &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);


    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    image = SOIL_load_image("/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/res/image/awesomeface.png",
            &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);


    while (!glfwWindowShouldClose(window)){
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glUniform1i(glGetUniformLocation(shader.Program,"ourTexture1"),0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glUniform1i(glGetUniformLocation(shader.Program,"ourTexture2"),1);

        glm::mat4 model;
        model = glm::rotate(model, -45.0f, glm::vec3(1.0f,0.0f,0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program,"model"),1,GL_FALSE,glm::value_ptr(model));

        glm::mat4 view;
        view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program,"view"),1,GL_FALSE,glm::value_ptr(view));

        glm::mat4 projection;
        projection = glm::perspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program,"projection"),1,GL_FALSE,glm::value_ptr(projection));


        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);

    glfwTerminate();

    return 0;
}


#endif //BASEOPENGL_COORDINATE_H
