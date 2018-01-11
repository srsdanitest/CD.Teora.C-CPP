# Nmake macros for building Windows 32-Bit apps

all: Enum_A~1.exe

# Update the resource if necessary

Enum_A~1.res: Enum_A~1.rc Enum_A~1.h
    rc -r -fo Enum_A~1.res Enum_A~1.rc

# Update the object file if necessary

Enum_A~1.obj: Enum_A~1.cpp Enum_A~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Enum_A~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Enum_A~1.exe: Enum_A~1.obj Enum_A~1.res
    $(link) $(linkdebug) $(guiflags) -out:Enum_A~1.exe Enum_A~1.obj Enum_A~1.res $(guilibs) advapi.lib
