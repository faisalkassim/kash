// unix shell project

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_TOKENS 64
#define INPUT_LENGTH 100

void parse_input(char *input, char **args);
int execute_builtin(char *str_1, char *str_2);

int main()
{
    char user_input[INPUT_LENGTH + 1];
    char *args[MAX_TOKENS];
    pid_t pid;
    int is_builtin;

    for (;;) //  prompts continuously
    {
        printf("kash> ");
        fgets(user_input, sizeof(user_input), stdin);

        // replace new line in user_input with \0
        user_input[strcspn(user_input, "\n")] = '\0';

        parse_input(user_input, args);

        // handles empty input
        if (args[0] == NULL)
        {
            continue;
        }
        

        
        is_builtin = execute_builtin(args[0], args[1]);

        // skips fork() if command is builtin
        if (is_builtin)
        {
            continue;
        }

        pid = fork();

        if (pid == 0)
        {
            execvp(args[0],args);

            // runs when execvp fails
            perror("kash");
            exit(1);
        }
        // executes in the parent process only
        else if (pid > 0)
        {
            waitpid(pid, NULL, 0);
        }
        else
        {
            perror("kash");
        }
    }
    return 0;
}

/*parse_input
separates the input strings into tokens using strtok and then store the pointer to each token
in the args pointer array
*/
void parse_input(char *input, char **args)
{
    char *ptr = strtok(input, " ");
    int i = 0;

    while (ptr != NULL && i != MAX_TOKENS)
    {
        args[i] = ptr;
        ptr = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
}

/* execute builtin
custom function for performing cd and exit commands in parent process
*/

int execute_builtin(char *str_1, char *str_2)
{
    int status;

    // checks if command is cd
    if (strcmp("cd", str_1) == 0 )
    {
        // handles case where no path is specified
        if (!(str_2 == NULL))
        {
            status = chdir(str_2);
            // failed to find directory
            if (status == -1)
            {
                perror("kash");
            }
        }
        
        return 1;
    }
    else if (strcmp("exit", str_1) == 0)
    {
        exit(0);
    }
    return 0;
}