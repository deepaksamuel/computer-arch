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

- Add a #define DEMO statement and
    ```c
    #ifdef DEMO
    printf("Debug mode active\n");
    #endif
    ```
    inside the main function and see what happens at the preprocessor level

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



## Compiler optimization 2 (see demo-c.c)
Use https://godbolt.org/ for demostrations
```c
int main(int n) {
    int s = 0;
    for (int i = 0; i < n; i++) {
        int k = 2 * 3;        // constant expression
        s += i * i + k - 6;   // k - 6 is always 0
    }
    return s;
}

```
In this task we will understand higher levels of optimization

Without optimization:

`gcc  -save-temps demo-c.c -o hello`

- O1

    - gcc -O1 -save-temps demo-c.c -o hello
    - You will see that the k-6 is gone since it does not make any sense  
    
    ```c 
        .file	"demo-c.c"  
        .text  
        .globl	main
        .type	main, @function
    main:
    .LFB0:
        .cfi_startproc
        endbr64
        testl	%edi, %edi
        jle	.L4
        movl	$0, %eax
        movl	$0, %edx
    .L3:
        movl	%eax, %ecx
        imull	%eax, %ecx
        addl	%ecx, %edx
        addl	$1, %eax
        cmpl	%eax, %edi
        jne	.L3
    .L1:
        movl	%edx, %eax
        ret
    .L4:
        movl	$0, %edx
        jmp	.L1
        .cfi_endproc
    ```

- O2
    - gcc -O2 -save-temps demo-c.c -o hello

    ```c   
        main:  
    .LFB0:
        .cfi_startproc
        endbr64
        testl	%edi, %edi
        jle	.L4
        xorl	%eax, %eax
        xorl	%edx, %edx
        .p2align 4,,10
        .p2align 3
    .L3:
        movl	%eax, %ecx
        imull	%eax, %ecx
        addl	$1, %eax
        addl	%ecx, %edx
        cmpl	%eax, %edi
        jne	.L3
    .L1:
        movl	%edx, %eax
        ret
    .L4:
        xorl	%edx, %edx
    ```

    - First notice the use of XOR. It is a faster way to initialize a register to 0. Compared to previous compilations where 0 was explicitly moved to those register

    - 
