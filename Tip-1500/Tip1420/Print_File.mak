# Nmake macros for building Windows 32-Bit apps

all: Print_~1.exe

# Update the resource if necessary

Print_~1.res: Print_~1.rc Print_~1.h
    rc -r -fo Print_~1.res Print_~1.rc

# Update the object file if necessary

Print_~1.obj: Print_~1.cpp Print_~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Print_~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Print_~1.exe: Print_~1.obj Print_~1.res
    $(link) $(linkdebug) $(guiflags) -out:Print_~1.exe Print_~1.obj Print_~1.res $(guilibs) advapi.lib
