//
// Created by 张瑞 on 2018/5/13.
// Copyright (c) 2018 emery. All rights reserved.
//

#ifndef BASEOPENGL_LIGHTING_BASIC_CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define BASEOPENGL_LIGHTING_BASIC_CAMERA_H
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
typedef enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} CameraMovement;

// Default camera values
const GLfloat YAW        = -90.0f;
const GLfloat PITCH      =  0.0f;
const GLfloat SPEED      =  3.0f;
const GLfloat SENSITIVTY =  0.25f;
const GLfloat ZOOM       =  45.0f;


class Camera {
public:
    GLfloat fov;
    GLfloat mouseSensitivity;
    GLfloat moveSpeed;

    glm::vec3 cameraPos;

    glm::vec3 cameraFront;
    glm::vec3 wordUp;

    Camera(glm::vec3 cameraPos = glm::vec3(0.0f,0.0f,0.0f),glm::vec3 wordUp = glm::vec3(0.0f,1.0f,0.0f),glm::vec3 cameraFont = glm::vec3(0.0f,0.0f,-1.0f)):yaw(YAW),pitch(PITCH),mouseSensitivity(SENSITIVTY),moveSpeed(SPEED),fov(ZOOM){
        this->cameraPos = cameraPos;
        this->wordUp = wordUp;
        this->cameraFront = cameraFont;
        this->updateCameraVectors();
    }
    void ProcessMouseScroll(GLfloat yOffset);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
    void ProcessKeyboard(CameraMovement movement,GLfloat deltaTime);

    glm::mat4 GetViewMatrix() const {
        // lookAt(position,target,up) 理论上：cameraPos - target = direction = - cameraFront ,所以 target = cameraPos + cameraFont
        return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    }

private:
    GLfloat pitch;
    GLfloat yaw;

    glm::vec3 cameraRight;
    glm::vec3 cameraUp;

    void updateCameraVectors();

};

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch){

    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(constrainPitch){
        if(pitch > 90.0f){
            pitch = 90.0f;
        }
        if(pitch < -89.0f){
            pitch = -89.0f;
        }
    }
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yOffset) {
    if(fov > 1.0f && fov < 45.0f){
        fov-= yOffset;
    }
    if( fov > 45.0f){
        fov = 45.0f;
    }
    if( fov < 1.0f){
        fov = 1.0f;
    }
}

/**
 * 处理do_movement
 *
 * @param direction
 * @param deltaTime
 */
void Camera::ProcessKeyboard(CameraMovement direction, GLfloat deltaTime) {

    GLfloat velocity = this->moveSpeed * deltaTime;
   if(direction == FORWARD){
       cameraPos += velocity * cameraFront;
   }
   if(direction == BACKWARD){
       cameraPos -= velocity * cameraFront;
   }
   if(direction == LEFT){
       cameraPos -= velocity * cameraRight;
   }
   if(direction == RIGHT){
       cameraPos += velocity * cameraRight;
   }
}

void Camera::updateCameraVectors() {
    //front 和 camera direction 方向相反
    glm::vec3 front;
    front.x = glm::cos(glm::radians(yaw)) + glm::cos(glm::radians(pitch));
    front.y = glm::sin(glm::radians(pitch));
    front.z = glm::sin(glm::radians(yaw)) + glm::cos(glm::radians(pitch));

    cameraFront = glm::normalize(front);

    cameraRight = glm::normalize(glm::cross(cameraFront,wordUp));
    cameraUp = glm::normalize(glm::cross(cameraRight,cameraFront));
}
#endif //BASEOPENGL_LIGHTING_BASIC_CAMERA_H
