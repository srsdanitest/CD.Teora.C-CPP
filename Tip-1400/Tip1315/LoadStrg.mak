# Nmake macros for building Windows 32-Bit apps

all: LoadStrg.exe

# Update the resource if necessary

show_~1.res: LoadStrg.rc LoadStrg.h
    rc -r -fo LoadStrg.res LoadStrg.rc

# Update the object file if necessary

LoadStrg.obj: LoadStrg.cpp LoadStrg.h
    $(cc) $(cdebug) $(cflags) $(cvars) LoadStrg.cpp

# Update the executable file if necessary, and if so, add the resource back in.

LoadStrg.exe: LoadStrg.obj LoadStrg.res
    $(link) $(linkdebug) $(guiflags) -out:LoadStrg.exe LoadStrg.obj LoadStrg.res $(guilibs) advapi.lib
