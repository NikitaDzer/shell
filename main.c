#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "parser.h"
#include "executer.h"
#include "common.h"


int main( const int argc, char **const argv)
{
	if ( argc != 2 )
	{
		return 1;
	}

	$("Kris clown", s);

	u32      n_commands = 0;
	Command *commands   = get_commands( argv[1], &n_commands);

	if ( commands == NULL )
	{
		return 1;	
	}


	int *const exit_codes = execute_commands( commands, n_commands);
       	
	if ( exit_codes != NULL	)
	{ 
		for ( u32 i = 0; i < n_commands; i++ )
		{
			printf( "%d ", exit_codes[i]);
		}

		printf( "\n");
	}


	free( exit_codes);
	free_commands( commands, n_commands);

	
	return 0;
}
