// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "malla.h"
#include <algorithm>

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
public:
	ObjRevolucion();
	ObjRevolucion(const std::string & archivo, int num_instancias, bool tapas=true, std::string tex="n") ;
	ObjRevolucion(const std::vector<Tupla3f>& archivo, int num_instancias, bool tapas=true, std::string tex="n") ;
	void actualizarTapas(bool tapas);

protected:
	unsigned size_tapas = 0, diferencia = 0;

	void crearMalla(const std::vector<Tupla3f>& perfil_original, int num_instancias, bool invertido = false);
	void insertarPolos(const std::vector<Tupla3f>& perfil_original, int num_instancias);
	void prepararObj(const std::vector<Tupla3f>& perfil, int num_instancias, bool tapas, std::string tex, bool invertido = false);
	void calcularCoordTextura(unsigned M, unsigned N);
};




#endif
