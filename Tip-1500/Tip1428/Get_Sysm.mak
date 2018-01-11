# Nmake macros for building Windows 32-Bit apps

all: Get_SysM.exe

# Update the resource if necessary

Get_SysM.res: Get_SysM.rc Get_SysM.h
    rc -r -fo Get_SysM.res Get_SysM.rc

# Update the object file if necessary

Get_SysM.obj: Get_SysM.cpp Get_SysM.h
    $(cc) $(cdebug) $(cflags) $(cvars) Get_SysM.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Get_SysM.exe: Get_SysM.obj Get_SysM.res
    $(link) $(linkdebug) $(guiflags) -out:Get_SysM.exe Get_SysM.obj Get_SysM.res $(guilibs) advapi.lib
