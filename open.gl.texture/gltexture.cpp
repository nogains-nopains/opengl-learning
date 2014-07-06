// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <common/shader.hpp>
//#include <common/texture.hpp>

#include <3rdparty/soil/src/SOIL.h>

//#define KITTEN

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "OpenGL - Textured KITTEN", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

    // Create Vertex Array Object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	static const GLfloat g_vertex_buffer_data[] = {
       //  Position   Color             Texcoords
        -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top-left
         0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Top-right
         0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


    // Create an element array
    GLuint ebo;
    glGenBuffers(1, &ebo);
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);


    // Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );


    // Load texture
    GLuint tex;
    glGenTextures(1, &tex);

#ifdef KITTEN
    int width, height;
    unsigned char* image = SOIL_load_image("kitten.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);
#else
    // Black/white checkerboard (4X4)
    float pixels[] = {
        0.0f, 0.0f, 0.0f,     1.0f, 1.0f, 1.0f,      0.0f, 0.0f, 0.0f,      1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 0.0f,      1.0f, 1.0f, 1.0f,      0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,     1.0f, 1.0f, 1.0f,      0.0f, 0.0f, 0.0f,      1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,     0.0f, 0.0f, 0.0f,      1.0f, 1.0f, 1.0f,      0.0f, 0.0f, 0.0f
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,    4,      4,     0,  GL_RGB, GL_FLOAT, pixels);
//                                          width  height
#endif

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_LINEAR);



    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(programID, "position");
    glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(
		posAttrib,          // attribute. No particular reason for 0, but must match the layout in the shader.
		2,                  // size : 3 floats for each vertex ==>g_vertex_buffer_data
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		7 * sizeof(GLfloat),                  // stride
		(void*)0            // array buffer offset
	);

    GLint colAttrib = glGetAttribLocation(programID, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    GLint texAttrib = glGetAttribLocation(programID, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));


	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

        // Draw a rectangle from the 2 triangles using 6 indices
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &vao);
    glDeleteTextures(1, &tex);
    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

