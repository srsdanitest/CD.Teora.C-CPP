# Nmake macros for building Windows 32-Bit apps

all: GetThr~1.exe

# Update the resource if necessary

generic.res:generic.rc generic.h
    rc -r -fo generic.res generic.rc

# Update the object file if necessary

GetThr~1.obj: GetThr~1.cpp generic.cpp generic.h
    $(cc) $(cdebug) $(cflags) $(cvars) GetThr~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

GetThr~1.exe: GetThr~1.obj generic.res
    $(link) $(linkdebug) $(guiflags) -out:GetThr~1.exe GetThr~1.obj generic.res $(guilibs) advapi.lib
