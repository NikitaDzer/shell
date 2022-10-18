#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "parser.h"
#include "executer.h"
#include "common.h"

#define BUFFER_SIZE 4096


int main( void)
{
	char buffer[BUFFER_SIZE] = { 0 };


	while ( true )
	{
		char *const string = fgets( buffer, BUFFER_SIZE, stdin);

		if ( string == NULL )
		{
			return 1;
		}


		u32      n_commands = 0;
		Command *commands   = get_commands( string, &n_commands);

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
	}
	
	return 0;
}
