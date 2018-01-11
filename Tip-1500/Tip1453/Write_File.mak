# Nmake macros for building Windows 32-Bit apps

all: Write_~1.exe

# Update the resource if necessary

Write_~1.res: Write_~1.rc Write_~1.h
    rc -r -fo Write_~1.res Write_~1.rc

# Update the object file if necessary

Write_~1.obj: Write_~1.cpp Write_~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Write_~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Write_~1.exe: Write_~1.obj Write_~1.res
    $(link) $(linkdebug) $(guiflags) -out:Write_~1.exe Write_~1.obj Write_~1.res $(guilibs) advapi.lib
