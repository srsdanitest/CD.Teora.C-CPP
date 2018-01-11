# Nmake macros for building Windows 32-Bit apps

all: Check_~1.exe

# Update the resource if necessary

Check_~1.res: Check_~1.rc Check_~1.h
    rc -r -fo Check_~1.res Check_~1.rc

# Update the object file if necessary

Check_~1.obj: Check_~1.cpp Check_~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Check_~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Check_~1.exe: Check_~1.obj Check_~1.res
    $(link) $(linkdebug) $(guiflags) -out:Check_~1.exe Check_~1.obj Check_~1.res $(guilibs) advapi.lib
