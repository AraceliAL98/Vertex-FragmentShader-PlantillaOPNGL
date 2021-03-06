// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include "Shader.h"
#include "Vertice.h"
 

Shader *shader;
GLuint posicionID;
GLuint colorID;

vector <Vertice> triangulo;
GLuint vertexArrayTrianguloID;
GLuint bufferTrianguloID;

void inicializarTriangulo()
{
	Vertice v1 =
	{
		vec3(0.0f, 0.03f, 0.0f),
		vec4(1.0f, 0.08f, 0.0f, 1.0f)

	};

	Vertice v2 = 
	{
		vec3(-0.3f, -0.3f, 0.0f),
		vec4(1.0f, 0.8f, 0.0f, 1.0f)

	};

	Vertice v3 =
	{
		vec3(0.3f, -0.3f, 0.0f),
		vec4(1.0f, 0.8f, 0.0f, 1.0f)

	};

	triangulo.push_back(v1);
	triangulo.push_back(v2);
	triangulo.push_back(v3);

}

using namespace std;

void dibujar() 
{
	//Elegir el Shader
	shader->enlazar();

	//Elegir un Vertex Array
	glBindVertexArray(vertexArrayTrianguloID);

	//Dibujar
	glDrawArrays(GL_TRIANGLES, 0, triangulo.size());

	//Soltar el vertex array
	glBindVertexArray(0);

	//Soltar el shader
	shader->desenlazar();


	
}

void actualizar() {

}

int main()
{
	//Declaramos apuntador de ventana
	GLFWwindow *window;

	//si no se pudo inicializar glfw terminamos ejecución
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//si se pudo iniciar GLFW entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	//si no podemos iniciar la ventana entonces terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//establecemos el contexto
	glfwMakeContextCurrent(window);

	//UNa vez establecido el contexto activamos funciones modernas (CPU/GPU)
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	const char *rutaVertex = "VertexShader.shader";
	const char *rutaFragment = "FragmentShader.shader";

	inicializarTriangulo();

	shader = new Shader(rutaVertex, rutaFragment);

	//Mapeo de atributos
	
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");

	//Desenlazar el shader
	
	shader->desenlazar();

	//Crear un Vertex Array

	glGenVertexArrays(1, &vertexArrayTrianguloID);
	glBindVertexArray(vertexArrayTrianguloID);

	//Crear vertex buffer
	glGenBuffers(1, &bufferTrianguloID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferTrianguloID);

	//llenar buffer

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * triangulo.size(), triangulo.data(), GL_STATIC_DRAW);

	//Habilitar tributo shader

	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);

	//Especificar a OpenGL como se tiene que inicializar

	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));

	//Soltar Vertex array y buffer

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
		


	//Cilco de dibijo (Draw loop)
	while (!glfwWindowShouldClose(window)) {
		//Establecer region de dibujo
		glViewport(0, 0, 1024, 768);
		//Esctablece el color de borrado
		glClearColor(0.25, 0, 0.3, 1);
		//Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de dibujo
		dibujar();
		actualizar();

		//Cambiar los buffers
		glfwSwapBuffers(window);
		//Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

    return 0;
}

