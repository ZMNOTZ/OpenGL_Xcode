//
// Created by 张瑞 on 2018/5/5.
// Copyright (c) 2018 emery. All rights reserved.
//

#ifndef BASEOPENGL_TRANSFORM_H
#define BASEOPENGL_TRANSFORM_H

#import <iostream>
// Include GLM core features
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>

#include <glm/glm.hpp>
// Include GLM extensions
#include <glm/gtc/matrix_transform.hpp>



int gl_matrix_transform_main(){

    return 0;
}

int maxtrix_transform_test(){
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4x4 trans={
            1.0f,0.0f,0.0f,0.0f,
            0.0f,1.0f,0.0f,0.0f,
            0.0f,0.0f,1.0f,0.0f,
            0.0f,0.0f,0.0f,1.0f,
    };
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    for (int i = 0; i < trans.length(); ++i) {
        for (int j = 0; j <trans.length(); ++j) {
            std::cout<<"trans["<<i<<"]"<<"["<<j<<"]="<< trans[i][j]<<std::endl;
        }
    }
    std::cout << vec.x << vec.y << vec.z << std::endl;

    glm::mat4 mat4;
    std::cout<<"mat4"<<std::endl;
    for (int i = 0; i < mat4.length(); ++i) {
        for (int j = 0; j <mat4.length(); ++j) {
            //std::cout<<"mat4["<<i<<"]"<<"["<<j<<"]="<< mat4[i][j]<<std::endl;
                    std::cout<<mat4[i][j]<<",";
        }
        std::cout<<std::endl;
    }
    return 0;
}

#endif //BASEOPENGL_TRANSFORM_H
