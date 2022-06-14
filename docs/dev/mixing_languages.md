# Mixing Languages

Although not used, Bluebox2D can be developed in other languages too, if needed. That is achieved by calling external functions at runtime (Or the entire source / object, if we deal with something like Python) and getting the results back. The codebase is not implemented as of now; It is extremely easy to implement it for another language. In all of this, ignore C++.

C++ is a special case, because both C and C++ in the end of the day are just high-level assembly. That means two files, one with C code only and the other with C++ code, can technically be mixed. For example:

```c
/* c_source.c */
#include <stdio.h>
#include <stdlib.h>

#include "cpp_header.h" // Contains the declaration for print_number
#define SOMETHING

int main(int argc, char** argv) {
        int num = 768;
        print_number(num);
}
```

```cxx
/* cpp_source.cpp */

#include <iostream>

void print_number(int number) {
        std::cout << number << std::endl;
        return;
}
```

In order to mix the two programs, we have to avoid linking and compile it manually. First, we will use GCC, which will compile both files without errors. We need to pass the `-c` flag to tell it not to link our files.

So that would be:
```sh
$ gcc -c cpp_source.cpp -o -fno-use-cxa-atexit cpp.o && gcc -c c_source.c -o c_source.o
```

Now we need to link them, along with eachother's standard library. That means:

```sh
$ ld cpp.o c_source.o -lc -lstdc++ -e main
```

Usually this approach is taken for modules to be loaded at runtime, since someone may want to write their module in C++.