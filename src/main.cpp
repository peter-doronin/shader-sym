#include <GL/glew.h>
#include <GL/glut.h>

#include <string>
#include <vector>
void reshape(int w, int h)
{
        glViewport(0, 0, w, h);
       
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0, w, 0, h);
       
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}

void display()
{
        glClear(GL_COLOR_BUFFER_BIT);
       
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2i(250, 450);
        glColor3f(0.0, 0.0, 1.0);
        glVertex2i(250, 150);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2i(550, 150);
        glColor3f(1.0, 0.0, 0.0);
        glVertex2i(550, 450);
        glEnd();
       
        glutSwapBuffers();
}

std::string fragmentSource = "\
#version 330 core \
out vec4 FragColor;\
  \
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  \
\
void main()\
{\
    FragColor = vertexColor;\
} \
int main (int argc, char * argv[])\
{\
 ";
GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
const GLchar *source = (const GLchar *)fragmentSource.c_str();
glShaderSource(fragmentShader, 1, &source, 0);
glCompileShader(fragmentShader);

glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
if (isCompiled == GL_FALSE){
	GLint maxLength = 0;
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

	// The maxLength includes the NULL character
	std::vector<GLchar> infoLog(maxLength);
	glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
	
	// We don't need the shader anymore.
	glDeleteShader(fragmentShader);
	// Either of them. Don't leak shaders.
	glDeleteShader(vertexShader);

	// Use the infoLog as you see fit.
	
	// In this simple program, we'll just leave
	return 0;
}

// Vertex and fragment shaders are successfully compiled.
// Now time to link them together into a program.
// Get a program object.
GLuint program = glCreateProgram();

// Attach our shaders to our program
glAttachShader(program, vertexShader);
glAttachShader(program, fragmentShader);

// Link our program
glLinkProgram(program);

// Note the different functions here: glGetProgram* instead of glGetShader*.
GLint isLinked = 0;
glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
if (isLinked == GL_FALSE)
{
	GLint maxLength = 0;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

	// The maxLength includes the NULL character
	std::vector<GLchar> infoLog(maxLength);
	glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
	
	// We don't need the program anymore.
	glDeleteProgram(program);
	// Don't leak shaders either.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Use the infoLog as you see fit.
	
	// In this simple program, we'll just leave
	return 0;
}

// Always detach shaders after a successful link.
glDetachShader(program, vertexShader);
glDetachShader(program, fragmentShader);


        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA); /*Включаем двойную буферизацию и четырехкомпонентный цвет*/
       
        glutInitWindowSize(800, 600);
        glutCreateWindow("OpenGL lesson 1");       
        glutReshapeFunc(reshape);
        glutDisplayFunc(display);

        glutMainLoop();
 
        return 0;
}
