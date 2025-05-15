//
//#include <iostream>
//#include <stdio.h>
//#include<string.h>
//
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
////WIndow's Dimensions
//const GLint WIDTH = 800, HEIGHT = 600;
//
//GLuint VAO, VBO, shader, uniformXMove;
//
//bool direction = true;
//float triOffset = 0.0f;
//float triMaxOffset = 0.7f;
//float triIncrement = 0.005f;
//
//
//
//// Vertex Shader code
//static const char* vShader = "                                                \n\
//#version 330                                                                  \n\
//                                                                              \n\
//layout (location = 0) in vec3 pos;											  \n\
//                                                                              \n\
//uniform float xMove;                                                          \n\
//                                                                              \n\
//void main()                                                                   \n\
//{                                                                             \n\
//    gl_Position = vec4(0.4 * pos.x + xMove, 0.4 * pos.y, pos.z, 1.0);				  \n\
//}";
//
//// Fragment Shader
//static const char* fShader = "                                                \n\
//#version 330                                                                  \n\
//                                                                              \n\
//out vec4 colour;                                                               \n\
//                                                                              \n\
//void main()                                                                   \n\
//{                                                                             \n\
//    colour = vec4(1.0, 0.0, 0.0, 1.0);                                         \n\
//}";
//
//
////glm::mat4 model = glm::mat4(1.0f);
//
//void CreateTriangle()
//{
//    GLfloat vertices[] = {
//        -1.0f, -1.0f, 0.0f,
//        1.0f, -1.0f, 0.0f,
//        0.0f, 1.0f, 0.0f
//    };
//
//
//    glGenVertexArrays(1, &VAO);
//    glBindVertexArray(VAO);
//
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //should  say sizeof(GLfloat) but since vertices only 9, its correct 
//    //GL_STATIC_DRAW means we aren't modifying the vertices array
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    //the 3 in size is for x,y,z coordinates
//    //stride is like ML CNNs
//    glEnableVertexAttribArray(0);//Enables the attribute index for the position attribute
//
//    //Essentially unbinding it
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);
//
//
//}
//
//void AddShader(GLuint theprogram, const char* shaderCode, GLenum shaderType)
//{
//    GLuint theShader = glCreateShader(shaderType); //create empty shader of that type
//
//    const GLchar* theCode[1]; //where we store the code
//    theCode[0] = shaderCode;
//
//    GLint codeLength[1]; // length of the code
//    codeLength[0] = strlen(shaderCode);
//
//    //source code for our shaders
//    // the in-memory theShader has the code modified 
//    glShaderSource(theShader, 1, theCode, codeLength);
//
//    glCompileShader(theShader);
//
//    GLint result = 0; //result of the 2 function AddShader
//
//    /*
//        a place to log the error if nothing works.
//        We actually need this, considering this will become a difficult place to debug,
//        so a log is absolutely necessary here.
//        Not to mention tht the vShader and fShader we've defined are not captured by
//        intellisense or the debugger
//    */
//    GLchar eLog[1024] = { 0 };
//
//    //create executables on GPU
//
//    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
//    if (!result)
//    {
//        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
//        printf("Error compiling the  %d shader: '%s'\n", shaderType, eLog);
//        return;
//    }
//
//    //attach to the program 
//    glAttachShader(theprogram, theShader);
//}
//
//
//void CompileShader()
//{
//    shader = glCreateProgram();
//
//    if (!shader)
//    {
//        printf("Error creating shader program!\n");
//        return;
//    }
//
//    //when we compile the shader, we need to describe the type of shader it will be
//    AddShader(shader, vShader, GL_VERTEX_SHADER);
//    AddShader(shader, fShader, GL_FRAGMENT_SHADER);
//
//    //we need to link the program and get the program --not as easy as it is
//    GLint result = 0; //result of the 2 function AddShader
//
//    /*
//        a place to log the error if nothing works.
//        We actually need this, considering this will become a difficult place to debug,
//        so a log is absolutely necessary here.
//        Not to mention tht the vShader and fShader we've defined are not captured by
//        intellisense or the debugger
//    */
//    GLchar eLog[1024] = { 0 };
//
//    //create executables on GPU
//    glLinkProgram(shader);
//
//    glGetProgramiv(shader, GL_LINK_STATUS, &result);
//    if (!result)
//    {
//        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
//        printf("Error linking program: '%s'\n", eLog);
//        return;
//    }
//
//    //validate program
//    //this is checking if the shader is valid with the current context that GL is working with
//    glValidateProgram(shader);
//
//    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
//    if (!result)
//    {
//        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
//        printf("Error validating program: '%s'\n", eLog);
//        return;
//    }
//
//    uniformXMove = glGetUniformLocation(shader, "xMove");
//
//
//
//}
//
//int main()
//{
//    //Initialize GLFW
//    if (!glfwInit())
//    {
//        printf("GLFW Initialization failed....");
//        glfwTerminate();
//        return 1;
//    };
//
//    // Setup GLFW Window properties
//    //OpenGL version
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//
//    //remove deprecated core profile = No backwards compatibility
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //allow forward compatibility
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT,
//        "Test Window", NULL, NULL);
//
//    if (!main)
//    {
//        printf("GLFW window creation failed!");
//        glfwTerminate(); return 1;
//    }
//
//
//    //Get Buffer size information
//    int bufferWidth, bufferHeight;
//    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
//
//    // Set context for GLEW to use
//    glfwMakeContextCurrent(mainWindow);
//
//
//    // Allow modern extension features
//    glewExperimental = GL_TRUE;
//
//    if (glewInit() != GLEW_OK)
//    {
//        printf("GLEW initialization failed!");
//        glfwDestroyWindow(mainWindow);
//        glfwTerminate(); return 1;
//    }
//
//
//    //Setup Viewport size
//    glViewport(0, 0, bufferWidth, bufferHeight);
//
//    CreateTriangle();
//    CompileShader();
//    //glfwSwapInterval(3);
//
//    // Loop until window closed
//    while (!glfwWindowShouldClose(mainWindow))
//    {
//        // Get + Handle user input events
//        glfwPollEvents();
//
//        // Clear window uses RGB values DIVIDED by 256
//        // So, a 128 / 256 would be 0.5f
//        //the last paramter, alpha is just transparent
//        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glUseProgram(shader); //to assign and make the shader in window
//
//        //indent
//        glBindVertexArray(VAO);
//        //bunch of mode first parameter, triangle assumes 3
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glBindVertexArray(0);
//
//
//        glUseProgram(0);
//
//        glfwSwapBuffers(mainWindow);
//
//    }
//
//    return 0;
//}