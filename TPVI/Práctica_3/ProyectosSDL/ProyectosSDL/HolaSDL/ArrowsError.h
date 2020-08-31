#pragma once
#include <stdexcept>
#include <string>
using std::logic_error;

class ArrowsError : public logic_error {
public:
	ArrowsError(const string& m) : logic_error("Empty vector. " + m) {};
};