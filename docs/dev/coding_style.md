# Coding style of Bluebox2D:

Like most of the software (And software developers), when writing code, you follow some specific conventions to comply with the consistency and readability of the source code. Since Bluebox2D tries to be as lightweight as a compiler can get it but also is an open source project, you are adviced to read this document at least 3 times to get a good idea of it.

Contributions following the style of coding defined here are much, much more likely to get accepted. So let's get started.

## SECTIONS
[1. Naming variables and functions](#1-naming-variables-and-functions)\
[2. Storage class specifiers](#2-storage-class-specifiers)\
[3. Rules of the thumb](#3-rules-of-the-thumb)\
[4. Reusing Code](#4-reusing-code) \
[5. Types](#5-types)\
[6. Scopes](#6-scopes)\
[7. Macros](#7-macros)\
[8. The general coding style](#8-general-coding-style)
# 1. Naming variables and functions

When you declare a new function or variable, always, but always, use the CamelCase syntax. An exception is static functions and throw-away variables. Here's an example:

```c
/* Valid. */
static void* get_texture_by_id(uint64_t id) {
        return NULL;
}

/* Also valid */
int RedrawTexture(Texture tex, Renderer* RendererID) {
        /* Also valid */
        int _tmp_var = 32;
        ASSERT(RendererID != NULL);
        return _tmp_var;
}

/* Invalid */

FORCE_INLINE inline int get_texture_count(void) {
        /* This code is also extremely bad practice, but let's ignore this. */
        int TemporaryVariable = *(int*) SomeTexture;
        return TemporaryVariable;
}
```
Avoid using (Especially in C) this type of naming too:
```c
/* Don't do this. */
uint32_t getInt32(bool uselessBoolean) {
        uint32_t returnValue = 32;
        return returnValue;
}
```

# 2. Storage Class Specifiers

C permits three storage classes. If you don't know any, stop reading here and read more about it:

- extern
- static
- register

You are free to use all of them, but always have a balance and a limit. For example, use ```extern``` on function declarations:
```c
/* This function gets the last texture used and returns it. */
extern Texture GetLastTexture(uint32_t ID);
```
But don't use it to refer to another variable:
```c
/* Don't do this. */
extern Texture Layer0;
```

The same goes for `static`, but you can use it much more. For example, if you have a function that you are going to use in one file, it makes it better to declare it `static`. However, if you know you need to save a value in your program for the entire life, then you can always use static. A great example is in `src/render.c`, line 121:
```c
  // We need to declare this as static so that the same message doesn't appear twice.
  static bool MessageShown = false;
```
The user will only be informed once with the message, and never again. Until he shuts down the program. Then it resets :P

Last goes the `register`. Registers are very expensive, and you are adviced not to declare anything with that specifier. The compiler is much smarter than any human when it comes to optimization, and it will do the right thing. After all the compiler will probably ignore you and determine on its own whether the variable should go into a register.
The only variable using this specifier in Bluebox2D is the `TextureID` variable in the `_RenderParticle()` function.

# 3. Rules of the thumb

Some things to remember when programming Bluebox2D go here. They couldn't fit in any other category so they deserve their own.

- **1. Don't declare everything inline.**

Seriously, don't. Some people like to think that declaring something as `inline` makes the program the most efficient C program to ever exist. That is far from the truth. In fact, if not handled correctly, the program may actually slow down. 

If you want to declare a function as `inline`, here are three things to remember (If you say no to any of these, don't inline it):
- 1. Is the function less than 5 lines of code (Including variables)?
- 2. Do you want it to actually inline it, or do you want a macro?
- 3. Are you calling this function inside a loop?

In [Section 7](#7-macros), you may want to read about the `FORCE_INLINE` attribute, which does exactly what it sounds like. It only works for GCC though.

- **2. Try to use `const` more often.**

`const` is one of the most used and useful keywords in C. When you declare something as constant, you tell both the program and the compiler not to change it. Of course, someone will just do the classic "Drop the constants" trick with pointers, but it's a good practice not to do that either.
Especially in function parameters, everything should be declared as `const`. Basically this is what a function declaration should look like:
```c
/* A function to multiply the first two numbers added by the third number. */
const double foo(const double FirstNum, const double SecondNum, const double ThirdNum) {
        return ((FirstNum + SecondNum) * ThirdNum);
}
```
Add an exception here if the type is opaque or is allocated in the heap. eg:
```c
        /* Get some memory for Bluebox2D. */
        void* NewMemory(const size_t Bytes, FILE* Write) {
                assert(Bytes != 0);
                void* retval = (void*) malloc(Bytes);
                assert(write_to_file(Write, VARIABLE, "Bytes allocated", (void*)Bytes) == 0);
                return retval;
        }
```
- **3. Use pointers.**
Sure, you can do:
```c
Texture CreateTexture(SDL_Renderer* RendererID, SDL_Window* WindowID) {
        /* ... */
}
```
But when we call a function with its arguments filled, we don't actually give it the variable we are passing, but copying the variable (And hence wasting memory and speed). Now a few bytes of data is not concerning and the speed difference only applies because the compiler has to actually copy the data, but what happens if we call this code for each frame?

```c
while (!Quit) {
        /* Creates a texture every frame */
        CreateTexture(RendererID, WindowID);
        WindowUpdate(&RendererID);
}
```
If we get even a 0.3% copying overhead for this function (100 being 16.66ms), we spend about 0.05ms just copying the data. That time is huge for graphics, and older machines may even have reduced FPS because of it.

Now if we do this again, but passing by reference:

```c
Texture CreateTexture(SDL_Renderer** Renderer, SDL_Window** Window) {
        /* ... */
}

/* ... */
while (!Quit) {
        CreateTexture(&RendererID, &WindowID);
}
```
We are saving this tiny bit of time which can be used for other calls. We did this by directly locating and accessing `RendererID` and `WindowID`, through a pointer. Cool, ain't it?

# 4. Reusing code

Bluebox2D already has alot of code to be reused. If a function, macro or variable already does what you want to do, use it. That means:

```c
/*
 * What this function does, step by step:
 * 1. Creates a new texture if there is not one already, and copies it to the renderer.
 * 2. Either sets an existing ID by CustomID set to true and ID not being NULL,
 * or creates a new one and uses it there.
*/
uint32_t SetTextureID(TextureData* data, bool CustomID, uint64_t* ID) {
        /* We assume the user wants to create the texture here. */
        if (!data->TextureID) {
                data->TextureID = _RenderParticle(/* ... */);
        }
        if (CustomID && ID) 
                data->ID = GenerateHashID(256);
        else
                data->ID = 0; // An ID of 0 is meant to indicate failure.
        return data->ID;
}
```
Now Bluebox2D does not even need to identify each texture (For now?), but if it did, the first function is already present in Bluebox2D (Textures are supposed to be copied the second they are created for safety), and the second can be implemented if needed without much code.

The point is, do not duplicate code. A function exists to be reused and hence you should use it too.

# 5. Types

Bluebox2D offers some custom types, but mostly relies on the default SDL2 types. Commonly used SDL2 types are `typedef`'d to increase readability. Eg:

```c
/* From include/type.h */
typedef SDL_Texture*  Texture;
typedef SDL_Renderer* Renderer;
```

The custom types Bluebox offers are mainly used to interact with the application at runtime. These are:

|      Type      |     What is is used for     | Function to call  |
|----------------|---------------------------- |-------------------|
| BlueboxVersion |   Get the Bluebox version   | GetBlueboxVersion |
|     Mouse      |   Get data about the mouse  |        --         |
|  ElementData   |      Under development      |   Internal usage  |
|  RendererSize  | Get the size of the renderer|   Internal usage  |
This list is probably going to be extended by v0.5.

# 6. Scopes

When you want to share an instance of an object to different functions, do NOT declare it as static in the global scope:

```c
/* NEVER do this. */
static Renderer RendererID;
```
Instead, declare this variable in `main()` or `PollEvents()`, and when a function needs them, pass them through a pointer as described above:
```c
int main(int argc, char* argv[]) {
        /* ... */
        Renderer RendererID = NULL; // No need to initialize it btw
        /* Give the address of the renderer to a function that needs it. */
        PassTheRendererHere(&RendererID);
}
```
The only thing that should be on a global scope, is anything that may be used through functions in the same file and only. Also use `NOINIT` attribute (See Bluebox.h) to save some startup time.

# 7. Macros

Several macros are often used in Bluebox2D, sometimes to validate expressions, sometimes to optimize the code and sometimes to simply reduce function call overhead.

These are the macros Bluebox2D defines on its behalf, and their use:

|  Macro Name  | Usage |
| ------------ | ----- |
|    MS(x)     | Count milliseconds of a second |
|    NOINIT    | GCC Optimization Flag |
| FORCE_INLINE | Force a function to be inlined |
|   NORETURN   | Functions declared with this will never return in the lifetime of the program |
|   NOSTRING   | Indicates that the array is not a string but just an array |
|__DEPRECATED__| The function or variable is going to be removed soon |
|    UNUSED    | The variable is not going to be used for now, avoids `-Wunused`|
|    NONNULL   | The function failed, but the failure was not critical and it can be recalled safely. |

# 8. General Coding Style

And we are gonna finish this one with smaller rules about writing code to contribute. 
Now you may disagree with some of these, and this is fine. The penalty isn't even that huge. But following it is greatly appreciated.

- **Brackets**

Like most UNIX-like software, the brackets are almost always placed after a previous token, and no newline in between. Examples:

```c

/* E1: When defining structs: */
struct UserData {
        const char* hostname;
        Mouse BoundMouse;
}

/* E2: When defining functions */
Renderer* GetRenderer(void) {
        return &Renderer;
}

/* E3: When creating new scopes */
inline void ScopeTest(void) {
        {
                /* This is a new, nested scope. */
        }
}

/* E4: When using if, for, while etc. */
if (!(x)) {
        printf("%s", "\nAssertion failed.");
        return -127;
} else {
        printf("%s", "\nAssertion did not fail.");
        return 0;
}
```

- **Indentation**

Indentation is the least important part here, although still useful. The recommended indentation rules are:

- 1. A tab should equal 8 spaces.
```c
if (Something) {
        /* 8-space indentation. */
}
```
- 2. You should never go deeper than 4 levels.
```c
/* The maximum indentation level allowed. */
if (Something) {
        switch (Result) {
                case SUCCESS:
                        break;
                default:
                        return -127;
        }
}
```
- 3. Use tabs, **ALWAYS**.

- **Commenting**

The code should always be readable enough to read for someone who barely knows C. If you need comments to explain your code, make sure your language is clear and complies with the next 2-3 lines. eg:

```c
/*
This function clears the screen, with a different color each time.
*/

void ClearScreenRC(Renderer* RendererID) {
        /* The initial color values */
        float var = 0.0f;
        /* How much to increment them in each call */
        float incr = 0.15f;
        static float color = var + incr;
        SDL_RenderClear(/* ... */);
}
```
The above example is a bit overcommenting, because it's clear what we are doing in the next few lines of code. But it's a good example to get started.\
A bad practice would be:
```c
/* W: Overcommenting */

/* This variable represents value foo. */
static int foo = 32;
/* To modify the variable through a function, you need to access its address. */
static int* foo_ptr = &foo;

/* A function to change foo to a new value passed as parameter. */
static void change_foo_to(int value) {
        /* Here we access the address of foo through its pointer and change the value stored in that address.
           We can only do this with a pointer, because normally variables are passed by value to the function, but we need passing by reference instead.
        */
        *foo_ptr = value;
}

```

So in general, when writing comments, write them in a way that they are not way too much but also exist if needed.