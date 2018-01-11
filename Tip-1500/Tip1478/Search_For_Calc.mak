# Nmake macros for building Windows 32-Bit apps

all: Search~1.exe

# Update the resource if necessary

Search~1.res: Search~1.rc Search~1.h
    rc -r -fo Search~1.res Search~1.rc

# Update the object file if necessary

Search~1.obj: Search~1.cpp Search~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Search~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Search~1.exe: Search~1.obj Search~1.res
    $(link) $(linkdebug) $(guiflags) -out:Search~1.exe Search~1.obj Search~1.res $(guilibs) advapi.lib
