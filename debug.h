#ifndef _DEBUG_H
#define _DEBUG_H
#include <time.h>

#define debugf(a...) { 													\
	time_t rawtime;														\
	struct tm *timeinfo;												\
	time(&rawtime);														\
	timeinfo = localtime(&rawtime);										\
	fprintf(stderr, "%s timing-debug: ", asctime(timeinfo)); 			\
	fprintf(stderr, a); 												\
	fprintf(stderr, " (%s %s:%d)\n", __FUNCTION__, __FILE__, __LINE__); \
}																		\

#define infof(a...) { 													\
	time_t rawtime;														\
	struct tm *timeinfo;												\
	time(&rawtime);														\
	timeinfo = localtime(&rawtime);										\
	fprintf(stderr, "%s timing-info: ", asctime(timeinfo)); 			\
	fprintf(stderr, a); 												\
	fprintf(stderr, " (%s %s:%d)\n", __FUNCTION__, __FILE__, __LINE__); \
}																		\

#define errorf(a...) { 													\
	time_t rawtime;														\
	struct tm *timeinfo;												\
	time(&rawtime);														\
	timeinfo = localtime(&rawtime);										\
	fprintf(stderr, "%s timing-error: ", asctime(timeinfo)); 			\
	fprintf(stderr, a); 												\
	fprintf(stderr, " (%s %s:%d)\n", __FUNCTION__, __FILE__, __LINE__); \
}																		\

#endif
