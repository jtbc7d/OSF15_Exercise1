#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "command.h"

#define MAX_CMD_COUNT 50
#define MAX_CMD_LEN 25


/*
 * PURPOSE: reads the user's input and puts it within an array checks indexes of that array for a valid command
 * INPUTS:
 *	input the text the user has typed
 *  cmd array text is put within, indexes are used for passed to appropiate functions
 * RETURN:
 **/

bool parse_user_input (const char* input, Commands_t** cmd) {

	if(!input)
		return false;

	if(!cmd)
		return false;


	char *string = strdup(input);

	*cmd = calloc (1,sizeof(Commands_t));
	(*cmd)->cmds = calloc(MAX_CMD_COUNT,sizeof(char*));

	unsigned int i = 0;
	char *token;
	token = strtok(string, " \n");
	for (; token != NULL && i < MAX_CMD_COUNT; ++i) {
		(*cmd)->cmds[i] = calloc(MAX_CMD_LEN,sizeof(char));
		if (!(*cmd)->cmds[i]) {
			perror("Allocation Error\n");
			return false;
		}
		strncpy((*cmd)->cmds[i],token, strlen(token) + 1);
		(*cmd)->num_cmds++;
		token = strtok(NULL, " \n");
	}
	free(string);
	return true;
}

/*
 * PURPOSE: destroys the command array
 * INPUTS:
 *	cmd the array filled with user commands to be freed
 * RETURN:
 **/

void destroy_commands(Commands_t** cmd) {

	if(!cmd)
		return;

	for (int i = 0; i < (*cmd)->num_cmds; ++i) {
		free((*cmd)->cmds[i]);
	}
	free((*cmd)->cmds);
	free((*cmd));
	*cmd = NULL;
}
