# Nmake macros for building Windows 32-Bit apps

all: Simple~1.exe

# Update the resource if necessary

generic.res:generic.rc generic.h
    rc -r -fo generic.res generic.rc

# Update the object file if necessary

Simple~1.obj: Simple~1.cpp generic.cpp generic.h
    $(cc) $(cdebug) $(cflags) $(cvars) Simple~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Simple~1.exe: Simple~1.obj generic.res
    $(link) $(linkdebug) $(guiflags) -out:Simple~1.exe Simple~1.obj generic.res $(guilibs) advapi.lib
