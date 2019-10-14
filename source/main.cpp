#include <iostream>
#include <GLFW/glfw3.h>


static void error_callback ( int error, const char* description ) {
    fprintf ( stderr, "Error: %s\n", description );
}

static void key_callback ( GLFWwindow* window, int key, int scancode, int action, int mods ) {
    if ( key == GLFW_KEY_ESCAPE && action == GLFW_PRESS )
        glfwSetWindowShouldClose ( window, GLFW_TRUE );
}

int main ( int argc, char **argv ) {
    glfwSetErrorCallback ( error_callback );
    if ( ! glfwInit() ) {
        std::cout << "GLFW Initialization failed" << std::endl;
        return 1;
    }
	std::cout << "GLFW Initialization successful" << std::endl;


    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 0 );
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 2 );

    GLFWwindow* window = glfwCreateWindow ( 640, 480, "Welcome to the MVD!", NULL, NULL );
    if ( ! window ) {
        std::cout << "Window Initialization failed" << std::endl;
        glfwTerminate();
        return 0;
    }
    std::cout << "Window Initialization successful" << std::endl;

    glfwSetKeyCallback ( window, key_callback );

    glfwMakeContextCurrent ( window );
    glfwSwapInterval ( 1 );
    
    while ( !glfwWindowShouldClose ( window ) ) {
        int width, height;
        glfwGetFramebufferSize ( window, &width, &height );
        glViewport ( 0, 0, width, height );

        glfwSwapBuffers ( window );
        glfwPollEvents();
    }

    glfwDestroyWindow ( window );
    glfwTerminate();
    return 0;
}
