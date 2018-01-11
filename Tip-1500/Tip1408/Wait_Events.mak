# Nmake macros for building Windows 32-Bit apps

all: Wait_E~1.exe

# Update the resource if necessary

generic.res:generic.rc generic.h
    rc -r -fo generic.res generic.rc

# Update the object file if necessary

Wait_E~1.obj: Wait_E~1.cpp generic.cpp generic.h
    $(cc) $(cdebug) $(cflags) $(cvars) Wait_E~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Wait_E~1.exe: Wait_E~1.obj generic.res
    $(link) $(linkdebug) $(guiflags) -out:Wait_E~1.exe Wait_E~1.obj generic.res $(guilibs) advapi.lib
