#ifndef SRC_UTILS_EXCEPTIONS_SYSCALLEXCEPTION_H_
#define SRC_UTILS_EXCEPTIONS_SYSCALLEXCEPTION_H_

#include <errno.h>
#include <string.h>
#include <stdexcept>
#include <string>

using std::runtime_error;

class SysCallException: public runtime_error {
public:
	SysCallException() :
			runtime_error("Error executing a system call") {
	}

	SysCallException(const std::string& msgError) :
			runtime_error("Unexpected error has occurred: " + msgError) {
	}
};

#endif /* SRC_UTILS_EXCEPTIONS_SYSCALLEXCEPTION_H_ */
