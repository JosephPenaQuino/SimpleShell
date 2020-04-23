/* *************************************************** *
 *  Title: simple shell
 *
 *  Author: Joseph Peña
 *
 * *************************************************** */

/* -------------------- Libraries -------------------- */
#include <sys/types.h>
#include <sys/wait.h> 
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ------------------ Pre processors  ----------------- */
#define MAX_INPUT 300
#define MAX_ARGS  100
#define MAX_ARG_LENGTH 100

/* --------------------- Structs ---------------------- */
struct Data
{
	char input_line[MAX_INPUT];
	char tokens[MAX_ARGS][MAX_ARG_LENGTH];
	uint8_t arg_number;
};

/* --------------- Function Prototypes --------------- */
void split_input(struct Data *data );
bool is_a_command(char *command);
void execute_command(struct Data *data);
static inline void print_error(char *tokens);

/* ----------------- Main Function  ------------------ */
int main()
{
	struct Data data;

	while(1)
	{
		memset(data.input_line, 0, MAX_INPUT);
		printf("OS_Joseph:~$ ");
		scanf("%[^\n]s", data.input_line);
		getchar();

    	split_input(&data);
    	if (is_a_command(data.tokens[0]))
    		execute_command(&data);
    	else
    		print_error(data.tokens[0]);
    }
}

/* --------------- Function Definitions -------------- */
void split_input(struct Data *data )
{
	uint8_t cnt = 0;
	char * temp = strtok (data->input_line," ");

	while (temp != NULL)
	{
		strcpy(data->tokens[cnt], temp);
		temp = strtok (NULL, " ");
		cnt++;
	}
	data->arg_number = cnt-1;
}

bool is_a_command(char *command)
{
	if (strcmp(command, "ls") == 0) 
		return true;
	else if (strcmp(command, "pwd") == 0) 
		return true;
	else if (strcmp(command, "cd") == 0) 
		return true;
	else if (strcmp(command, "mkdir") == 0) 
		return true;
	else if (strcmp(command, "rm") == 0) 
		return true;
	else if (strcmp(command, "nano") == 0) 
		return true;
	else if (strcmp(command, "cat") == 0) 
		return true;
	else if (strcmp(command, "exit") == 0) 
		return true;
	else if (strcmp(command, "vim") == 0 )
		return true;
	else if (strcmp(command, "gcc") == 0)
		return true;
	else 
		return false;
}

void execute_command(struct Data *data)
{
	pid_t pid;
	pid = fork ();
	char path[100];
	strcpy(path, "/bin/");
	strcat(path, data->tokens[0]);

	if (strcmp(data->tokens[0], "exit") == 0)
			exit(1);

	if (strcmp(data->tokens[0], "cd") == 0)
		chdir(data->tokens[1]);

	if (pid < 0)
		fprintf(stderr, "Fork Failed");
	else if (pid == 0)
	{
		switch (data->arg_number)
		{
				case 0:
				printf("\t-path: %s, %s", path, data->tokens[0]);
				execlp(path, data->tokens[0], NULL);
				break;
			case 1:
				printf("\t-path: %s, %s %s", path, data->tokens[0], data->tokens[1]);
				execlp(path, data->tokens[0], data->tokens[1], NULL);
				break;
			case 2:
				printf("\t-path: %s, %s %s %s", path, data->tokens[0], data->tokens[1], data->tokens[2]);
				execlp(path, data->tokens[0], data->tokens[1], data->tokens[2], NULL);
				break;
			default:
				break;
		}
		exit(1);
	}

	else
		wait(NULL);
}

static inline void print_error(char *tokens)
{
	printf("%s: command not found\n", tokens);
}
