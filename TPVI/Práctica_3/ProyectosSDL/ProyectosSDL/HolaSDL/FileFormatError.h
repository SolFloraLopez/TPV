#pragma once
#include "ArrowsError.h"

class FileFormatError : public ArrowsError {
public:

	FileFormatError(string const& m) : ArrowsError("Ha ocurrido un error durante la lectura del archivo " + m + ".txt") {}
};
