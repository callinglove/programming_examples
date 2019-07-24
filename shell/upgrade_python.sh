#!/bin/bash

# up python to 2.7.11 for CentOS6.5

FILE_DIR=$(cd "$(dirname "$0")"; pwd)

function upgrade_python {
    yum -y install wget xz 
    yum -y install gcc gcc-c++
    yum -y install make automake autoconf
    
    yum -y install bzip2 bzip2-devel bzip2-libs zlib-devel
    yum -y install openssl openssl-devel
    yum -y install bind-utils
    
    [ -e Python-2.7.11.tar.xz ] || wget https://www.python.org/ftp/python/2.7.11/Python-2.7.11.tar.xz

    xz -k -d Python-2.7.11.tar.xz
    tar xvf Python-2.7.11.tar
    cd Python-2.7.11
    ./configure --enable-shared
    make
    make install
    cd "${FILE_DIR}"

    echo "/usr/local/lib" > /etc/ld.so.conf.d/python2.7.conf
    ldconfig
    sed -i '1s/python$/python2.6/' /usr/bin/yum

    wget https://bootstrap.pypa.io/get-pip.py -O - | python

    mv /usr/bin/python{,_bk}
    ln -s /usr/local/bin/python /usr/bin/python
}

upgrade_python
