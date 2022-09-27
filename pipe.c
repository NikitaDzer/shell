#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "common.h"
#include "pipe.h"


static const char *const PIPES[] = { "SHELL_PIPE1", "SHELL_PIPE2" };


int make_pipes( void)
{
	mkfifo( PIPES[0], S_IRUSR | S_IWUSR);
      	mkfifo( PIPES[1], S_IRUSR | S_IWUSR);

	return 0;
}

int unlink_pipes( void)
{
	unlink( PIPES[0]);
	unlink( PIPES[1]);

	return 0;
}

const char *get_pipe( const u32 command_counter)
{
	return PIPES[ command_counter % 2 ];
}
