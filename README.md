# Simple Shell

## Description

The Simple Shell is a basic UNIX command-line interpreter that replicates the behavior of the shell (sh). It allows users to execute commands, handle the environment, and navigate the file system.

## Features

- Execute commands with their full path or relative path.
- Handle command-line arguments.
- Implement built-in commands such as `exit` and `env`.
- Support for environment variable management (`setenv`, `unsetenv`, `printenv`).
- Basic error handling.
- Interactive and non-interactive modes.

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/holbertonschool-simple_shell.git
   cd holbertonschool-simple_shell
   ```

2. Compile the shell:

   ```bash
   gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
   ```

3. Run the shell:

   - Interactive mode:
     ```bash
     ./hsh
     ```

   - Non-interactive mode:
     ```bash
     echo "/bin/ls" | ./hsh
     ```

## Built-in Commands

- **`exit`**: Exits the shell.
- **`env`**: Prints the current environment.
- **`setenv`**: Sets or updates an environment variable.
  - Usage: `setenv VARIABLE_NAME VALUE`
- **`unsetenv`**: Unsets an environment variable.
  - Usage: `unsetenv VARIABLE_NAME`
- **`showpath`**: Displays all directories in the PATH environment variable.

## Examples

- Running a command:
  ```bash
  $ /bin/ls
  file1 file2 file3
  ```

- Setting an environment variable:
  ```bash
  $ setenv MY_VAR HelloWorld
  ```

- Displaying environment variables:
  ```bash
  $ env
  ```

- Removing an environment variable:
  ```bash
  $ unsetenv MY_VAR
  ```

- Exiting the shell:
  ```bash
  $ exit
  ```
