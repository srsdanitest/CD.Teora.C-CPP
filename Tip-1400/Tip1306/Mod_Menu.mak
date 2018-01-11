# Nmake macros for building Windows 32-Bit apps

all: Mod_Menu.exe

# Update the resource if necessary

Mod_Menu.res: Mod_Menu.rc Mod_Menu.h
    rc -r -fo Mod_Menu.res Mod_Menu.rc

# Update the object file if necessary

Mod_Menu.obj: Mod_Menu.cpp Mod_Menu.h
    $(cc) $(cdebug) $(cflags) $(cvars) Mod_Menu.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Mod_Menu.exe: Mod_Menu.obj Mod_Menu.res
    $(link) $(linkdebug) $(guiflags) -out:Mod_Menu.exe Mod_Menu.obj Mod_Menu.res $(guilibs) advapi.lib
