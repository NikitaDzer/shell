#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "pipe.h"
#include "executer.h"
#include "common.h"


static int execute_command( const Command *const command)
{
	return execvp( command->path, command->options);
}

int *execute_commands( const Command *const commands, const u32 n_commands)
{
	int *const exit_codes = (int *)calloc( n_commands, sizeof(int));

	if ( exit_codes == NULL )
	{
		return NULL;
	}

	
	const bool extended_mode = n_commands >= 2;

	int fd_in  = STDIN_FILENO;
	int fd_out = STDOUT_FILENO; 
	
	int   wstatus = 0;
	pid_t pid     = 0;


	if ( extended_mode )
	{
		make_pipes();


		pid = fork();

		if ( pid == 0 )
		{
			fd_out = open( get_pipe( 0), O_WRONLY);
			dup2( fd_out, STDOUT_FILENO);
		
			execute_command( commands + 0); 
		}

		fd_in = open( get_pipe( 0), O_RDONLY);
		
		wait( &wstatus);
		exit_codes[0] = WEXITSTATUS( wstatus);


		for ( u32 i = 1; i < (n_commands - 1); i++ )
		{
			pid = fork();

			if ( pid == 0 )
			{
				fd_out = open( get_pipe( i), O_WRONLY);

				dup2( fd_in,  STDIN_FILENO);				
				dup2( fd_out, STDOUT_FILENO);

				execute_command( commands + i);
			}

			fd_in = open( get_pipe( i), O_RDONLY);
			
			wait( &wstatus);
			exit_codes[i] = WEXITSTATUS( wstatus);
		}
	}


	pid = fork();

	if ( pid == 0 )
	{
		dup2( fd_in, STDIN_FILENO);

		execute_command( commands + n_commands - 1);
	}

	wait( &wstatus);
	exit_codes[n_commands - 1] = wstatus;


	if ( extended_mode )
	{
		unlink_pipes();
	}


	return exit_codes;
}
