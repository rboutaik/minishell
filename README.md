# Minishell

Minishell is a simple shell program developed as part of the 42 School curriculum. This project aims to provide a deeper understanding of how a Unix shell works, including process creation, signal handling, and command execution.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)


## Overview

Minishell is a minimalistic shell that replicates some of the basic functionalities of popular Unix shells like `bash`. It allows users to interact with the system by executing commands, handling redirections, pipes, and more. The project helps in understanding the inner workings of a shell, including how to manage processes, signals, and environment variables.

## Features

- Command execution with arguments
- Environment variable management (`export`, `unset`, etc.)
- Built-in commands (`cd`, `echo`, `env`, `pwd`, `exit`)
- Redirections (`<`, `>`, `>>`)
- Pipes (`|`) for command chaining
- Signal handling (e.g., `Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Error handling and custom prompt

## Installation

### Prerequisites

Ensure you have the following:

- GCC or Clang (for compiling the C code)
- `make` (for building the project)

### Build Instructions

1. Clone the repository:
   ```bash
   git clone https://github.com/rboutaik/minishell.git
   cd minishell
