# Nmake macros for building Windows 32-Bit apps

all: Conver~1.exe

# Update the resource if necessary

Conver~1.res: Conver~1.rc Conver~1.h
    rc -r -fo Conver~1.res Conver~1.rc

# Update the object file if necessary

Conver~1.obj: Conver~1.cpp Conver~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Conver~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Conver~1.exe: Conver~1.obj Conver~1.res
    $(link) $(linkdebug) $(guiflags) -out:Conver~1.exe Conver~1.obj Conver~1.res $(guilibs) advapi.lib
