# Nmake macros for building Windows 32-Bit apps

all: Show_t~1.exe

# Update the resource if necessary

Show_t~1.res: Show_t~1.rc Show_t~1.h
    rc -r -fo Show_t~1.res Show_t~1.rc

# Update the object file if necessary

Show_t~1.obj: Show_t~1.cpp Show_t~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Show_t~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Show_t~1.exe: Show_t~1.obj Show_t~1.res
    $(link) $(linkdebug) $(guiflags) -out:Show_t~1.exe Show_t~1.obj Show_t~1.res $(guilibs) advapi.lib
