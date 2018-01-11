# Nmake macros for building Windows 32-Bit apps

all: Sample~1.exe

# Update the resource if necessary

Sample~1.res: Sample~1.rc Sample~1.h
    rc -r -fo Sample~1.res Sample~1.rc

# Update the object file if necessary

Sample~1.obj: Sample~1.cpp Sample~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Sample~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Sample~1.exe: Sample~1.obj Sample~1.res
    $(link) $(linkdebug) $(guiflags) -out:Sample~1.exe Sample~1.obj Sample~1.res $(guilibs) advapi.lib
