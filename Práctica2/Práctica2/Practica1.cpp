#include "Practica1.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

bool cargarCoches(string fichEntrada, ListaCoches& listaCoches)
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
		aux = "";

		input >> aux;

		listaCoches.coches[i].codigo = stoi(aux);

		aux = "";

		input >> aux;

		listaCoches.coches[i].precio = stoi(aux);

		getline(input, listaCoches.coches[i].nombre);
	}

	input.close();
	return true;
}

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

bool leerAlquileres(string fichEntrada, ListaAlquileres& listaAlquileres, ListaCoches listaCoches)
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
		int d, m, a;

		input >> aux;

		listaAlquileres.alquileres[i].codigo = stoi(aux);

		input >> d; input.get(c); input >> m; input.get(c); input >> a;

		listaAlquileres.alquileres[i].fecha = Date(d, m, a);

		getline(input, aux);
		listaAlquileres.alquileres[i].dia = stoi(aux);

		listaAlquileres.alquileres[i].coche = buscaCoche(listaCoches, listaAlquileres.alquileres[i].codigo);
	}

	input.close();
	return true;
}

bool sortingFunction(Alquiler alquiler1, Alquiler alquiler2)
{
	return alquiler1.fecha < alquiler2.fecha;
}

void ordenarAlquileres(ListaAlquileres& listaAlquileres)
{
	sort(listaAlquileres.alquileres, &listaAlquileres.alquileres[listaAlquileres.cont], sortingFunction);
}

void mostrarAlquileres(string fichSalida, ListaAlquileres listaAlquileres)
{
	ofstream output;
	output.open(fichSalida);

	//Escribir fecha

	for (int i = 0; i < listaAlquileres.cont; i++)
	{
		output << listaAlquileres.alquileres[i].fecha;

		if (listaAlquileres.alquileres[i].coche != nullptr)
		{
			output << listaAlquileres.alquileres[i].coche->nombre << " " << listaAlquileres.alquileres[i].dia << " dia(s) por "
				<< listaAlquileres.alquileres[i].coche->precio * listaAlquileres.alquileres[i].dia << " euros\n";
		}

		else
		{
			output << " ERROR: Modelo inexistente \n";
		}
	}

	output.close();
}

int main()
{
	string fichCoches = "coches.txt"; string fichAlquileres = "rent.txt"; string fichSalida = "exitPractica.txt";
	ListaCoches listaCoches;
	ListaAlquileres listaAlquileres;

	cargarCoches(fichCoches, listaCoches);
	leerAlquileres(fichAlquileres, listaAlquileres, listaCoches);
	ordenarAlquileres(listaAlquileres);
	mostrarAlquileres(fichSalida, listaAlquileres);
}

