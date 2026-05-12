**BMCC Honors Project: Tic-Tac-Toe Console Suite**
**Inspiration**
While basic programming focuses on linear execution, mastering Object-Oriented Programming (OOP) requires understanding how to encapsulate state and behavior. I hypothesized that building a Tic-Tac-Toe engine using the Gaddis Method would create a scalable system that separates the user interface from underlying game rules, making the code easier to debug and expand.

**What it does****
I developed a modular C++ application that manages a 3x3 game board through a dedicated TicTacToe class. The system uses a private array to track player moves and features a backend implementation of checkWinner() that performs exhaustive checks across rows, columns, and diagonals. It also includes makeMove() for coordinate validation to ensure data integrity during gameplay.

**Challenges I ran into**

Array Indexing: Mapping user-friendly input (1–3) to zero-based C++ indices (0–2) without memory errors.

Separation of Concerns: Transitioning to a three-file structure using Tictactoe.h and implementation files.

Header Management: Utilizing header guards to prevent redefinition errors during compilation.

Accomplishments that I'm proud of

Successfully encapsulated the board's data structure, hiding it from the main function.

Implemented an efficient resetBoard() method for seamless consecutive matches.

Established a clean version control workflow on GitHub with descriptive commits.

**What I learned**

How to define class blueprints in header files while keeping logic in implementation files.

Crafting efficient boolean logic for win-state detection without redundant processing.

Applying professional Gaddis Design principles for readable, industry-standard code.

**Built with**

C++

Object-Oriented Programming

GitHub

Standard Template Library (STL)
