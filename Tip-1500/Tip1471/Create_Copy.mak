# Nmake macros for building Windows 32-Bit apps

all: Create~1.exe

# Update the resource if necessary

Create~1.res: Create~1.rc Create~1.h
    rc -r -fo Create~1.res Create~1.rc

# Update the object file if necessary

Create~1.obj: Create~1.cpp Create~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Create~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Create~1.exe: Create~1.obj Create~1.res
    $(link) $(linkdebug) $(guiflags) -out:Create~1.exe Create~1.obj Create~1.res $(guilibs) advapi.lib
