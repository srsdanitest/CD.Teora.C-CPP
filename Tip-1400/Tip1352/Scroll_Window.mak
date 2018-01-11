# Nmake macros for building Windows 32-Bit apps

all: Scroll~1.exe

# Update the resource if necessary

Scroll~1.res: Scroll~1.rc Scroll~1.h
    rc -r -fo Scroll~1.res Scroll~1.rc

# Update the object file if necessary

Scroll~1.obj: Scroll~1.cpp Scroll~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Scroll~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Scroll~1.exe: Scroll~1.obj Scroll~1.res
    $(link) $(linkdebug) $(guiflags) -out:Scroll~1.exe Scroll~1.obj Scroll~1.res $(guilibs) advapi.lib
