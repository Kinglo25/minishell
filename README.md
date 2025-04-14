# Minishell

_minishell_ is a School 42 project that challenges you to create a simplified Unix shell. The project requires you to build a command-line interpreter in C, supporting built-in commands, external command execution, piping, redirection, and environment variable management. This project reinforces your understanding of system calls, process management, and low-level programming in a Unix environment.

---

## Table of Contents

- [Introduction](#introduction)
- [Project Description](#project-description)
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [Author](#author)
- [License](#license)

---

## Introduction

The _minishell_ project focuses on creating a basic shell that can interpret and execute commands entered by the user. This includes handling built-in commands (such as `cd`, `echo`, and `exit`), executing external programs, and managing features like piping and redirection. Through this project, you'll gain valuable insights into process control, file descriptors, and the intricacies of system-level programming.

---

## Project Description

In _minishell_, you will develop a custom shell that mimics the functionality of a typical Unix shell, albeit on a smaller scale. The project includes:

- **Command Parsing:** Breaking down the user input into executable commands and arguments.
- **Execution:** Creating child processes to execute external commands using system calls (e.g., `fork()`, `execve()`).
- **Built-in Commands:** Implementing commands that are part of the shell itself (e.g., `cd`, `export`, `unset`, `echo`, and `exit`).
- **I/O Redirection & Piping:** Allowing the user to redirect input/output and pipe commands together.
- **Environment Variables:** Managing and utilizing environment variables during shell execution.

The project’s modular design should help you separate the concerns of parsing, execution, and built-in functionalities for easier management and scalability.

---

## Features

- **Interactive Shell:** A prompt-based interactive shell that reads user commands.
- **Built-in Commands:** Implementation of shell built-in functions for navigation and environment management.
- **External Command Execution:** Supports launching external programs and handling their outputs.
- **Redirection & Piping:** Manage standard input, output, error redirections, and command piping.
- **Error Handling:** Displays relevant error messages for invalid commands or execution failures.
- **Signal Handling:** Manages signals (such as `CTRL+C` and `CTRL+D`) gracefully without crashing the shell.

---

## Prerequisites

Before building and running _minishell_, ensure you have the following:

- A C compiler (e.g., `gcc` or `clang`)
- [Make](https://www.gnu.org/software/make/) for build automation
- A Unix/Linux or macOS environment (the project relies on Unix system calls)
- Basic knowledge of C programming, system calls, and Unix process management

---

## Installation

Follow these steps to clone, build, and run the project:

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/Kinglo25/minishell.git
   cd minishell
   ```

2. **Build the Project:**

   Use the provided Makefile to clean any previous builds and compile the project:

   ```bash
   make fclean
   make
   ```

3. **Verify the Build:**

   Run your custom shell to ensure it starts correctly:

   ```bash
   ./minishell
   ```

   You should see a shell prompt where you can start entering commands.

---

## Usage

Once built, you can run _minishell_ by executing the compiled binary:

```bash
./minishell
```

**Basic Usage:**

- **Executing Commands:**  
  Simply type any Unix command (e.g., `ls`, `pwd`, `echo Hello, World!`) and press Enter.

- **Built-in Commands:**  
  Use built-in commands like `cd` to change directories, `export` to manage environment variables, and `exit` to close the shell.

- **Piping & Redirection:**  
  You can pipe commands together or redirect input/output, for example:
  ```bash
  ls -l | grep minishell > output.txt
  ```

- **Signal Handling:**  
  Use `CTRL+C` to interrupt a running command, and `CTRL+D` to exit the shell (if no command is being entered).

---

## Troubleshooting

- **Compilation Errors:**  
  Ensure all necessary headers and libraries are available on your system. Verify that your compiler supports the required Unix system calls.

- **Command Not Found:**  
  Check that the command exists in your system’s PATH. For built-in commands, review your implementation if they are not recognized.

- **Redirection/Pipe Issues:**  
  Validate your parsing and management of file descriptors. Use debugging tools or print statements to trace the execution flow.

- **Unexpected Shell Behavior:**  
  Verify signal handling and memory management. Running your program through tools like Valgrind can help identify memory leaks and errors.

For additional support, refer to your project documentation, consult with peers, or discuss issues with instructors at School 42.

---

## Contributing

Contributions and suggestions for _minishell_ are welcome! To contribute:

1. Fork the repository.
2. Create a new branch for your changes:
   ```bash
   git checkout -b feature/my-new-feature
   ```
3. Make your modifications, following the coding standards set by School 42.
4. Commit your changes with clear and descriptive commit messages.
5. Push your branch:
   ```bash
   git push origin feature/my-new-feature
   ```
6. Open a pull request for review.

Your contributions help improve the project and benefit the learning community!

---

## Author

- **Kinglo25**  
  [GitHub: Kinglo25](https://github.com/Kinglo25)

Developed as part of the School 42 curriculum.

---

## License

Distributed under the MIT License. See the `LICENSE` file for details.
```

---
