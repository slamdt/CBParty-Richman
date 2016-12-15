#!/bin/sh

sh build_native.sh
ant release
#nice -r.be able to install without uninstalling before.
adb install -r bin/DoTaBattle-release.apk