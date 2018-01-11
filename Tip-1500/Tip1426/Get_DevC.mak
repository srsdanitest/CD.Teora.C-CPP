# Nmake macros for building Windows 32-Bit apps

all: Get_DevC.exe

# Update the resource if necessary

Get_DevC.res: Get_DevC.rc Get_DevC.h
    rc -r -fo Get_DevC.res Get_DevC.rc

# Update the object file if necessary

Get_DevC.obj: Get_DevC.cpp Get_DevC.h
    $(cc) $(cdebug) $(cflags) $(cvars) Get_DevC.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Get_DevC.exe: Get_DevC.obj Get_DevC.res
    $(link) $(linkdebug) $(guiflags) -out:Get_DevC.exe Get_DevC.obj Get_DevC.res $(guilibs) advapi.lib
