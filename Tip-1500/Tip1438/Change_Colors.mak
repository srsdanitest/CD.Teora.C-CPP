# Nmake macros for building Windows 32-Bit apps

all: Change_1.exe

# Update the resource if necessary

Change_1.res: Change_1.rc Change_1.h
    rc -r -fo Change_1.res Change_1.rc

# Update the object file if necessary

Change_1.obj: Change_1.cpp Change_1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Change_1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Change_1.exe: Change_1.obj Change_1.res
    $(link) $(linkdebug) $(guiflags) -out:Change_1.exe Change_1.obj Change_1.res $(guilibs) advapi.lib
