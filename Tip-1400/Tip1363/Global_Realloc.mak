# Nmake macros for building Windows 32-Bit apps

all: Global~1.exe

# Update the resource if necessary

Global~1.res: Global~1.rc Global~1.h
    rc -r -fo Global~1.res Global~1.rc

# Update the object file if necessary

Global~1.obj: Global~1.cpp Global~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Global~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Global~1.exe: Global~1.obj Global~1.res
    $(link) $(linkdebug) $(guiflags) -out:Global~1.exe Global~1.obj Global~1.res $(guilibs) advapi.lib
