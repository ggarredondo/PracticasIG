#include "luz.h"

void Luz::activar() 
{
	glEnable(id);
	glLightfv(id, GL_POSITION, posicion);
	glLightfv(id, GL_DIFFUSE, colorDifuso);
	glLightfv(id, GL_SPECULAR, colorEspecular);
	glLightfv(id, GL_AMBIENT, colorAmbiente);
}