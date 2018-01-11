# Nmake macros for building Windows 32-Bit apps

all: Handle~1.exe

# Update the resource if necessary

generic.res:generic.rc generic.h
    rc -r -fo generic.res generic.rc

# Update the object file if necessary

Handle~1.obj: Handle~1.cpp generic.cpp generic.h
    $(cc) $(cdebug) $(cflags) $(cvars) Handle~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Handle~1.exe: Handle~1.obj generic.res
    $(link) $(linkdebug) $(guiflags) -out:Handle~1.exe Handle~1.obj generic.res $(guilibs) advapi.lib
