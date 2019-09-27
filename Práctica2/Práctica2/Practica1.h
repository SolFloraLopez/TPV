#pragma once
#include <string>

//using namespace std;

struct Coche
{
	int codigo;
	int precio;
	std::string nombre;
};

struct Alquiler 
{
	int codigo;
	int dia;
	std::string fecha;
	Coche* coche;
};

struct ListaCoches 
{
	int cont;
	Coche* coches;
};

struct ListaAlquileres 
{
	int cont;
	Alquiler* alquileres;
};