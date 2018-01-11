# Nmake macros for building Windows 32-Bit apps

all: Draw_2~1.exe

# Update the resource if necessary

Draw_2~1.res: Draw_2~1.rc Draw_2~1.h
    rc -r -fo Draw_2~1.res Draw_2~1.rc

# Update the object file if necessary

Draw_2~1.obj: Draw_2~1.cpp Draw_2~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Draw_2~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Draw_2~1.exe: Draw_2~1.obj Draw_2~1.res
    $(link) $(linkdebug) $(guiflags) -out:Draw_2~1.exe Draw_2~1.obj Draw_2~1.res $(guilibs) advapi.lib
