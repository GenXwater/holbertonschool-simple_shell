# Simple Shell - Holberton School Project

## Description

This project is a simple Unix shell implemented in C as part of the Holberton School curriculum. The shell provides a command-line interface where users can execute commands, manage environment variables, and navigate the file system.

## Features

- **Execute Commands**: Run system commands like `ls`, `pwd`, `echo`, etc.
- **Built-in Commands**:
  - `exit`: Exit the shell.
  - `printenv`: Display all environment variables.
  - `setenv`: Set or modify an environment variable.
  - `unsetenv`: Remove an environment variable.
  - `showpath`: Display the directories in the `PATH` variable.
  - `man simple_shell`: Display the manual page for this shell.
- **Environment Variable Management**: Set, unset, and display environment variables.
- **Command Execution**: Supports command execution with arguments and options.
- **Process Management**: Handles process creation and waits for child processes to finish.
- **Memory Management**: Properly allocates and frees memory to avoid leaks.

## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/simple_shell.git
    cd simple_shell
    ```

2. Compile the shell:

    ```bash
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
    ```

3. Run the shell:

    ```bash
    ./hsh
    ```

## Usage

- **Basic Commands**: You can run any basic Unix command.

    ```bash
    $ ls
    $ pwd
    $ echo "Hello, World!"
    ```

- **Built-in Commands**: The shell has several built-in commands.

    - **Exit the shell**:
        ```bash
        $ exit
        ```

    - **Print environment variables**:
        ```bash
        $ printenv
        ```

    - **Set an environment variable**:
        ```bash
        $ setenv MYVAR "HelloWorld"
        ```

    - **Unset an environment variable**:
        ```bash
        $ unsetenv MYVAR
        ```

    - **Show directories in `PATH`**:
        ```bash
        $ showpath
        ```

    - **Display the manual for the shell**:
        ```bash
        $ man simple_shell
        ```

## Memory Management

The shell has been tested for memory leaks using Valgrind. All dynamic memory allocations are properly freed before the shell exits, ensuring that no memory leaks occur during execution.

## Testing

To test the shell, use the following command with Valgrind to check for memory leaks:

```bash
valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-origins=yes ./hsh
```
