# Demonstrations of compiler process

The process of compilation takes place in many intermediate steps:

Text input &rarr; Preprocess &rarr; compile &rarr; assemble &rarr; link &rarr; binary output

- Preprocessor outputs a text file (.i)
- compiler outputs an assembly language file (.s)

## Demo a:

Compile command:
 - gcc -save-temps demo-a.c -o hello

### Preprocessor output (.i file):

 Replaces the contents of #include # define statement with the respective contents (that's why they are called as preprocessor directives)

 - Add a comment to the file, compile and see at the end what happens to the output file (at the end of it, you will still see it)
    - comments are removed in the preprocessor output

- Add some garbage text somewhere
    - Garbage remain as garbage.

- Intentionally make an error
    - Preprocessor file still gets generated

- Add a #define statement and see:
    - #define N 10
    - int a = 5 + N

### Assembler output (.s file)

Converts to mnemonics (assembly language)

- Constant folding:

    Constant folding is a compiler optimization technique where expressions containing fixed values are calculated and simplified during compilation rather than at runtime
    - Check that when you do 1+5, the number 6 is already present in the assembly code even before it goes to to the runtime.
    - You will not see the ADD mnemonic

    - In order to see the ADD mnemonic:

    ```c
    int b
    int a = 5+b;
    ```

## Compiler optimization (see demo-b.c)
```c
int x = 10;
if (x > 16) { x=8;} // Impossible condition
```
The if condition is never going to be satisifed. 

- Compiling without optimization
    - gcc -save-temps demo-b.c -o hello
        You will see a `cmpl	$16, -4(%rbp)` which is writing the assembly code for the if statement (compare)

- Compiling with optimization (level 1: -O1)
    - gcc -O1 -save-temps demo-b.c -o hello
    You will see the if condition has gone away since it is trivial.