# Nmake macros for building Windows 32-Bit apps

all: Scroll1.exe

# Update the resource if necessary

Scroll1.res: Scroll1.rc Scroll1.h
    rc -r -fo Scroll1.res Scroll1.rc

# Update the object file if necessary

Scroll1.obj: Scroll1.cpp Scroll1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Scroll1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Scroll1.exe: Scroll1.obj Scroll1.res
    $(link) $(linkdebug) $(guiflags) -out:Scroll1.exe Scroll1.obj Scroll1.res $(guilibs) advapi.lib
