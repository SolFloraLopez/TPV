#pragma once
#include "ArrowsError.h"

class FileNotFoundError : public ArrowsError {
public:

	FileNotFoundError(string const& m) :ArrowsError("Ha ocurrido un error al buscar el archivo " + m + ".txt") {}
};