# Nmake macros for building Windows 32-Bit apps

all: FindRes.exe

# Update the resource if necessary

show_~1.res: FindRes.rc FindRes.h
    rc -r -fo FindRes.res FindRes.rc

# Update the object file if necessary

FindRes.obj: FindRes.cpp FindRes.h
    $(cc) $(cdebug) $(cflags) $(cvars) FindRes.cpp

# Update the executable file if necessary, and if so, add the resource back in.

FindRes.exe: FindRes.obj FindRes.res
    $(link) $(linkdebug) $(guiflags) -out:FindRes.exe FindRes.obj FindRes.res $(guilibs) advapi.lib
