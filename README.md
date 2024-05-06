# Binary-parser-language
### General Overview

For this project, I am developing a basic toy programming language named "Blip". Initially, in Phase A, we are focusing on creating simple straight-line code with basic assignment (`var`, `set`) and output (`output`, `text`) commands.

### Language Design and Parsing

Blip is uniquely designed for ease of parsing. This simplicity allows for a distinct syntax that differs from typical programming languages, adopting a prefix expression syntax rather than the common infix. For example, to represent "2 + 2", we write "+ 2 2". The language does not resemble any conventional programming languages, which facilitates our learning and implementation from scratch.

### Features Implemented

1. **Variable Initialization (`var`)** - Initializes a new variable, handling re-initializations with a warning.
2. **Variable Assignment (`set`)** - Assigns a new value to an existing variable, with warnings for undeclared variables.
3. **Output Expressions (`output`)** - Evaluates and displays results of expressions using Blip’s integer operators.
4. **Text Output (`text`)** - Displays a text message on the screen.

### Symbol Table and Memory

Implementation of variables requires an efficient implentation of a data structure that is able to store and return output based on the given input string, here I used a self implented linked list that is able to store the computed value of a givne variable. We are also able to compute this input by utilizing a recursive funciton that produces a binary expression tree based on the given tokens / elements. Other ways of implementing this would be via using the stack data structure to push and pop the given variables based on the input string.
