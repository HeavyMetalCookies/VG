
//:Include Vulkan:
//:#include "V:/VK_HEAD/include/vulkan/vulkan.h" 

#define GLFW_INCLUDE_VULKAN
#include "V:\DEPS\GLFW\include\GLFW\glfw3.h"

#include <stdio.h> //:for: printf(...)

struct 玉星{

    GLFWwindow* win;

}玉星;

void 玉星_initWindow(){

    //:DontCreateOpenGLContext:
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    //:For simplicity, disable window resize:
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    玉星.win=(
        glfwCreateWindow(800,600,"VULKAN",NULL,NULL)
    );;

}
// 
// void VG_run(){
//     initWindow();
//     initVulkan();
//     mainLoop();
//     cleanup();
// }

int 玉星_Demo(){
    printf("[玉星_Demo()...]\n");
    return( 0 );
}