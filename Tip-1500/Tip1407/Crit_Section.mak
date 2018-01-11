# Nmake macros for building Windows 32-Bit apps

all: Crit_S~1.exe

# Update the resource if necessary

generic.res:generic.rc generic.h
    rc -r -fo generic.res generic.rc

# Update the object file if necessary

Crit_S~1.obj: Crit_S~1.cpp generic.cpp generic.h
    $(cc) $(cdebug) $(cflags) $(cvars) Crit_S~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Crit_S~1.exe: Crit_S~1.obj generic.res
    $(link) $(linkdebug) $(guiflags) -out:Crit_S~1.exe Crit_S~1.obj generic.res $(guilibs) advapi.lib
