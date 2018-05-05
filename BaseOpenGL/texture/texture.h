//
//  texture.h
//  BaseOpenGL
//
//  Created by 张瑞 on 2018/5/3.
//  Copyright © 2018年 emery. All rights reserved.
//

#ifndef texture_h
#define texture_h
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../SOIL2/SOIL2.h"
#include "../common/shader.h"

void key_callback(GLFWwindow*,int,int,int,int);

int texture_main() {
    const GLuint WIDTH = 800,HEIGHT = 600;

    if(!glfwInit()){
        std::cout<<"ERROR GLFW INIT FAILED" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window= glfwCreateWindow(WIDTH, HEIGHT, "texture learning", nullptr, nullptr);

    if(!window){
        std::cout<<"ERROR WINDOW INIT FAILED"<<std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    //glfwSetKeyCallback(window,key_callback);

    glewExperimental = GL_TRUE;

    glewInit();

    //glViewport(0, 0, WIDTH, HEIGHT);

    Shader shader("/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/texture/vertexShader.vs",
            "/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/texture/fragmentShader.frag");

    GLfloat vertexs[] = {
            //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    GLuint indics[] = {
            0, 1, 3, // First Triangle
            1, 2, 3  // Second Triangle
    };
    GLuint VAO,VBO,EBO;

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs),vertexs,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indics),indics,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(3*(sizeof(GLfloat))));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(6*(sizeof(GLfloat))));
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);

    GLuint texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // 为当前绑定的纹理对象设置环绕、过滤方式

    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	// Set texture wrapping to GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINE);

    int width,height;
    unsigned  char *image = SOIL_load_image("/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/res/image/timg.jpeg",
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
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(shader.Program,"ourTexture"),0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&EBO);

    glfwTerminate();

    return 0;
}


#endif /* texture_h */
