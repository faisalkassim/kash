# Kash — Kassim's Shell

A Unix shell built in C from scratch.

## Features (in progress)
- [x] Basic REPL loop
- [x] Command parsing
- [x] Command execution (fork/exec)
- [x] Built-in commands (cd, exit)
- [ ] Pipes
- [ ] Redirection

## Build
```bash
gcc main.c -o kash
./kash
```

## What I learned
I learned how to tokenize string input using strtok, and how to use the fork() and execvp() system calls to create a child process and replace it with a new program respectively. I also learned how to use perror() to display descriptive error messages when system calls fail.
I learned that some commands like cd must be executed directly in the shell process rather than in a forked child, because changes made in a child process do not affect the parent. This led to implementing a builtin handler that runs before the fork.