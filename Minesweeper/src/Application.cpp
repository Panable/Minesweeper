//STD LIBRARY
#include <fstream>
#include <iostream>
#include <sstream>

//OPENGL STUFF
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//MY INCLUDES
#include "IndexBufferObject.h"
#include "ShaderProgram.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"


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
        //COORDINATES     |     COLOR  
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom - left
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom - right
        -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, //top
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        1, 2,3
    };

    //VAO GENERATION
    const VertexArrayObject VAO1;
    VAO1.Bind();

    const VertexBufferObject VBO1(vertices, sizeof(vertices));
    const IndexBufferObject IBO1(indices, sizeof(indices));

    //COORDS
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);

	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VBO1.Unbind();
    VAO1.Unbind();
    IBO1.Unbind();

    //SHADER GENERATION
    const ShaderProgram shader1("res/shaders/basic/vertex.shader", "res/shaders/basic/fragment.shader");
    const ShaderProgram shader2("res/shaders/basic/vertex.shader", "res/shaders/basic/fragmentUniform.shader");

    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        shader2.Activate();
        shader2.SetVector4f("ourColor", glm::vec4(1.0f, greenValue, 0.0f, 1.0f));
        VAO1.Bind();
        //params 1: what type of shape to draw
        //params 2: what vertex in the array should we start with
        //params 3: how many vertices are we rendering?
        glDrawArrays(GL_TRIANGLES, 0, 3);
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

inline VertexArrayObject GenerateVAO()
{
	float vertices[] =
	{
		//x     y       z     r     g   b
		////
		//COORDINATES     |     COLOR  
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom - left
		0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,// bottom - right
		-0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, //top
		0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f
	};

	unsigned int indices[] =
	{
		0, 1, 2,
		1, 2,3
	};




	unsigned int EBO;

	VertexArrayObject VAO1;
	VAO1.Bind();
	VertexBufferObject VBO1(vertices, sizeof(vertices));

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VBO1.Unbind();
	VAO1.Unbind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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