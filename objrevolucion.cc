#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"



// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapas) {
	std::vector<Tupla3f> vertices;
	ply::read_vertices(archivo, vertices);
	prepararObj(vertices, num_instancias, tapas);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

 
ObjRevolucion::ObjRevolucion(const std::vector<Tupla3f>& archivo, int num_instancias, bool tapas) {
    prepararObj(archivo, num_instancias, tapas);
}

void ObjRevolucion::actualizarTapas(bool tapas) {
	if (!tapas) {
		tam1 -= size_tapas;
		diferencia = size_tapas;
	}
	else {
		tam1 += diferencia;
		diferencia = 0;
	}
	tamA = tam1*0.5;
	tamB = tam1-tamA;
}

void ObjRevolucion::prepararObj(const std::vector<Tupla3f>& perfil, int num_instancias, bool tapas) {
	crearMalla(perfil, num_instancias);
    insertarPolos(perfil, num_instancias);
	preparar_modos();
	actualizarTapas(tapas);
}

void ObjRevolucion::crearMalla(const std::vector<Tupla3f>& perfil_original, int num_instancias) {
	Tupla3f v_aux;
	unsigned N = num_instancias, M = perfil_original.size();

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M; ++j) {
			v_aux = perfil_original[j];
			v_aux[2] = -v_aux[0]*sin(2*M_PI*i/N);
			v_aux[0] *= cos(2*M_PI*i/N);
			v.push_back(v_aux);
		}
	}

	unsigned a, b;
	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < M-1; ++j) {
			a = M*i + j;
			b = M*((i+1)%N)+j;
			f.push_back(Tupla3i(a, b, b+1));
			f.push_back(Tupla3i(a, b+1, a+1));
		}
	}
}

void ObjRevolucion::insertarPolos(const std::vector<Tupla3f>& perfil_original, int num_instancias)
{
	float min_h = perfil_original[0][1], max_h = perfil_original[perfil_original.size()-1][1];

	//formar tapas
	int polo = v.size(), anterior = -1, primero, N = num_instancias, M = perfil_original.size();

	v.push_back(Tupla3f{0, min_h, 0});
	for (unsigned i = 0; i < N; ++i) {
			if (anterior == -1)
				primero = M*i;
			if (anterior != -1) {
				f.push_back(Tupla3i(polo, M*i, anterior));
				size_tapas++;
			}
			anterior = M*i;
	}
	f.push_back(Tupla3i(polo, primero, anterior));
	size_tapas++;

	polo = v.size();
	v.push_back(Tupla3f{0, max_h, 0});
	anterior = -1;
	for (unsigned i = 0; i < N; ++i) {
			if (anterior == -1)
				primero = M*(i+1)-1;
			if (anterior != -1) {
				f.push_back(Tupla3i(anterior, M*(i+1)-1, polo));
				size_tapas++;
			}
			anterior = M*(i+1)-1;
	}
	f.push_back(Tupla3i(anterior, primero, polo));
	size_tapas++;
}