# Nmake macros for building Windows 32-Bit apps

all: Create~1.exe

# Update the resource if necessary

generic.res:generic.rc generic.h
    rc -r -fo generic.res generic.rc

# Update the object file if necessary

Create~1.obj: Create~1.cpp generic.cpp generic.h
    $(cc) $(cdebug) $(cflags) $(cvars) Create~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Create~1.exe: Create~1.obj generic.res
    $(link) $(linkdebug) $(guiflags) -out:Create~1.exe Create~1.obj generic.res $(guilibs) advapi.lib
