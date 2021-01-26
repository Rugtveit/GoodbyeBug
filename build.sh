#!/bin/bash
NDKPath="$(cat ndkpath.txt)"
buildScript="$NDKPath/build/ndk-build"
$buildScript NDK_PROJECT_PATH=. APP_BUILD_SCRIPT="$(pwd)/Android.mk" NDK_APPLICATION_MK="$(pwd)/Application.mk"