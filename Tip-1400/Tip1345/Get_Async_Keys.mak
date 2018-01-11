# Nmake macros for building Windows 32-Bit apps

all: Get_As~1.exe

# Update the resource if necessary

Get_As~1.res: Get_As~1.rc Get_As~1.h
    rc -r -fo Get_As~1.res Get_As~1.rc

# Update the object file if necessary

Get_As~1.obj: Get_As~1.cpp Get_As~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Get_As~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Get_As~1.exe: Get_As~1.obj Get_As~1.res
    $(link) $(linkdebug) $(guiflags) -out:Get_As~1.exe Get_As~1.obj Get_As~1.res $(guilibs) advapi.lib
