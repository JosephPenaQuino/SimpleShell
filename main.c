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

#define SET_BIN_LENGTH 8
#define SET_USR_LENGTH 2
/* ----------------- Global Variables ----------------- */
char * allowed_commands_set_bin[SET_BIN_LENGTH]={	"ls", 
																									"pwd", 
																									"cd", 
																									"mkdir", 
																									"rm", 
																									"nano", 
																									"cat", 
																									"exit"};

char * allowed_commands_set_usr[SET_USR_LENGTH]={	"vim", 
																									"gcc"};

/* --------------------- Structs ---------------------- */
struct Data
{
	char input_line[MAX_INPUT];
	char tokens[MAX_ARGS][MAX_ARG_LENGTH];
	uint8_t arg_number;
};

/* --------------- Function Prototypes --------------- */
void split_input(struct Data *data );
int is_a_command(char *command);
void execute_command(struct Data *data, int set);
static inline void print_error(char *tokens);

/* ----------------- Main Function  ------------------ */
int main()
{
	struct Data data;
	int set;

	while(1)
	{
		memset(data.input_line, 0, MAX_INPUT);
		printf("OS_Joseph:~$ ");
		scanf("%[^\n]s", data.input_line);
		getchar();

    	split_input(&data);
    	if (set = is_a_command(data.tokens[0]))
    		execute_command(&data, set);
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

int is_a_command(char *command)
{
	for (int i=0; i<SET_BIN_LENGTH; ++i)
		if (!strcmp(allowed_commands_set_bin[i], command))
			return 1;
	for (int i=0; i<SET_USR_LENGTH; ++i)
		if (!strcmp(allowed_commands_set_usr[i], command))
			return 2;
	return 0;
}

void execute_command(struct Data *data, int set)
{
	pid_t pid;
	pid = fork ();
	char path[100];

	if (strcmp(data->tokens[0], "exit") == 0)
			exit(1);

	if (strcmp(data->tokens[0], "cd") == 0)
		chdir(data->tokens[1]);

	if (pid < 0)
		fprintf(stderr, "Fork Failed");
	else if (pid == 0)
	{
		if (set==1)
			strcpy(path, "/bin/");
		else if (set==2)
			strcpy(path, "/usr/bin/");
		strcat(path, data->tokens[0]);
		
		switch (data->arg_number)
		{
			case 0:
				execlp(path, data->tokens[0], NULL);
				break;
			case 1:
				execlp(path, data->tokens[0], data->tokens[1], NULL);
				break;
			case 2:
				execlp(path, data->tokens[0], data->tokens[1], data->tokens[2], NULL);
				break;
			case 3:
				execlp(path, data->tokens[0], data->tokens[1], data->tokens[2], data->tokens[3], NULL);
				break;
			case 4:
				execlp(path, data->tokens[0], data->tokens[1], data->tokens[2], data->tokens[3], data->tokens[4], NULL);
				break;
			case 5:
				execlp(path, data->tokens[0], data->tokens[1], data->tokens[2], data->tokens[3], data->tokens[4], data->tokens[5], NULL);
				break;
			case 6:
				execlp(path, data->tokens[0], data->tokens[1], data->tokens[2], data->tokens[3], data->tokens[4], data->tokens[5], data->tokens[6], NULL);
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
