#!/bin/bash
adb shell am force-stop com.beatgames.beatsaber
adb shell am start -n com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity
echo "Clearing logcat buffer."
adb logcat -c
echo "Cleared logcat buffer.."
echo "Starting logcat to log.log..."
adb logcat > .\log.log