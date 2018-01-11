# Nmake macros for building Windows 32-Bit apps

all: Add_Del.exe

# Update the resource if necessary

show_~1.res: Add_Del.rc Add_Del.h
    rc -r -fo Add_Del.res Add_Del.rc

# Update the object file if necessary

Add_Del.obj: Add_Del.cpp Add_Del.h
    $(cc) $(cdebug) $(cflags) $(cvars) Add_Del.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Add_Del.exe: Add_Del.obj Add_Del.res
    $(link) $(linkdebug) $(guiflags) -out:Add_Del.exe Add_Del.obj Add_Del.res $(guilibs) advapi.lib
