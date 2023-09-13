#!/bin/bash

PATH="$PATH:$HOME/opt/bin/"

### check tool exists
if ! cmake --version 2>&1; then
	echo "Update \$PATH?"
	exit 1
fi

### options
EXTRA=""
if [[ $# > 0 ]]; then
	if [[ $1 == "--run" ]]; then
		EXTRA="$EXTRA --target run_game"
	else
		echo "usage: $0 [--run]"
		exit 2
	fi
fi

## run
cmake -DCMAKE_TOOLCHAIN_FILE=./mingw-w64-x86_64.cmake -DMOD_ID=Hydration -DAUTO_COPY_MOD=ON -DAUTO_COPY_MOD_HAMMERSTONE=ON -DSAPIENS_MOD_DIRECTORY="/media/dyfract/Big Media/Games/SteamLibrary/steamapps/compatdata/1060230/pfx/drive_c/users/steamuser/AppData/Roaming/majicjungle/sapiens/mods/" . -B build
cmake --build build/ --target sync_mod_files $EXTRA
