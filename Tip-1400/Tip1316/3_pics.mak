# Nmake macros for building Windows 32-Bit apps

all: 3_pics.exe

# Update the resource if necessary

show_~1.res: 3_pics.rc 3_pics.h
    rc -r -fo 3_pics.res 3_pics.rc

# Update the object file if necessary

3_pics.obj: 3_pics.cpp 3_pics.h
    $(cc) $(cdebug) $(cflags) $(cvars) 3_pics.cpp

# Update the executable file if necessary, and if so, add the resource back in.

3_pics.exe: 3_pics.obj 3_pics.res
    $(link) $(linkdebug) $(guiflags) -out:3_pics.exe 3_pics.obj 3_pics.res $(guilibs) advapi.lib
