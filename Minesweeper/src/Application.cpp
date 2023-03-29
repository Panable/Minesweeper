#include <fstream>
#include <iostream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//
std::string LoadShader(const char* path)
{
    std::ifstream shaderFile(path);
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//
unsigned int InitializeShader()
{
    //reading file into string
    std::string vertexShaderString, fragmentShaderString;

    vertexShaderString = LoadShader("res/shaders/basic/vertex.shader");
    fragmentShaderString = LoadShader("res/shaders/basic/fragment.shader");

    const char* vertexShaderCode = vertexShaderString.c_str();
	const char* fragmentShaderCode = fragmentShaderString.c_str();

    //'id'
    unsigned int vertexShader, fragmentShader;

    //Create shaders
    vertexShader = glCreateShader(GL_VERTEX_SHADER);


    //Attach Shader code to shaders.
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);

    //ERROR TEST THE SHADER
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //ERROR TEST THE SHADER
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //create shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

    //attach shaders to shader program
    glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //ERROR TEST THE SHADER
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Delete shaders (they are used in shader program)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    
    return shaderProgram;
}

unsigned int GenerateVAO()
{
    //vertices of our triangle
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


    //VBO is just data

    //VAO has the VBO inside it, but it also defines how the data is laid out

    unsigned int VBO, VAO, EBO; //object 'ids'. These are the references used to bind these

    //Generate the 'id's for the VBO and VAO and stores them in the variables defined above
    //What this does is find an unused id then assigns them sort of like PK in sql
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO); //attaches the VAO to the gpu
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //attaches the VBO to the gpu
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    //NOTE: WHEN THE VBO IS BOUND IT IS AUTOMATICALLY ASSOCIATED WITH THE VAO AND NOW
    //THEY ARE LINKED

    //pushes data to the vbo object on the GPU
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //GL_STATIC_DRAW -> vertices selected once drawn many
    //GL_DYNAMIC -> vertices changed a lot drawn a lot

    //defines the layout of the VBO (STORED ON THE VAO) 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    //THIS ENABLES THE ATTRIB POINTER THINGS ABOVE ON THE VAO. DON'T FORGET TO DO THIS FOR EACH.
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    //UNBIND EVERYTHING
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);

	return VAO; //RETURN THE VAO (id of the VAO) to be used by the application later
}

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

    unsigned int shaderProgram = InitializeShader();
    unsigned int VAO = GenerateVAO();
    std::cout << VAO << std::endl;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

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