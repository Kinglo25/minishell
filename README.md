Project Minishell - 42 School
The Minishell project is a foundational exercise in systems programming at 42 School, challenging students to build a simplified Unix shell. It teaches core concepts like process execution, environment management, signal handling, and command parsing, mirroring the behavior of real-world shells (e.g., bash, zsh). This project emphasizes understanding how shells interact with the operating system kernel and user input.
Core Objective

Create a minimalistic shell that can interpret and execute user commands, including built-in functions, pipes, redirections, and environment variables. The shell must handle process creation, job control, and errors gracefully while adhering to POSIX standards.
Key Requirements

    Basic Functionality:

        Execute commands from PATH (e.g., /bin/ls, grep).

        Handle pipes (|), input/output redirections (<, >, >>), and heredoc (<<).

        Manage environment variables (e.g., $PATH, $HOME) and expand $VAR in commands.

    Built-in Commands:
    Implement essential shell built-ins:

        echo (with -n flag).

        cd (change directory).

        pwd (print working directory).

        export (set environment variables).

        unset (remove environment variables).

        env (list environment variables).

        exit (terminate the shell with optional status code).

    Signal Handling:

        Respond to Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT) by interrupting or killing processes.

        Prevent termination of the shell itself with Ctrl+C during command execution.

    Error Handling:

        Display meaningful errors (e.g., command not found, syntax error).

        Handle invalid permissions, missing files, and memory leaks.

Technical Implementation

    Lexing & Parsing:

        Split input into tokens (commands, arguments, operators).

        Resolve ambiguities (e.g., quotes "...", escaping \).

        Build an abstract syntax tree (AST) to represent command pipelines and redirections.

    Process Execution:

        Use fork(), execve(), and waitpid() to launch processes.

        Manage file descriptors for pipes and redirections (dup2, pipe, open).

        Handle built-in commands in the parent process (no fork() needed).

    Signals:

        Override default signal handlers using signal() or sigaction().

        Ensure foreground/background process control (e.g., Ctrl+Z for SIGTSTP in bonus).

    Memory Management:

        Avoid leaks with careful allocation/freeing of command structures.

        Use tools like valgrind to debug memory issues.

Bonus Extensions

Optional advanced features to deepen understanding:

    Job Control:

        Implement & for background processes.

        Add fg, bg, and jobs commands to manage suspended jobs.

    Logical Operators:

        Support && (and) and || (or) between commands.

    Wildcards:

        Expand * wildcards in filenames (e.g., ls *.c).

    Subshells:

        Handle commands in parentheses (echo "hello" && ls).

    History:

        Save and recall command history (e.g., !!, !n).

Learning Outcomes

    Process Management: Mastery of fork(), execve(), and process synchronization.

    File Descriptors: Understanding redirections, pipes, and I/O manipulation.

    Parsing Techniques: Writing robust lexers/parsers for complex input.

    Signal Handling: Graceful interruption and process control.

    Shell Internals: Insight into how shells interface with the OS kernel.

Minishell is a pivotal project for aspiring systems programmers, bridging theoretical OS concepts with real-world application. It demands meticulous attention to edge cases, memory safety, and POSIX compliance, preparing students for advanced work in operating systems and embedded systems.
