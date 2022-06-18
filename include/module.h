#ifndef __MODULE_H__
#define __MODULE_H__

#define MODULE_SUCCESS	0
#define MODULE_NO_ENTR	127
#define MODULE_INVALID	-1

/*
 * An opaque type, representing a module. You should NOT
 * free() any object like this manually.
*/

typedef struct Module Module;

/*
 * Load the module into Bluebox2D and set it ready for use.
 * This function does NOT check if the module is valid. If needed, soon
 * a function may be added for extra explanation.
*/

extern Module* LoadModule(const char* filename);

/* 
 * Execute the module.
 * As described in the Bluebox2D modules documentation, this function
 * just calls the init() function of the module, aka its supposed entry point.
 * Will return MODULE_NO_ENTR if the module does not have the function, or 
 * MODULE_INVALID if the module is invalid. Else, MODULE_SUCCESS.
*/

extern int ExecuteModule(Module* mod);

/*
 * Unload the module from Bluebox2D.
 * This function does not force quit, and hence, if the module has failed,
 * you should instead call UnloadModuleF() which forcefully unloads the module.
*/

extern void UnloadModule(Module* mod);

/*
 * Forcefully remove the module from Bluebox2D.
 * If the module is for whatever reason failing, you should immediately call this function.
 * Make sure you do not cause any memory leaks !
 * VERY UNSAFE FUNCTION: There's a chance that it may even cause a segmentation fault.
*/

extern void UnloadModuleF(Module* mod);

#endif /* __MODULE_H__ */
