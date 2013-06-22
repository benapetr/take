#!/bin/sh

echo "Building"
make || exit 1
echo "Copying produced release to output folder"

if [ ! -d installer/usr/local ];then
  mkdir installer/usr/local
fi


if [ ! -d installer/usr/local/bin ];then
  mkdir installer/usr/local/bin
fi

cp bin/Release/take installer/usr/local/bin/take
echo "Producing package"
fakeroot dpkg-deb --build installer take.deb
