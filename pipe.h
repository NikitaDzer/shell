#ifndef PIPE_H
#define PIPE_H

#include "common.h"

int make_pipes  ( void);
int unlink_pipes( void);

const char *get_pipe( const u32 command_counter);

#endif // PIPE_H
