# Nmake macros for building Windows 32-Bit apps

all: Displa~1.exe

# Update the resource if necessary

Displa~1.res: Displa~1.rc Displa~1.h
    rc -r -fo Displa~1.res Displa~1.rc

# Update the object file if necessary

Displa~1.obj: Displa~1.cpp Displa~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Displa~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Displa~1.exe: Displa~1.obj Displa~1.res
    $(link) $(linkdebug) $(guiflags) -out:Displa~1.exe Displa~1.obj Displa~1.res $(guilibs) advapi.lib
