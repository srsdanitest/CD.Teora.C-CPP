# Nmake macros for building Windows 32-Bit apps

all: CrossH~1.exe

# Update the resource if necessary

CrossH~1.res: CrossH~1.rc CrossH~1.h
    rc -r -fo CrossH~1.res CrossH~1.rc

# Update the object file if necessary

CrossH~1.obj: CrossH~1.cpp CrossH~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) CrossH~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

CrossH~1.exe: CrossH~1.obj CrossH~1.res
    $(link) $(linkdebug) $(guiflags) -out:CrossH~1.exe CrossH~1.obj CrossH~1.res $(guilibs) advapi.lib
