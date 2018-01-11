# Nmake macros for building Windows 32-Bit apps

all: Move_F~1.exe

# Update the resource if necessary

Move_F~1.res: Move_F~1.rc Move_F~1.h
    rc -r -fo Move_F~1.res Move_F~1.rc

# Update the object file if necessary

Move_F~1.obj: Move_F~1.cpp Move_F~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Move_F~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Move_F~1.exe: Move_F~1.obj Move_F~1.res
    $(link) $(linkdebug) $(guiflags) -out:Move_F~1.exe Move_F~1.obj Move_F~1.res $(guilibs) advapi.lib
