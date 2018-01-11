# Nmake macros for building Windows 32-Bit apps

all: Draw_B~1.exe

# Update the resource if necessary

Draw_B~1.res: Draw_B~1.rc Draw_B~1.h
    rc -r -fo Draw_B~1.res Draw_B~1.rc

# Update the object file if necessary

Draw_B~1.obj: Draw_B~1.cpp Draw_B~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Draw_B~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Draw_B~1.exe: Draw_B~1.obj Draw_B~1.res
    $(link) $(linkdebug) $(guiflags) -out:Draw_B~1.exe Draw_B~1.obj Draw_B~1.res $(guilibs) advapi.lib
