# Nmake macros for building Windows 32-Bit apps

all: Dlgbox.exe

# Update the resource if necessary

show_~1.res: Dlgbox.rc Dlgbox.h
    rc -r -fo Dlgbox.res Dlgbox.rc

# Update the object file if necessary

Dlgbox.obj: Dlgbox.cpp Dlgbox.h
    $(cc) $(cdebug) $(cflags) $(cvars) Dlgbox.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Dlgbox.exe: Dlgbox.obj Dlgbox.res
    $(link) $(linkdebug) $(guiflags) -out:Dlgbox.exe Dlgbox.obj Dlgbox.res $(guilibs) advapi.lib
