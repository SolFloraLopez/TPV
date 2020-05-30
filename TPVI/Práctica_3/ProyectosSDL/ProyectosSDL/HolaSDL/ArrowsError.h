#pragma once
#include <stdexcept>
#include <string>
using std::logic_error;



class ArrowsError : public logic_error {
public:
	ArrowsError(string& m) : logic_error("Empty vector. " + m) {};
};