# Nmake macros for building Windows 32-Bit apps

all: First_~1.exe

# Update the resource if necessary

First_~1.res: First_~1.rc First_~1.h
    rc -r -fo First_~1.res First_~1.rc

# Update the object file if necessary

First_~1.obj: First_~1.cpp First_~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) First_~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

First_~1.exe: First_~1.obj First_~1.res
    $(link) $(linkdebug) $(guiflags) -out:First_~1.exe First_~1.obj First_~1.res $(guilibs) advapi.lib
