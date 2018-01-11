# Nmake macros for building Windows 32-Bit apps

all: EnumResT.exe

# Update the resource if necessary

EnumResT.res: EnumResT.rc EnumResT.h
    rc -r -fo EnumResT.res EnumResT.rc

# Update the object file if necessary

EnumResT.obj: EnumResT.cpp EnumResT.h
    $(cc) $(cdebug) $(cflags) $(cvars) EnumResT.cpp

# Update the executable file if necessary, and if so, add the resource back in.

EnumResT.exe: EnumResT.obj EnumResT.res
    $(link) $(linkdebug) $(guiflags) -out:EnumResT.exe EnumResT.obj EnumResT.res $(guilibs) advapi.lib
