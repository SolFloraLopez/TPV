#include <stdexcept>

using std::logic_error;

class ArrowsError : public logic_error {
public:
	using logic_error::logic_error;
};