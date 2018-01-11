# Nmake macros for building Windows 32-Bit apps

all: Enable~1.exe

# Update the resource if necessary

Enable~1.res: Enable~1.rc Enable~1.h
    rc -r -fo Enable~1.res Enable~1.rc

# Update the object file if necessary

Enable~1.obj: Enable~1.cpp Enable~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Enable~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Enable~1.exe: Enable~1.obj Enable~1.res
    $(link) $(linkdebug) $(guiflags) -out:Enable~1.exe Enable~1.obj Enable~1.res $(guilibs) advapi.lib
