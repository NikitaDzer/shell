#ifndef PARSER_H
#define PARSER_H

#include "common.h"

typedef struct Command
{
	char  *path;
	char **options;
	u32    n_options;
} Command;


static const char COMMAND_PATH_PREFIX[] = "/usr/bin/";
static const u32  COMMAND_PATH_MAX_SIZE = 256;


void free_commands( Command *const commands, const u32 n_commands);

Command *get_commands( char *const string, u32 *const n_commands);

#endif // PARSER_H
