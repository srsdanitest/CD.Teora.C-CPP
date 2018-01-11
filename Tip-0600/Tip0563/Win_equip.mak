# Nmake macros for building Windows 32-Bit apps

all: ShowEqup.exe

# Update the resource if necessary

generic.res:generic.rc generic.h
    rc -r -fo generic.res generic.rc

# Update the object file if necessary

Win_e~1.obj: Win_e~1.cpp generic.cpp generic.h
    $(cc) $(cdebug) $(cflags) $(cvars) Win_e~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Win_e~1.exe: Win_e~1.obj generic.res
    $(link) $(linkdebug) $(guiflags) -out:Win_e~1.exe Win_e~1.obj generic.res $(guilibs) advapi.lib
