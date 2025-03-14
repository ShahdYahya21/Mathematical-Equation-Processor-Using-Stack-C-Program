# **Mathematical Equation Processor Using Stack (C Program)**  

This C program processes **mathematical equations** by reading them from a file, checking their validity, converting them from **infix notation to prefix notation**, and evaluating them using **stack-based operations**.

## **Core Stack Operations**  

- `createStack()` – Initializes an empty stack.  
- `push()` – Adds an element to the stack.  
- `pop()` – Removes the top element from the stack.  
- `Top()` – Retrieves the top element without removing it.  
- `IsEmpty()` – Checks if the stack is empty.  

## **Mathematical Processing Functions**  

The program supports the following **validation and transformation functions**:  

- `IsBalanced(char equation[maxLength][maxLength])` – Checks if the parentheses (`()`, `[]`) in the equation are balanced.  
- `ValidOperators(char equation[maxLength][maxLength])` – Ensures valid operator usage (e.g., no consecutive operators, valid placement).  
- `reverse(char array[maxLength][maxLength])` – Reverses an equation stored in an array.  
- `negativeCases(char equations[][maxLength][maxLength], int count, const int valid[maxLength])` – Handles negative numbers in equations (e.g., `3+-5` is treated as `3 + (-5)`).  

## **Arithmetic Operations**  

The program supports the following arithmetic operations:  

- `InfixToPrefix(char equations[maxLength][maxLength][maxLength], int count, const int valid[maxLength])`  
  - Converts **infix expressions** (e.g., `3 + 5`) to **prefix notation** (e.g., `+ 3 5`).  
  - Uses a **stack-based approach** to handle operator precedence and parentheses.  

- `evaluation(char arr[maxLength][maxLength][maxLength], int count, const int valid[maxLength])`  
  - Evaluates **prefix expressions** and computes the result using a stack.  

## **Features** 

**Reads equations from an input file (`Input`)**  
**Checks equation validity (balanced parentheses, correct operator usage)**  
**Converts infix equations to prefix notation**  
**Evaluates prefix expressions**  
**Handles negative numbers correctly**  

> **Unfortunately, the program does not handle division by zero**

**Prints results to an output file (`OutputEquation`)**  
**Provides a menu-based user interface**

## Program Output Example
When running the calculator, the user is presented with the following menu:

#### Welcome to my calculator
Select (1 - 7):

1. Enter the name of the file to read it
2. Check the validity of equations
3. Print the prefix expressions
4. Evaluate the prefix expressions
5. Print invalid equations
6. Print all equations to a file indicating for each input equation if it is valid or not and if valid, print out the prefix expression and its result
7. Exit

---

#### If the User Chooses 1: Enter the Name of the File to Read It

**Input:**

equation #1 -> -(8+9+8)  
equation #2 -> -5+-5  
equation #3 -> 2+(14-9)+4*[6+(7+5)-1]  
equation #4 -> ()(4+9)  
equation #5 -> (7-9(  
equation #6 -> -((4+9))  
equation #7 -> 9+8  
equation #8 -> 4+2+(4+4)  
equation #9 -> 7+7  
equation #10 -> (((5+4)))  
equation #11 -> 100+99  
equation #12 -> 5/-4  
equation #13 -> -5-(3+9)  

---

#### If the User Chooses 2: Check the Validity of Equations

**Output:**

equation #1 -> valid  
equation #2 -> valid  
equation #3 -> valid  
equation #4 -> invalid -> () is not valid  
equation #5 -> invalid -> ( is not closed  
equation #6 -> valid  
equation #7 -> valid  
equation #8 -> valid  
equation #9 -> valid  
equation #10 -> valid  
equation #11 -> valid  
equation #12 -> valid  
equation #13 -> valid  

---

#### If the User Chooses 3: Print the Prefix Expressions

**Output:**

equation 1:  
+ -8 + -9 -8  

equation 2:  
+ -5 -5  

equation 3:  
+ 2 + - 14 9 * 4 + 6 - + 7 5 1  

equation 6:  
+ -4 -9  

equation 7:  
+ 9 8  

equation 8:  
+ 4 + 2 + 4 4  

equation 9:  
+ 7 7  

equation 10:  
+ 5 4  

equation 11:  
+ 100 99  

equation 12:  
/ 5 -4  

equation 13:  
- -5 + 3 9  


---

#### If the User Chooses 4: Evaluate the Prefix Expressions

**Output:**

equation 1 -> -25  
equation 2 -> -10  
equation 3 -> 75  
equation 6 -> -13  
equation 7 -> 17  
equation 8 -> 14  
equation 9 -> 14  
equation 10 -> 9  
equation 11 -> 199  
equation 12 -> -1  
equation 13 -> -17  

---

#### If the User Chooses 5: Print Invalid Equations

**Output:**

invalid equations  
()(4+9)  
(7-9(

---

#### If the User Chooses 6: Print All Equations to a File

**Output:**

The program will write to an output file the following details for each equation:
- Whether the equation is valid or invalid
- The prefix expression (if valid)
- The evaluation result (if valid)

---

#### If the User Chooses 7: Exit

This option will exit the program.

---

