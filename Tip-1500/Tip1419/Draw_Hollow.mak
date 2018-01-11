# Nmake macros for building Windows 32-Bit apps

all: Draw_H~1.exe

# Update the resource if necessary

Draw_H~1.res: Draw_H~1.rc Draw_H~1.h
    rc -r -fo Draw_H~1.res Draw_H~1.rc

# Update the object file if necessary

Draw_H~1.obj: Draw_H~1.cpp Draw_H~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Draw_H~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Draw_H~1.exe: Draw_H~1.obj Draw_H~1.res
    $(link) $(linkdebug) $(guiflags) -out:Draw_H~1.exe Draw_H~1.obj Draw_H~1.res $(guilibs) advapi.lib
