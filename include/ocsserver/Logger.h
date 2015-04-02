#ifndef _LOGGER_INCLUDE
#define _LOGGER_INCLUDE

#include <logging.h>

#ifdef OCSSERVER_API_EXPORTS
#define OCSSERVER_API __declspec(dllexport)
#else
#define OCSSERVER_API __declspec(dllimport)
#endif

class OCSSERVER_API Logger
{
public:
	Logger();
	~Logger();
};

#endif
