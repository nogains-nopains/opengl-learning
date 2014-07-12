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

// Shader macro
#define GLSL(src) "#version 150 core\n" #src

// Vertex shader
const GLchar* vertexShaderSrc = GLSL(
    in vec2 pos;
    in vec3 color;
    in float sides;

    out vec3 vColor;
    out float vSides;

    void main() {
        gl_Position = vec4(pos, 0.0, 1.0);
        vColor = color;
        vSides = sides;
    }
);

// Geometry shader
const GLchar* geometryShaderSrc = GLSL(
    layout(points) in;
    layout(line_strip, max_vertices = 64) out;

    in vec3 vColor[];
    in float vSides[];
    out vec3 fColor;

    const float PI = 3.1415926;

    void main() {
        fColor = vColor[0];

        // Safe, GLfloats can represent small integers exactly
        for (int i = 0; i <= vSides[0]; i++) {
            // Angle between each side in radians
            float ang = PI * 2.0 / vSides[0] * i;

            // Offset from center of point (0.3 to accomodate for aspect ratio)
            vec4 offset = vec4(cos(ang) * 0.3, -sin(ang) * 0.4, 0.0, 0.0);
            gl_Position = gl_in[0].gl_Position + offset;

            EmitVertex();
        }

        EndPrimitive();
    }
);

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
    //  Coordinates  Color             Sides
        -0.45f,  0.45f, 1.0f, 0.0f, 0.0f,  4.0f,
         0.45f,  0.45f, 0.0f, 1.0f, 0.0f,  8.0f,
         0.45f, -0.45f, 0.0f, 0.0f, 1.0f, 16.0f,
        -0.45f, -0.45f, 1.0f, 1.0f, 0.0f, 32.0f
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
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat)));

    GLint sidesAttrib = glGetAttribLocation(shaderProgram, "sides");
    glEnableVertexAttribArray(sidesAttrib);
    glVertexAttribPointer(sidesAttrib, 1, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*) (5 * sizeof(GLfloat)));
    
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

