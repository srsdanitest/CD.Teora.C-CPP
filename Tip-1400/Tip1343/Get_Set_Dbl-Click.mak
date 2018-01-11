# Nmake macros for building Windows 32-Bit apps

all: Get_Se~1.exe

# Update the resource if necessary

Get_Se~1.res: Get_Se~1.rc Get_Se~1.h
    rc -r -fo Get_Se~1.res Get_Se~1.rc

# Update the object file if necessary

Get_Se~1.obj: Get_Se~1.cpp Get_Se~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Get_Se~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Get_Se~1.exe: Get_Se~1.obj Get_Se~1.res
    $(link) $(linkdebug) $(guiflags) -out:Get_Se~1.exe Get_Se~1.obj Get_Se~1.res $(guilibs) advapi.lib
