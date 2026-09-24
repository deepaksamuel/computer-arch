# Demonstrations of compiler process

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