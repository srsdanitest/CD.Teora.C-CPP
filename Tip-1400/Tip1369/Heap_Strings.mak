# Nmake macros for building Windows 32-Bit apps

all: Heap_S~1.exe

# Update the resource if necessary

Heap_S~1.res: Heap_S~1.rc Heap_S~1.h
    rc -r -fo Heap_S~1.res Heap_S~1.rc

# Update the object file if necessary

Heap_S~1.obj: Heap_S~1.cpp Heap_S~1.h
    $(cc) $(cdebug) $(cflags) $(cvars) Heap_S~1.cpp

# Update the executable file if necessary, and if so, add the resource back in.

Heap_S~1.exe: Heap_S~1.obj Heap_S~1.res
    $(link) $(linkdebug) $(guiflags) -out:Heap_S~1.exe Heap_S~1.obj Heap_S~1.res $(guilibs) advapi.lib
