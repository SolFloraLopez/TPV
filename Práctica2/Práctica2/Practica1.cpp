#include "Practica1.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{

}

bool cargarCoches(string fichEntrada, ListaCoches listaCoches) 
{
	ifstream input;
	string aux;

	input.open(fichEntrada);

	if (!input.is_open()) return false;

	getline(input, aux);
	listaCoches.cont = stoi(aux);
	listaCoches.coches = new Coche[listaCoches.cont];

	for (int i = 0; i < listaCoches.cont; i++) 
	{
		char c;
		input.get(c);
		aux = "";

		while (c != ' ') 
		{
			aux += c;
			input.get(c);
		}

		listaCoches.coches[i].codigo = stoi(aux);

		input.get(c);
		aux = "";

		while (c != ' ')
		{
			aux += c;
			input.get(c);
		}
		
		listaCoches.coches[i].precio = stoi(aux);

		getline(input, listaCoches.coches[i].nombre);
	}

	input.close();
	return true;
}

bool leerAlquileres	(string fichEntrada, ListaAlquileres listaAlquileres, ListaCoches listaCoches)
{
	ifstream input;
	string aux;

	input.open(fichEntrada);

	if (!input.is_open()) return false;

	getline(input, aux);
	listaAlquileres.cont = stoi(aux);
	listaAlquileres.alquileres = new Alquiler[listaAlquileres.cont];

	for (int i = 0; i < listaAlquileres.cont; i++)
	{
		char c;
		input.get(c);
		aux = "";

		while (c != ' ')
		{
			aux += c;
			input.get(c);
		}

		listaAlquileres.alquileres[i].codigo = stoi(aux);

		input.get(c);
		aux = "";

		while (c != ' ')
		{
			aux += c;
			input.get(c);
		}

		listaAlquileres.alquileres[i].fecha = aux;

		getline(input, aux);
		listaAlquileres.alquileres[i].dias = stoi(aux);

		listaAlquileres.alquileres[i].coche = buscaCoche(listaCoches, listaAlquileres.alquileres[i].codigo);
	}

	input.close();
	return true;
}

void 

Coche * buscaCoche(ListaCoches listaCoches, int codigo) 
{
	int i = 0;

	while (i < listaCoches.cont && listaCoches.coches[i].codigo != codigo) 
	{
		i++;
	}

	if (i == listaCoches.cont) return nullptr;

	return &listaCoches.coches[i];
}