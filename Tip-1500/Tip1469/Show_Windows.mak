# Nmake macros for building Windows 32-Bit apps

all: Show_W~1.exe

# Update the resource if necessary

generic.res:generic.rc generic.h
    rc -r -fo generic.res generic.rc

# Update the object file if necessary

Show_W~1.obj: Show_W~1.cpp generic.cpp generic.h
    $(cc) $(cdebug) $(cflags) $(cvars) Show_W~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Show_W~1.exe: Show_W~1.obj generic.res
    $(link) $(linkdebug) $(guiflags) -out:Show_W~1.exe Show_W~1.obj generic.res $(guilibs) advapi.lib
