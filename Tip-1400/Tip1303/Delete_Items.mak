# Nmake macros for building Windows 32-Bit apps

all: Add_Del.exe

# Update the resource if necessary

Delete~1.res: Delete~1.rc Delete~1.h
    rc -r -fo Delete~1.res Delete~1.rc

# Update the object file if necessary

Delete~1.obj: Delete~1.cpp Delete~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Delete~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Delete~1.exe: Delete~1.obj Delete~1.res
    $(link) $(linkdebug) $(guiflags) -out:Delete~1.exe Delete~1.obj Delete~1.res $(guilibs) advapi.lib
