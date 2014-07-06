// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <common/shader.hpp>

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
	window = glfwCreateWindow( 1024, 768, "Triangle : triangle", NULL, NULL);
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

	//get the open gl version string:
	const GLubyte * ver = glGetString(GL_VERSION);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

        //Vertex Array Objects
        //
        //You can imagine that real graphics programs use many different shaders and vertex 
        // layouts to take care of a wide variety of needs and special effects. Changing
        // the active shader program is easy enough with a call to glUseProgram, but it
        // would be quite inconvenient if you had to set up all of the attributes again every time.
        //
        //Luckily, OpenGL solves that problem with Vertex Array Objects (VAO). VAOs store 
        // all of the links between the attributes and your VBOs with raw vertex data.
        //A VAO is created in the same way as a VBO:
	GLuint vao;
	glGenVertexArrays(1, &vao);
        //To start using it, simply bind it:
	glBindVertexArray(vao);
        //As soon as you've bound a certain VAO, every time you call glVertexAttribPointer,
        // that information will be stored in that VAO. This makes switching between 
        // different vertex data and vertex formats as easy as binding a different VAO!
        // Just remember that a VAO doesn't store any vertex data by itself, it just 
        // references the VBOs you've created and how to retrieve the attribute values from them.
        //
        //Since only calls after binding a VAO stick to it, make sure that you've created
        // and bound the VAO at the start of your program.
        //

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );



	//static const GLfloat g_vertex_buffer_data[] = { 
	//	-10.0f, -1.0f, 0.0f,
	//	 1.0f, -1.0f, 0.0f,
	//	 0.0f,  1.0f, 0.0f,
	//};
    
    //Step 1: define the vertices:
    static const GLfloat g_vertex_buffer_data[] = {
        0.0f,  0.5f, // Vertex 1 (X, Y)
        0.5f, -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f  // Vertex 3 (X, Y)
    };

	GLuint vertexbuffer;
    
    //Step 2: upload this vertex data to the graphics card.
    // This is important because the memory on your graphics 
    // card is much faster and you won't have to send the data
    // again every time your scene needs to be rendered 
    // (about 60 times per second).
    // This is done by creating a Vertex Buffer Object (VBO):

    //The memory is managed by OpenGL, so instead of a pointer 
    // you get a positive number as a reference to it. GLuint 
    // is simply a cross-platform substitute for unsigned int, 
    // just like GLint is one for int. You will need this number 
    // to make the VBO active and to destroy it when you're 
    // done with it.
	glGenBuffers(1, &vertexbuffer);
    
    //This statement makes the VBO we just created the active array buffer.
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    
    //Now that it's active we can copy the vertex data to it.  
    //GL_STATIC_DRAW: The vertex data will be uploaded once and drawn many times (e.g. the world).
    //GL_DYNAMIC_DRAW: The vertex data will be changed from time to time, but drawn many times more than that.
    //GL_STREAM_DRAW: The vertex data will change almost every time it's drawn (e.g. user interface).
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    //The vertices with their attributes have been copied to the graphics card now, 
    // but they're not quite ready to be used yet. Remember that we can make up any
    // kind of attribute we want and in any order, so now comes the moment where you
    // have to explain to the graphics card how to handle these attributes. This is
    // where you'll see how flexible modern OpenGL really is.


	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader. To actually start using the shaders in the program,
		glUseProgram(programID);

    GLint uniColor = glGetUniformLocation(programID, "triangleColor");
float time = (float)clock() / (float)1500;
glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

        //Making the link between vertex data and attributes
        //Although we have our vertex data and shaders now, OpenGL still doesn't 
        //know how the attributes are formatted and ordered. You first need to
        //retrieve a reference to the position input in the vertex shader:
        GLint posAttrib = glGetAttribLocation(programID, "position");
        //The location is a number depending on the order of the input definitions. 
        //The first and only input position in this example will always have location 0.

		// 1rst attribute buffer : vertices
  //       GLint posAttrib = 0;
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

        //  specify how the data for that input is retrieved from the array:
		glVertexAttribPointer(
			posAttrib,          // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size of the g_vertex_buffer_data,  the number of values for that input, which is the same as the number of components of the vec.
			GL_FLOAT,           // type
			GL_FALSE,           // normalized between -1.0 and 1.0 (or 0.0 and 1.0 depending on the format)  if they aren't floating point numbers.?
			0,                  // stride
			(void*)0            // array buffer offset
		);
        //It is important to know that this function will store not only the stride and the offset, 
        //but also the VBO that is currently bound to GL_ARRAY_BUFFER. That means that
        //you don't have to explicitly bind the correct VBO when the actual drawing 
        //functions are called. This also implies that you can use a different VBO for each attribute.

        //Last, but not least, the vertex attribute array needs to be enabled.
		glEnableVertexAttribArray(posAttrib);


		// Draw the triangle !
        //Now that you've loaded the vertex data, created the shader programs and
        // linked the data to the attributes, you're ready to draw the triangle. 
        // The VAO that was used to store the attribute information is already 
        // bound, so you don't have to worry about that. All that's left is to 
        // simply call glDrawArrays in your main loop:
		glDrawArrays(GL_TRIANGLES, 0, 3); // 3 indices starting at 0 -> 1 triangle

//why do I have to enable and disable vertex attribute arrays in the first place? 
//In order to tell OpenGL which attribute arrays are valid and which are not.
//Remember: OpenGL is a state machine. When you call glVertexAttribPointer, that basically sets fields in a struct. And state always has a value. There's no way to call glVertexAttribPointer and say, "This attribute doesn't matter anymore; don't use it."
//That's what the enable/disable calls are for. To tell OpenGL whether or not it should use the state for that attribute. 
//
//The state of which Vertex Attribute Arrays are enabled can be either bound to a Vertex Array Object (VAO), or be global.
//If you're using VAOs, then you should not disable attribute arrays, as they are encapsulated in the VAO.
//However for global vertex attribute array enabled state you should disable them, because if they're left enabled OpenGL will try to read from arrays, which may be bound to a invalid pointer, which may either crash your program if the pointer is to client address space, or raise a OpenGL error if it points out of the limits of a bound Vertex Buffer Object.

		glDisableVertexAttribArray(0);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteVertexArrays(1, &vao);
	glDeleteProgram(programID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

