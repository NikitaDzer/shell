#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef  int64_t i64;
typedef  int32_t i32;

#define $(variable, specifier)                					\
	do 									\
	{									\
		printf("%s: %" #specifier "\n", #variable, variable);		\
	}									\
	while (0)

#endif // COMMON_H
