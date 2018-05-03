//
//  main.cpp
//  BaseOpenGL
//  Copyright © 2018年 emery. All rights reserved.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "hello_triangle.h"
extern "C" {
#include "SOIL2/SOIL2.h"
}
#include "res/shaders/shader.h"
#include "res/shaders/shader_sample.h"
int main(int argc, const char * argv[]) {
    
   // hello_triangle_main();
    
   // shader_sample_main();

    int width=200;
    int height=100;
    unsigned char* image = SOIL_load_image("/Users/emery/AppcodeProjects/OpenGL_Xcode/BaseOpenGL/res/image/tips.png",
            &width, &height, 0, SOIL_LOAD_RGBA);

    std::cout<<&image<<std::endl;
    return 0;
    
}
