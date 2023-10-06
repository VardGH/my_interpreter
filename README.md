## my_interpreter

**my_interpreter** is a simple programming language interpreter written in C++. It supports basic language features such as variable declarations, assignments, conditionals (`if` statements), loops (`while` statements), and array operations.

### Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
  - [Running the my_interpreter](#running-the-interpreter)
  - [Example Code](#example-code)
- [Language Syntax](#language-syntax)
  - [Variables](#variables)
  - [Assignments](#assignments)
  - [Conditionals](#conditionals)
  - [Loops](#loops)
  - [Arrays](#arrays)
- [License](#license)

### Features

- **Variable Declarations**: Declare variables of different types.
- **Assignments**: Assign values to variables.
- **Conditionals**: Support for `if` statements.
- **Loops**: Support for `while` loops.
- **Arrays**: Declare and manipulate arrays of various types.
- **Input/Output**: Basic support for `std::cin` and `std::cout`.

### Getting Started

#### Prerequisites

- C++ compiler (supporting C++11 or later)

#### Installation

Clone the repository:

```bash
git clone git@github.com:VardGH/my_interpreter.git
```

Compile the interpreter:

```bash
g++ *cpp -o interpreter
make
```

### Usage

#### Running the Interpreter

```bash
./interpreter
```

#### Example Code

```cpp
// Example program
#include <iostream>

int main() {

  int n = 5;

  int iarr[n];
  iarr[1] = 3;
  iarr[2] = 5;

  while (iarr[1] != iarr[2]) {
    std::cout << "yes";
    std::cin >> iarr[1];
  }

  string arr[n] = {"ai", "bo", "ap", "bd", "a"};

  int i = 0;

  while (i < 5) {
    std::cout << arr[i];
    ++ i;
  }

  int arr3[n];

  i = 0;
  while (i < n) {
    std::cin >> arr3[i];
    ++ i;
  }

  std::cout << "---";
  i = 0;
  while (i < 5) {
    std::cout << arr3[i];
    ++ i;
  }
}
```

### Language Syntax

#### Variables

Variables can be declared using the following syntax:

```cpp
int x;
float y;
char ch;
```

#### Assignments

Assign values to variables using the assignment operator (`=`):

```cpp
x = 42;
y = 3.14;
ch = 'A';
```

#### Conditionals

Use `if` statements for conditional execution:

```cpp
if (x > 10) {
    // code to execute if x is greater than 10
}
```

#### Loops

Support for `while` loops:

```cpp
while (x > 0) {
    // code to repeat while x is greater than 0
    x = x - 1;
}
```

#### Arrays

Arrays can be declared and initialized using braces:

```cpp
int arr[5] = {1, 2, 3, 4, 5};
```

### License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.