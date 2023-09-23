clear
echo BUILDING WITH PREMAKE5
if tools/premake5 gmake2;
then
    echo COMPILING WITH GMAKE
    if make config=debug_windows needlemake;
    then
        echo RUNNING AT PROJECT ROOT
        proj/bin/debug-windows-x86_64/needlemake/needlemake.exe Status
    fi
fi
