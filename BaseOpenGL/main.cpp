//
//  main.cpp
//  BaseOpenGL
//  Copyright © 2018年 emery. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/OpenGL.h>



void render(void){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    {
        glColor3f(1.0f,0.0f, 0.0f);
        glVertex2f(0, .5);
        
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex2f(-.5f, -.5f);
        
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex2f(.5f, -.5f);
    }
    glEnd();
    glFlush();
}
int main(int argc, const char * argv[]) {
    GLFWwindow *win;
    if(!glfwInit()){
        return -1;
    }
    
    win = glfwCreateWindow(640, 480, "OpenGL Base Project", NULL, NULL);
                           
    if(!win){
       glfwTerminate();
       exit(EXIT_FAILURE);
    }
                           
   if(!glewInit()){
       return -1;
   }
                           
    glfwMakeContextCurrent(win);
   while(!glfwWindowShouldClose(win)){
       render();
       glfwSwapBuffers(win);
       glfwPollEvents();
   }
   glfwTerminate();
   exit(EXIT_SUCCESS);
   
    return 0;
}
