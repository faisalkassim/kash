// unix shell project

#include <stdio.h>
#include <string.h>

#define MAX_TOKENS 64
#define INPUT_LENGTH 100

void parse_input(char *input, char **args);

int main()
{
    char user_input[INPUT_LENGTH + 1];
    char *args[MAX_TOKENS];

    for (;;) //  prompts continuously
    {
        printf("kash> ");
        fgets(user_input, sizeof(user_input), stdin);

        // replace new line in user_input with \0
        user_input[strcspn(user_input, "\n")] = '\0';

        parse_input(user_input, args);

        if (args[0] == NULL)
        {
            continue;
        }
        // program ends when first token is "exit"
        if (strcmp("exit", args[0]) == 0)
        {
            break;
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
        printf("%s\n", args[i]);
        ptr = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
}