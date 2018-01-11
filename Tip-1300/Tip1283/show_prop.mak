# Nmake macros for building Windows 32-Bit apps

all: show_p~1.exe

# Update the resource if necessary

show_p~1.res: show_p~1.rc show_p~1.h
    rc -r -fo show_p~1.res show_p~1.rc

# Update the object file if necessary

show_p~1.obj: show_p~1.cpp show_p~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) show_p~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

show_p~1.exe: show_p~1.obj show_p~1.res
    $(link) $(linkdebug) $(guiflags) -out:show_p~1.exe show_p~1.obj show_p~1.res $(guilibs) advapi.lib
