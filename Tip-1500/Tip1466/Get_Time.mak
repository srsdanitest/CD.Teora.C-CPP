# Nmake macros for building Windows 32-Bit apps

all: Get_Time.exe

# Update the resource if necessary

Get_Time.res: Get_Time.rc Get_Time.h
    rc -r -fo Get_Time.res Get_Time.rc

# Update the object file if necessary

Get_Time.obj: Get_Time.cpp Get_Time.h
    $(cc) $(cdebug) $(cflags) $(cvars) Get_Time.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Get_Time.exe: Get_Time.obj Get_Time.res
    $(link) $(linkdebug) $(guiflags) -out:Get_Time.exe Get_Time.obj Get_Time.res $(guilibs) advapi.lib
