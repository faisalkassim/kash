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

int main()
{
    char user_input[INPUT_LENGTH + 1];
    char *args[MAX_TOKENS];
    pid_t pid;

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
        // program ends when first token is "exit"
        if (strcmp("exit", args[0]) == 0)
        {
            break;
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