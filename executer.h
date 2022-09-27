#ifndef EXECUTER_H
#define EXECUTER_H

#include "common.h"
#include "parser.h"

int *execute_commands( const Command *const commands, const u32 n_commands);

#endif // EXECUTER_H
