#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"


static const char PIPE_CHAR       = '|';
static const char STRING_END_CHAR = 255;


bool is_string_end( const char ch)
{
	return ch == STRING_END_CHAR;
}

bool is_space( const char ch)
{
	return isspace( ch) || ch == '\0';
}

bool is_pipe( const char ch)
{
	return ch == PIPE_CHAR;
}

char *skip_space( char *const string)
{
	u32 i = 0;

	while ( true )
	{
		if ( is_space( string[i]) )
		{
			i += 1;

			continue;
		}
			
		if ( is_string_end( string[i]) )
		{

			string[i] = '\0';

			return NULL;
		}

		return string + i;
	}
}

void prepare_string( char *const string, u32 *const string_len)
{
	const u32 len = strlen(string);

	string[len] = STRING_END_CHAR;
     	*string_len = len;	
}

void free_commands( Command *const commands, const u32 n_commands)
{
	char **const options = commands[0].options;

	for ( u32 i = 0; i < n_commands; i++ )
	{
		free( commands[i].path);		
	}

	free( commands);
	free( options);
}

char *extract_word( char **const string)
{	
	char *start = *string;
	u32   i     = 1;

	while ( true )
	{
		if ( is_space( start[i]) || is_string_end( start[i]) )
		{
			break;
		}
		
		i += 1;
	}

	if ( !is_string_end( start[i]) )
	{
		start[i] = '\0';
	}
	
	*string = start + i;

	return start; 
}

char *get_command_path( char **const string)
{
	char *const command_name = extract_word( string); 
	char *const command_path = (char *)calloc( COMMAND_PATH_MAX_SIZE, sizeof(char));

	if ( command_path == NULL )
	{
		return NULL;
	}

	
	const u32 command_path_size = (sizeof(COMMAND_PATH_PREFIX) - 1) + (*string - command_name) + 1;

	if ( command_path_size > COMMAND_PATH_MAX_SIZE)
	{
		free( command_path);
		
		return NULL;
	}	

	memcpy( command_path,                                   COMMAND_PATH_PREFIX, sizeof(COMMAND_PATH_PREFIX) - 1);
	memcpy( command_path + sizeof(COMMAND_PATH_PREFIX) - 1, command_name,        *string - command_name);

	command_path[command_path_size - 1] = '\0';

	return command_path;
}

Command *get_command( char **const string, char **const options, Command *const command)
{
	char *iterator = skip_space( *string);

	if ( iterator == NULL || is_pipe( *iterator) )
	{
		return NULL;
	}


	char *const path = get_command_path( &iterator);
	
	if ( path == NULL )
	{
		return NULL;
	}
	
	options[0] = path;


	u32 n_options = 1;

	while ( true )
	{
		iterator = skip_space( iterator);

		if ( iterator == NULL || is_pipe( *iterator) )
		{
			break;
		}

		options[n_options] = extract_word( &iterator);	
		n_options += 1;
	}

	*string = iterator;
	options[n_options++] = NULL;	

	command->path      = path;
	command->options   = options;
	command->n_options = n_options;

	return command;	
}

Command *get_commands( char *const string, u32 *const n_commands)
{
	u32 string_len = 0;
	prepare_string( string, &string_len);

	if ( string_len == 0 )
		return NULL;

	Command  *const commands = (Command *)calloc( string_len,     sizeof(Command));
	char          **options  = (char **)  calloc( string_len * 2, sizeof(char *));
	
	if ( commands == NULL || options == NULL )
	{
		free( commands);
		free( options);
	
		return NULL;
	}
	

	char *iterator = string;

	if ( get_command( &iterator, options, commands + 0) == NULL )
	{
		free_commands( commands, 0);

		return NULL;
	}

	if ( iterator == NULL )
	{
		*n_commands = 1;
		
		return commands;
	}


	for ( u32 i = 1;; i++ )
	{
		options  += commands[i - 1].n_options;
		iterator += 1;

		if ( get_command( &iterator, options, commands + i) == NULL )
		{
			free_commands( commands, i);
			
			return NULL;
		
		}

		if ( iterator == NULL )
		{	
			*n_commands = i + 1;

			return commands;
		}
	}
}
