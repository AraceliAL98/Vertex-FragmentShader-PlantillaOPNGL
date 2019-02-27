#version 330 core
//Primer linea SIEMPRE es ;a version

//Atributos de entrada (Vienen desde el vertex)

in vec4 fragmentColor;

//Atributos de salida

out vec4 salidaColor;

//Funcion msin()

void main()
{

	salidaColor = fragmentColor;

}