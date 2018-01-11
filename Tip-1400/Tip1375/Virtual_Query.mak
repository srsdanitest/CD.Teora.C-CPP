# Nmake macros for building Windows 32-Bit apps

all: Virtua~1.exe

# Update the resource if necessary

Virtua~1.res: Virtua~1.rc Virtua~1.h
    rc -r -fo Virtua~1.res Virtua~1.rc

# Update the object file if necessary

Virtua~1.obj: Virtua~1.cpp Virtua~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Virtua~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Virtua~1.exe: Virtua~1.obj Virtua~1.res
    $(link) $(linkdebug) $(guiflags) -out:Virtua~1.exe Virtua~1.obj Virtua~1.res $(guilibs) advapi.lib
