# Nmake macros for building Windows 32-Bit apps

all: List_Dir.exe

# Update the resource if necessary

List_Dir.res: List_Dir.rc List_Dir.h
    rc -r -fo List_Dir.res List_Dir.rc

# Update the object file if necessary

List_Dir.obj: List_Dir.cpp List_Dir.h
    $(cc) $(cdebug) $(cflags) $(cvars) List_Dir.cpp

# Update the executable file if necessary, and if so, add the resource back in.

List_Dir.exe: List_Dir.obj List_Dir.res
    $(link) $(linkdebug) $(guiflags) -out:List_Dir.exe List_Dir.obj List_Dir.res $(guilibs) advapi.lib
