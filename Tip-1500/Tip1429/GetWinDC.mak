# Nmake macros for building Windows 32-Bit apps

all: GetWinDC.exe

# Update the resource if necessary

GetWinDC.res: GetWinDC.rc GetWinDC.h
    rc -r -fo GetWinDC.res GetWinDC.rc

# Update the object file if necessary

GetWinDC.obj: GetWinDC.cpp GetWinDC.h
    $(cc) $(cdebug) $(cflags) $(cvars) GetWinDC.cpp

# Update the executable file if necessary, and if so, add the resource back in.

GetWinDC.exe: GetWinDC.obj GetWinDC.res
    $(link) $(linkdebug) $(guiflags) -out:GetWinDC.exe GetWinDC.obj GetWinDC.res $(guilibs) advapi.lib
