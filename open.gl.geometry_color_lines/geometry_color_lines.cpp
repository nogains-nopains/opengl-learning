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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;


//#define LINES

// Shader macro
#define GLSL(src) "#version 150 core\n" #src

// Vertex shader
const GLchar* vertexShaderSrc = GLSL(
in vec2 pos;
in vec3 color;

out vec3 vColor; // Output to geometry (or fragment) shader

void main() {
    gl_Position = vec4(pos, 0.0, 1.0);
    vColor = color;
}
);

// Geometry shader
#ifdef LINES
const GLchar* geometryShaderSrc = GLSL(

layout(points) in;
layout(line_strip, max_vertices = 2) out;
in vec3 vColor[]; // Output from vertex shader for each vertex
out vec3 fColor; // Output to fragment shader

void main() {
    fColor = vColor[0]; // Point has only one vertex

    gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.1, 0.0, 0.0);
    EmitVertex();

    EndPrimitive();
}
);

#else

const GLchar* geometryShaderSrc = GLSL(

    // squares
layout(points) in;
layout(line_strip, max_vertices = 5) out;
in vec3 vColor[]; // Output from vertex shader for each vertex
out vec3 fColor; // Output to fragment shader

    void main() {
         fColor = vColor[0]; // Point has only one vertex

        gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1, 0.0, 0.0);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.1, 0.0, 0.0);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + vec4(0.1, -0.1, 0.0, 0.0);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + vec4(-0.1, -0.1, 0.0, 0.0);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.1, 0.0, 0.0);
        EmitVertex();

        EndPrimitive();
    }
);
#endif

// Fragment shader
const GLchar* fragmentShaderSrc = GLSL(
in vec3 fColor;

out vec4 outColor;

void main() {
    outColor = vec4(fColor, 1.0);
}
);

// Shader creation helper
GLuint createShader(GLenum type, const GLchar* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}

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
    window = glfwCreateWindow( 1024, 768, "OpenGL -Circles", NULL, NULL);
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

   // Compile and activate shaders
    GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint geometryShader = createShader(GL_GEOMETRY_SHADER, geometryShaderSrc);
    GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, geometryShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Create VBO with point coordinates
    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat points[] = {
    -0.45f,  0.45f, 1.0f, 0.0f, 0.0f, // Red point
     0.45f,  0.45f, 0.0f, 1.0f, 0.0f, // Green point
     0.45f, -0.45f, 0.0f, 0.0f, 1.0f, // Blue point
    -0.45f, -0.45f, 1.0f, 1.0f, 0.0f, // Yellow point
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Create VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Specify layout of point data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "pos");
    glEnableVertexAttribArray(posAttrib);
glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
glEnableVertexAttribArray(colAttrib);
glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,
                      5 * sizeof(float), (void*) (2 * sizeof(float)));
    do{

      // Render frame
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_POINTS, 0, 4);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0 );

    // Cleanup VBO and shader
    glDeleteProgram(shaderProgram);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

