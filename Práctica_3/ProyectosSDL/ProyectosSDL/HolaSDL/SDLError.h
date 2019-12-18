#pragma once
#include "ArrowsError.h"

class SDLError : public ArrowsError {
public:

	SDLError(string & m) : ArrowsError(string(m)){};
};
