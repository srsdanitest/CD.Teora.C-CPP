# Nmake macros for building Windows 32-Bit apps

all: enumpr~1.exe

# Update the resource if necessary

enumpr~1.res: enumpr~1.rc enumpr~1.h
    rc -r -fo enumpr~1.res enumpr~1.rc

# Update the object file if necessary

enumpr~1.obj: enumpr~1.cpp enumpr~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) enumpr~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

enumpr~1.exe: enumpr~1.obj enumpr~1.res
    $(link) $(linkdebug) $(guiflags) -out:enumpr~1.exe enumpr~1.obj enumpr~1.res $(guilibs) advapi.lib
