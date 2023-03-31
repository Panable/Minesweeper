//STD LIBRARY
#include <fstream>
#include <iostream>
#include <sstream>
#include <Debug.h>
//OPENGL STUFF
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//MY INCLUDES
#include "IndexBufferObject.h"
#include "ShaderProgram.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include <stb_image/stb_image.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{

    //Initialize GLFW and set opengl version
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << glGetString(GL_VERSION) << std:: endl;

    //DATA
    float vertices[] =
    {
        //x     y       z     r     g   b
        ////
        //COORDINATES       |     COLOR           | TEX COORD
        -0.5f,  -0.5f,  0.0f,  1.0f, 0.0f, 0.0f,   0.0f, 0.0f,        //bottom - left
         0.5f,  -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,          // bottom - right
        -0.5f,   0.5f,  0.0f,  0.0f, 0.0f, 1.0f,   0.0f, 1.0f,          //top - left
         0.5f,   0.5f,  0.0f,  1.0f, 0.0f, 0.0f,   1.0f, 1.0f            //top -  right
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        1, 2, 3
    };


    //VAO GENERATION
    const VertexArrayObject VAO1;
    VAO1.Bind();

    const VertexBufferObject VBO1(vertices, sizeof(vertices));
    const IndexBufferObject IBO1(indices, sizeof(indices));

    //COORDS
    const int numCoords = 3;
    const int numColors = 3;
    const int numTextCoords = 2;
    const int stride = (numCoords + numColors + numTextCoords) * sizeof(float);

    VAO1.LinkAttrib(VBO1, 0, numCoords, GL_FLOAT, stride, (void*)0);

    VAO1.LinkAttrib(VBO1, 1, numColors, GL_FLOAT, stride, (void*)(numCoords * sizeof(float)));

    VAO1.LinkAttrib(VBO1, 2, numTextCoords, GL_FLOAT, stride, (void*)((numCoords + numColors) * sizeof(float)));

    VBO1.Unbind();
    VAO1.Unbind();
    IBO1.Unbind();

    //TEXTURE GENERATION


    const char* filePath ="res/texture/brick.png";
    int width, height, colorChannel;

    unsigned char* data = stbi_load(filePath, &width, &height, &colorChannel, 4);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    if (data)
    {
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	    glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
	    std::cout << "ERROR LOADING TEXTURE AT " << filePath << std::endl;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    //SHADER GENERATION
    const ShaderProgram shader1("res/shaders/basic/vertex.shader", "res/shaders/basic/fragment.shader");
    const ShaderProgram shader2("res/shaders/basic/vertex.shader", "res/shaders/basic/fragmentUniform.shader");

    shader2.Activate();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    shader2.Set1i("ourTexture", 0);


    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        shader2.Activate();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}