#!/bin/bash

VERSION="embroidermodder2.0.0-alpha"

set -e

if [ "$1" = "Ubuntu" ]; then

    sudo apt-get update
    sudo apt-get install git build-essential cmake qt6-base-dev qml-qt6 libqt6widgets6 \
        libqt6printsupport6 libqt6core6 libgl-dev libgl1-mesa-dev libglx-dev \
        libsdl3-dev libsdl3-image-dev libsdl3-ttf-dev

elif [ "$1" = "MacOS" ]; then

    brew install qt6 sdl3 sdl3_image sdl3_ttf

elif [ "$1" = "Windows" ]; then

    QT_VERSION="6.5.0"

    python -m pip install -U pip --upgrade pip
    pip install aqtinstall
    python -m aqt install-qt windows desktop "${QT_VERSION}" win64_mingw

    QT_DIR="`pwd`/${QT_VERSION}/mingw_64"
    export PATH="${QT_DIR}/bin:${PATH}"
    export CMAKE_PREFIX_PATH="${QT_PATH}"

fi

mkdir build
cd build
cmake ..
cmake --build .

mkdir "${VERSION}"

if [ "$1" = "Ubuntu" ]; then
mv embroidermodder2 LICENSE.md help icons images samples \
    translations "${VERSION}"
tar -czf "${VERSION}-linux.tar.gz" "${VERSION}"
elif [ "$1" = "MacOS" ]; then
cpack
elif [ "$1" = "Windows" ]; then
cpack
fi

cd ..
