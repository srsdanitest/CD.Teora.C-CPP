# Nmake macros for building Windows 32-Bit apps

all: show_m~1.exe

# Update the resource if necessary

show_m~1.res: show_m~1.rc show_m~1.h
    rc -r -fo show_m~1.res show_m~1.rc

# Update the object file if necessary

show_m~1.obj: show_m~1.cpp show_m~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) show_m~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

show_m~1.exe: show_m~1.obj show_m~1.res
    $(link) $(linkdebug) $(guiflags) -out:show_m~1.exe show_m~1.obj show_m~1.res $(guilibs) advapi.lib
