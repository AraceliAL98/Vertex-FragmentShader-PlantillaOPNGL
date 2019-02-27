#include "stdafx.h"
#include "Shader.h"

GLuint Shader::getID()
{
	return ShaderID;

}

Shader::Shader(const char * rutaVertex, const char * rutaFragment)
{
	string codigoVertexShader;
	ifstream vertexShaderStream(rutaVertex, ios::in);

	if (vertexShaderStream.is_open())
	{
		string linea;
		while (getline(vertexShaderStream, linea))
		{
			codigoVertexShader += linea + "\n";
		}
		vertexShaderStream.close();
	}

	else
	{
		cout << "No se pudo abrir el archivo " << rutaVertex;
	
	}

	string codigoFragmentShader;
	ifstream fragmentShaderStream(
		rutaFragment, ios::in 
	);

	if (fragmentShaderStream.is_open())
	{
		string linea;
		while (getline(fragmentShaderStream, linea))
		 {
			codigoFragmentShader += linea + "\n";
		
		}
	}
	else
	{
		cout << "No se pudo abrir el archivo" << rutaFragment << endl;

	}

	//Convertir de String a cadena char
	const char* cadenaCodigoVertex = codigoVertexShader.c_str();
	const char* cadenaCodigoFragment = codigoFragmentShader.c_str();

	//1- Crear el programa de Shader
	
	ShaderID = glCreateProgram();
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//2.- Cargar el codigo Shader

	glShaderSource(vertexShaderID, 1, &cadenaCodigoVertex, NULL);
	glShaderSource(fragmentShaderID, 1, &cadenaCodigoFragment, NULL);

	//3.- Compilar los shaders

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);
}

void Shader::verificarCompilacion(GLuint id)
{
	GLint resultado = GL_FALSE;
	int longitudLog = 0;

}