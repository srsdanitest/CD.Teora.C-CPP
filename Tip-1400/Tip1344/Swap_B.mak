# Nmake macros for building Windows 32-Bit apps

all: Swap_B.exe

# Update the resource if necessary

Swap_B.res: Swap_B.rc Swap_B.h
    rc -r -fo Swap_B.res Swap_B.rc

# Update the object file if necessary

Swap_B.obj: Swap_B.cpp Swap_B.h
    $(cc) $(cdebug) $(cflags) $(cvars) Swap_B.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Swap_B.exe: Swap_B.obj Swap_B.res
    $(link) $(linkdebug) $(guiflags) -out:Swap_B.exe Swap_B.obj Swap_B.res $(guilibs) advapi.lib
