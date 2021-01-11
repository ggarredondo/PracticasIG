#include "camara.h"

void Camara::modificarVisualizacion(float left, float right, float bottom, float top, float near, float far)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->near = near;
	this->far = far;
}

Camara::Camara(Tupla3f eye, Tupla3f at, Tupla3f up, float left, float right, float bottom, float top, float near, float far, tipoCamara tipo)
{
	this->eye = eye;
	this->at = at;
	this->up = up;
	vpn = eye-at;
	modificarVisualizacion(left,right,bottom,top,near,far);
	this->tipo = tipo;
	angleY = 0;
}

inline void rotarEjeX(Tupla3f& t, float angle) {
	t[1] = t[1]*cos(angle) - t[2]*sin(angle);	
	t[2] = t[1]*sin(angle) + t[2]*cos(angle);
}

inline void rotarEjeY(Tupla3f& t, float angle) {
	t[0] = t[2]*sin(angle) + t[0]*cos(angle);
	t[2] = t[2]*cos(angle) - t[0]*sin(angle);
}

inline void rotarEjeZ(Tupla3f& t, float angle) {
	t[0] = t[0]*cos(angle) - t[1]*sin(angle);	
	t[1] = t[0]*sin(angle) + t[1]*cos(angle);
}

//examinar
void Camara::rotarXExaminar(float angle)
{
	float modulo = sqrt(vpn.lengthSq());

	rotarEjeX(vpn, angle);
	rotarEjeX(up, angle);

	vpn = vpn.normalized()*modulo;

	eye = vpn + at;
}

void Camara::rotarYExaminar(float angle)
{
	angleY += angle;
	float modulo = sqrt(vpn.lengthSq());

	rotarEjeY(vpn, angle);
	rotarEjeY(up, angle);

	vpn = vpn.normalized()*modulo;

	eye = vpn + at;
}

void Camara::rotarZExaminar(float angle)
{
	float modulo = sqrt(vpn.lengthSq());

	rotarEjeZ(vpn, angle);
	rotarEjeZ(up, angle);

	vpn = vpn.normalized()*modulo;

	eye = vpn + at;
}

void Camara::rotarVerticalExaminar(float angle) 
{ 
	float aux = angleY;
	rotarYExaminar(-angleY);
	rotarXExaminar(angle);
	rotarYExaminar(aux);
}

//firstperson
void Camara::rotarXFirstPerson(float angle)
{
	Tupla3f ateye = at - eye;
	float modulo = sqrt(ateye.lengthSq());

	ateye[1] = ateye[1]*cos(angle) - ateye[2]*sin(angle);	
	ateye[2] = ateye[1]*sin(angle) + ateye[2]*cos(angle);

	up[1] = up[1]*cos(angle) - up[2]*sin(angle);	
	up[2] = up[1]*sin(angle) + up[2]*cos(angle);

	ateye = ateye.normalized()*modulo;

	at = ateye - eye;
}

void Camara::rotarYFirstPerson(float angle)
{
	Tupla3f ateye = at - eye;
	float modulo = sqrt(ateye.lengthSq());

	ateye[0] = ateye[2]*sin(angle) + ateye[0]*cos(angle);
	ateye[2] = ateye[2]*cos(angle) - ateye[0]*sin(angle);

	up[0] = up[2]*sin(angle) + up[0]*cos(angle);
	up[2] = up[2]*cos(angle) - up[0]*sin(angle);

	ateye = ateye.normalized()*modulo;

	at = ateye - eye;
}

void Camara::rotarZFirstPerson(float angle)
{
	Tupla3f ateye = at - eye;
	float modulo = sqrt(ateye.lengthSq());

	ateye[0] = ateye[0]*cos(angle) - ateye[1]*sin(angle);	
	ateye[1] = ateye[0]*sin(angle) + ateye[1]*cos(angle);

	up[0] = up[2]*sin(angle) + up[0]*cos(angle);
	up[2] = up[2]*cos(angle) - up[0]*sin(angle);

	ateye = ateye.normalized()*modulo;

	at = ateye - eye;
}

void Camara::girar(int x, int y)
{ //no es así
	rotarXFirstPerson(x); 
	rotarYFirstPerson(y);
}

//

void Camara::zoom(float factor)
{
	left += factor;
	right -= factor;
	top -= factor;
	bottom += factor;
}

void Camara::setObserver() {
	glMatrixMode(GL_MODELVIEW);
  	glLoadIdentity();
	gluLookAt(eye[0],eye[1],eye[2],at[0],at[1],at[2],up[0],up[1],up[2]);
}

void Camara::setProyeccion()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (tipo == ORTOGONAL)
		glOrtho(left,right,bottom,top,near,far);
	else
		glFrustum(left,right,bottom,top,near,far);
}