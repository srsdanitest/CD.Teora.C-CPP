# Nmake macros for building Windows 32-Bit apps

all: Enab_Dis.exe

# Update the resource if necessary

Enab_Dis.res: Enab_Dis.rc Enab_Dis.h
    rc -r -fo Enab_Dis.res Enab_Dis.rc

# Update the object file if necessary

Enab_Dis.obj: Enab_Dis.cpp Enab_Dis.h
    $(cc) $(cdebug) $(cflags) $(cvars) Enab_Dis.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Enab_Dis.exe: Enab_Dis.obj Enab_Dis.res
    $(link) $(linkdebug) $(guiflags) -out:Enab_Dis.exe Enab_Dis.obj Enab_Dis.res $(guilibs) advapi.lib
