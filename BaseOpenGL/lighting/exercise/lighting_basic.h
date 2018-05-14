//
// Created by 张瑞 on 2018/5/13.
// Copyright (c) 2018 emery. All rights reserved.
//

#ifndef BASEOPENGL_LIGHTING_BASIC_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SOIL2.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "lighting_basic_camera.h"

#define BASEOPENGL_LIGHTING_BASIC_H



void key_callback(GLFWwindow*,int,int,int,int);
void scroll_callback(GLFWwindow*,double,double);
void mouse_callback(GLFWwindow*,double,double);
void do_movement();

glm::vec3 lightPos ;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

bool firstMove = true;
bool keys[1024];
GLfloat lastX;
GLfloat lastY;

GLfloat deltaTime;
GLfloat lastFrame;

int lighting_basic_main(){

    GLuint width=800,height=600;
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, "learn opengl lighting", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glewExperimental = GL_TRUE;
    glewInit();

    Shader objectShader(
            "/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/lighting/exercise/lighting_basic.vs",
            "/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/lighting/exercise/lighting_basic.frag");

    Shader lampShader(
            "/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/lighting/exercise/lighting_lamp.vs",
            "/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/lighting/exercise/lighting_lamp.frag"
            );


    GLfloat vetexces[]={

    };

    GLuint VAO,VBO;

    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vetexces),vetexces,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6* sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6* sizeof(GLfloat),(GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        glClearColor(.2f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        objectShader.use();
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        view = camera.GetViewMatrix();
        projection = glm::perspective(camera.fov,(GLfloat)width/(GLfloat)height , 0.1, 100.0f);

        glUniform4fv(glGetUniformLocation(objectShader.Program,"model"),1,glm::value_ptr(model));
        glUniform4fv(glGetUniformLocation(objectShader.Program,"view"),1,glm::value_ptr(view));
        glUniform4fv(glGetUniformLocation(objectShader.Program,"projection"),1,glm::value_ptr(projection));

        glUniform3f(glGetUniformLocation(objectShader.Program,"lightPos"),lightPos.x,lightPos.y,lightPos.z);
        glUniform3f(glGetUniformLocation(objectShader.Program,"lightColor"),1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(objectShader.Program,"objectColor"),1.0f, 0.5f, 0.31f);

        //draw objection
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        lampShader.use();

        //draw lamp
        lightPos.x = sin(glfwGetTime());
        lightPos.z = cos(glfwGetTime());

        model = glm::translate(model, lightPos);
        glUniformMatrix4fv(glGetUniformLocation(lampShader.Program,"model"),1,GL_FALSE,glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(lampShader.Program,"view"),1,GL_FALSE,glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(lampShader.Program,"projection"),1,GL_FALSE,glm::value_ptr(projection));
        //draw lamp
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);

    glfwTerminate();

    return -1;
}
void key_callback(GLFWwindow* window,int key,int scanMode,int action,int mode) {
    if (GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }

}
void mouse_callback(GLFWwindow* window,double xPos, double yPos){
    // Calculate deltatime of current frame
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if(firstMove){
       lastX = xPos;
       lastY = yPos;
       firstMove = false;
    }

    GLfloat xOffset = lastX - xPos;
    GLfloat yOffset = lastY - yPos;
    lastX = xPos;
    lastY = yPos;
    camera.ProcessMouseMovement(xOffset, yOffset, true);
}
void scroll_callback(GLFWwindow* window,double xOffset,double yOffset){
    camera.ProcessMouseScroll(yOffset);
}
void do_movement(){
    if(keys[GLFW_KEY_W]){
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if(keys[GLFW_KEY_S]){
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if(keys[GLFW_KEY_L]){
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if(keys[GLFW_KEY_R]){
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}
#endif //BASEOPENGL_LIGHTING_BASIC_H
