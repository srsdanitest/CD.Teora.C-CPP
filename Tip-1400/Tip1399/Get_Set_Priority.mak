# Nmake macros for building Windows 32-Bit apps

all: Get_Se~1.exe

# Update the resource if necessary

generic.res:generic.rc generic.h
    rc -r -fo generic.res generic.rc

# Update the object file if necessary

Get_Se~1.obj: Get_Se~1.cpp generic.cpp generic.h
    $(cc) $(cdebug) $(cflags) $(cvars) Get_Se~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Get_Se~1.exe: Get_Se~1.obj generic.res
    $(link) $(linkdebug) $(guiflags) -out:Get_Se~1.exe Get_Se~1.obj generic.res $(guilibs) advapi.lib
