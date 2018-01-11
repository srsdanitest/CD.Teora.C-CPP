# Nmake macros for building Windows 32-Bit apps

!include <ntwin32.mak>

all: client.exe

# Update the resource if necessary

client.res: client.rc client.h
    rc -r -fo client.res client.rc

# Update the object file if necessary

client.obj: client.c client.h
    $(cc) $(cdebug) $(cflags) $(cvars) client.c

# Update the executable file if necessary, and if so, add the resource back in.

client.exe: client.obj client.res
    $(link) $(linkdebug) $(guiflags) -out:client.exe client.obj client.res $(guilibs)
