#!/bin/bash -eux

# In this case everything is built in docker
if [[ "$CONF" == "linux-package-appimage" ]];
then
    exit 0
fi

# Install the deps
case "$TRAVIS_OS_NAME" in
  linux)
    sudo chmod -R a+rwx /opt

    wget -nv https://cmake.org/files/v3.13/cmake-3.13.3-Linux-x86_64.tar.gz -O cmake-linux.tgz &

    echo 'deb http://apt.llvm.org/trusty/ llvm-toolchain-trusty-7 main' | sudo tee /etc/apt/sources.list.d/llvm.list
    sudo apt-key adv --recv-keys --keyserver keyserver.ubuntu.com 1397BC53640DB551
    sudo apt-key adv --recv-keys --keyserver keyserver.ubuntu.com 15CF4D18AF4F7421

    sudo add-apt-repository --yes ppa:jonathonf/ffmpeg-3
    sudo add-apt-repository --yes ppa:ubuntu-toolchain-r/test
    sudo add-apt-repository --yes ppa:beineri/opt-qt596-trusty

    sudo apt-get update -qq
    sudo apt-get install -qq --force-yes \
        g++-8 binutils libasound-dev ninja-build \
        gcovr lcov qt59-meta-minimal qt59svg \
        qt59quickcontrols2 qt59websockets qt59serialport \
        qt59multimedia libgl1-mesa-dev \
        libavcodec-dev libavutil-dev libavfilter-dev libavformat-dev libswresample-dev \
        portaudio19-dev clang-7 lld-7 \
        libbluetooth-dev \
        libsdl2-dev libsdl2-2.0-0 libglu1-mesa-dev libglu1-mesa \
        qt59base qt59declarative qt59xmlpatterns libgles2-mesa-dev \
        libavahi-compat-libdnssd-dev

    wait wget || true

    tar xaf cmake-linux.tgz
    mv cmake-*-x86_64 cmake
  ;;
  osx)
    set +e

    brew update
    brew install gnu-tar xz

    SDK_ARCHIVE=homebrew-cache.txz
    wget -nv https://github.com/OSSIA/score-sdk/releases/download/sdk9/$SDK_ARCHIVE -O $SDK_ARCHIVE
    gtar xhaf $SDK_ARCHIVE --directory /usr/local/Cellar

    AUDIO_ARCHIVE=mac-audio-sdk.txz
    wget -nv https://github.com/OSSIA/score-sdk/releases/download/sdk10/$AUDIO_ARCHIVE -O $AUDIO_ARCHIVE
    sudo gtar xhaf $AUDIO_ARCHIVE --directory /opt/ossia-sdk

    brew unlink cmake
    brew link --force boost ninja qt5 cmake

    set -e
  ;;
esac
