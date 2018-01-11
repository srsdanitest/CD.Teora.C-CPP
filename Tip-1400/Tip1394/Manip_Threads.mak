# Nmake macros for building Windows 32-Bit apps

all: Manip_~1.exe

# Update the resource if necessary

generic.res:generic.rc generic.h
    rc -r -fo generic.res generic.rc

# Update the object file if necessary

Manip_~1.obj: Manip_~1.cpp generic.cpp generic.h
    $(cc) $(cdebug) $(cflags) $(cvars) Manip_~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Manip_~1.exe: Manip_~1.obj generic.res
    $(link) $(linkdebug) $(guiflags) -out:Manip_~1.exe Manip_~1.obj generic.res $(guilibs) advapi.lib
