#!/bin/sh
if [ $# -lt 1 ]; then
echo "Please enter '$0 deploy_root'"
exit 1
fi

SIGNING_KEY_STORE=pictoword_all.keystore
SIGNING_KEY_ALIAS=hortorpictoword_all
SIGNING_STORE_PASSWORD=hortor
SIGNING_KEY_PASSWORD=hortor

DEPLOY_ROOT="$1"

BUNDLE_IDENTIFIER=$(grep  'package' AndroidManifest_template.xml | /usr/local/bin/gawk '{if(match($0,/package="([^"]+)"/,m)) print m[1];}')
BUNDLE_VERSION=$(grep  'android:versionName' AndroidManifest_template.xml | /usr/local/bin/gawk '{if(match($0,/android:versionName="([^"]+)"/,m)) print m[1];}')

echo "BUNDLE_IDENTIFIER = ${BUNDLE_IDENTIFIER}"
echo "BUNDLE_VERSION = ${BUNDLE_VERSION}"

if [ "$ENV_NAME" == "DEBUG" ]; then
    APK_FILENAME=pictoword-debug.apk
else
    APK_FILENAME=pictoword-release.apk
fi

DEPLOY_PARENT=build/$DEPLOY_ROOT/$BUNDLE_IDENTIFIER

if [ -e "$DEPLOY_PARENT/build_version" ]; then
    BUILD_VERSION=`cat "$DEPLOY_PARENT/build_version"`
    BUILD_VERSION=`expr $BUILD_VERSION + 1`
else
    BUILD_VERSION=1
fi


APP_MANIFEST=AndroidManifest.xml

DEPLOY_PATH=$DEPLOY_PARENT/${BUNDLE_VERSION}-build${BUILD_VERSION}

sh build_native.sh
if [[ $? != 0 ]] ; then
    exit $?
fi

if [ "$APP_MANIFEST" ]; then
    ANT_ADD_OPTS="-Dmanifest.file=$APP_MANIFEST"
else
    ANT_ADD_OPTS=
fi

if [ "$ENV_NAME" == "DEBUG" ]; then
    DEBUG_OPTS=debug
else
    DEBUG_OPTS=release
    ANT_ADD_KEY_STORE="-Dkey.store=$SIGNING_KEY_STORE"
    ANT_ADD_KEY_ALIAS="-Dkey.alias=$SIGNING_KEY_ALIAS"
    ANT_ADD_STORE_PASSWORD="-Dkey.store.password=$SIGNING_STORE_PASSWORD"
    ANT_ADD_KEY_PASSWORD="-Dkey.alias.password=$SIGNING_KEY_PASSWORD"
fi

for chanel in $@
do
    awk '{gsub(/android:value="Umeng"/,"android:value=\"'"$chanel"'\"",$0);print $0}' AndroidManifest_template.xml>AndroidManifest.xml
    echo "ant clean $DEBUG_OPTS $ANT_ADD_OPTS $ANT_ADD_KEY_STORE $ANT_ADD_KEY_ALIAS $ANT_ADD_STORE_PASSWORD $ANT_ADD_KEY_PASSWORD"
    if !(ant clean $DEBUG_OPTS $ANT_ADD_OPTS "$ANT_ADD_KEY_STORE" "$ANT_ADD_KEY_ALIAS" "$ANT_ADD_STORE_PASSWORD" "$ANT_ADD_KEY_PASSWORD"); then
        echo "Error(s) occred in processing"
        exit 1
    fi

    if [ ! -f "bin/$APK_FILENAME" ]; then
        echo "Unable to found apk result: bin/$APK_FILENAME"
        exit 1
    fi

    mkdir -p $DEPLOY_PATH
    mv bin/$APK_FILENAME $DEPLOY_PATH/${BUNDLE_IDENTIFIER}-${chanel}.apk

done

/bin/echo -n $BUILD_VERSION >$DEPLOY_PARENT/build_version

adb install -r $DEPLOY_PATH/${BUNDLE_IDENTIFIER}-${chanel}.apk

echo "Find your apk at http://192.168.1.149/download/$BUNDLE_IDENTIFIER/${BUNDLE_VERSION}-build${BUILD_VERSION}/"

