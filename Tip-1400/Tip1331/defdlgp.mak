# Nmake macros for building Windows 32-Bit apps

all: Defdlgp.exe

# Update the resource if necessary

Defdlgp.res: Defdlgp.rc Defdlgp.h
    rc -r -fo Defdlgp.res Defdlgp.rc

# Update the object file if necessary

Defdlgp.obj: Defdlgp.cpp Defdlgp.h
    $(cc) $(cdebug) $(cflags) $(cvars) Defdlgp.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Defdlgp.exe: Defdlgp.obj Defdlgp.res
    $(link) $(linkdebug) $(guiflags) -out:Defdlgp.exe Defdlgp.obj Defdlgp.res $(guilibs) advapi.lib
