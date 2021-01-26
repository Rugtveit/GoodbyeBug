#!/bin/bash
NDKPath="$(cat ndkpath.txt)"
ModID="$(cat modid.txt)"
buildScript="$NDKPath/build/ndk-build"
$buildScript NDK_PROJECT_PATH=. APP_BUILD_SCRIPT="$(pwd)/Android.mk" NDK_APPLICATION_MK="$(pwd)/Application.mk"
adb push "libs/arm64-v8a/$ModID.so" "/sdcard/Android/data/com.beatgames.beatsaber/files/mods/$ModID.so"
adb shell am force-stop com.beatgames.beatsaber
adb shell am start -n com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity