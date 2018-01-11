# Nmake macros for building Windows 32-Bit apps

all: Paint_~1.exe

# Update the resource if necessary

Paint_~1.res: Paint_~1.rc Paint_~1.h
    rc -r -fo Paint_~1.res Paint_~1.rc

# Update the object file if necessary

Paint_~1.obj: Paint_~1.cpp Paint_~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Paint_~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Paint_~1.exe: Paint_~1.obj Paint_~1.res
    $(link) $(linkdebug) $(guiflags) -out:Paint_~1.exe Paint_~1.obj Paint_~1.res $(guilibs) advapi.lib
