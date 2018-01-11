# Nmake macros for building Windows 32-Bit apps

all: 2_menus.exe

# Update the resource if necessary

2_menus.res: 2_menus.rc 2_menus.h
    rc -r -fo 2_menus.res 2_menus.rc

# Update the object file if necessary

2_menus.obj: 2_menus.cpp 2_menus.h
    $(cc) $(cdebug) $(cflags) $(cvars) 2_menus.cpp

# Update the executable file if necessary, and if so, add the resource back in.

2_menus.exe: 2_menus.obj 2_menus.res
    $(link) $(linkdebug) $(guiflags) -out:2_menus.exe 2_menus.obj 2_menus.res $(guilibs) advapi.lib
