/* The maximum amount of KBs a module can receive at runtime. */
#define MAXBUF	1024
#define __MODULE_API__

#define NOEXITFUNC 	    -88
#define MODULE_EXIT_SUCCESS 0

#include <module.h>
#include <dlfcn.h>

struct Module {
	void* handle;
	bool open;
	char* filename;
};

/* Do not use FORCE_INLINE in this, the compiler can decide here. */
inline static int call_quit_module(Module* mod) {
	int(*__quit)(void) = dlsym(mod->handle, "exitmod");
	if (!__quit)
		return NOEXITFUNC;
	(*__quit)();
	return MODULE_EXIT_SUCCESS;
}

Module* LoadModule(const char* filename) {
	assert(filename != NULL);
	Module* module = calloc(1, sizeof(struct Module));
	if (!module) {
		LogMessage("Could not allocate memory for the module");
		return NULL;
	}
	module->filename = filename;
	module->handle	 = dlopen(filename, RTLD_LAZY);
	if (!module->handle) {
		LogMessage("Could not load shared object");
		return NULL;
	}	
	module->open = true;
	return module;
	
}

int ExecuteModule(Module* mod) {
	ASSERT(mod != NULL);
	int (*init)(void) = dlsym(mod->handle, "init");
	if (!init) 
		return MODULE_NO_ENTR;
	if ((*init)() != 0)
		return MODULE_FAILURE;
	return MODULE_SUCCESS;
}

void UnloadModule(Module* mod) {
	ASSERT(mod != NULL);
	call_quit_module(mod);
	dlclose(mod->handle);
	/* We will also free the module here, to save some space in calls. */
	free(mod);
}

void UnloadModuleF(Module* mod) {
	ASSERT(mod != NULL);
	/* YES, not closing the shared object will cause a memory leak. */
	dlclose(mod->handle);
	free(mod);
}
