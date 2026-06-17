// unix shell project

#include <stdio.h>
#include <string.h>

#define INPUT_LENGTH 100

int main()
{
    char user_input[INPUT_LENGTH + 1];

    for (;;) //  prompts continuously
    {
        printf("kash> ");
        fgets(user_input, INPUT_LENGTH, stdin);

        // replace new line in user_input with \0
        user_input[strcspn(user_input, "\n")] = '\0';

        puts(user_input);
        // program ends when user_input is "exit"

        if (strcmp("exit", user_input) == 0)
        {
            break;
        }
    }
    return 0;
}
