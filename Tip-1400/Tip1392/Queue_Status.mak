# Nmake macros for building Windows 32-Bit apps

all: Queue~1.exe

# Update the resource if necessary

generic.res:generic.rc generic.h
    rc -r -fo generic.res generic.rc

# Update the object file if necessary

Queue~1.obj: Queue~1.cpp generic.cpp generic.h
    $(cc) $(cdebug) $(cflags) $(cvars) Queue~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Queue~1.exe: Queue~1.obj generic.res
    $(link) $(linkdebug) $(guiflags) -out:Queue~1.exe Queue~1.obj generic.res $(guilibs) advapi.lib
