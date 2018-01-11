# Nmake macros for building Windows 32-Bit apps

all: Two_Ic~1.exe

# Update the resource if necessary

Two_Ic~1.res: Two_Ic~1.rc Two_Ic~1.h
    rc -r -fo Two_Ic~1.res Two_Ic~1.rc

# Update the object file if necessary

Two_Ic~1.obj: Two_Ic~1.cpp Two_Ic~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Two_Ic~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Two_Ic~1.exe: Two_Ic~1.obj Two_Ic~1.res
    $(link) $(linkdebug) $(guiflags) -out:Two_Ic~1.exe Two_Ic~1.obj Two_Ic~1.res $(guilibs) advapi.lib
