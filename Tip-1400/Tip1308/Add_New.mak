# Nmake macros for building Windows 32-Bit apps

all: Add_New.exe

# Update the resource if necessary

Add_New.res: Add_New.rc Add_New.h
    rc -r -fo Add_New.res Add_New.rc

# Update the object file if necessary

Add_New.obj: Add_New.cpp Add_New.h
    $(cc) $(cdebug) $(cflags) $(cvars) Add_New.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Add_New.exe: Add_New.obj Add_New.res
    $(link) $(linkdebug) $(guiflags) -out:Add_New.exe Add_New.obj Add_New.res $(guilibs) advapi.lib
