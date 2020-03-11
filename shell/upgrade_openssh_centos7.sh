#!/bin/bash

# up openssh to openssh-8.1p1 for CentOS7

FILE_DIR=$(cd "$(dirname "$0")"; pwd)
OPENSSH_FILE=openssh-8.1p1
OPENSSH_TAR=${OPENSSH_FILE}.tar.gz

function build_openssh_rpm {
    # 安装工具包与依赖库
    yum install -y gcc automake autoconf unzip
    yum install -y rpmdevtools rpm-build
    yum install -y zlib-devel openssl-devel perl-devel pam-devel

    if [ ! -e openssh-8.1p1.tar.gz ]
    then
        curl -o ${OPENSSH_TAR} https://cdn.openbsd.org/pub/OpenBSD/OpenSSH/portable/${OPENSSH_TAR}
    fi

    # 构建目录树
    rpmdev-setuptree

    # rpmbuild -D '%_topdir %(echo $PWD)' -ba SPECS/activemq.spec
    SPECS=$(rpm --eval "%{_specdir}")
    SOURCES=$(rpm --eval "%{_sourcedir}")

    cp ${OPENSSH_TAR} ${SOURCES}
    tar zxvf ${OPENSSH_TAR}  ${OPENSSH_FILE}/contrib/redhat/openssh.spec
    mv ${OPENSSH_FILE}/contrib/redhat/openssh.spec ${SPECS}
    chown sshd:sshd ${SPECS}/openssh.spec
    cp ${SPECS}/openssh.spec{,_def}

    # 配置spec文件
    sed -i -e "s/%define no_gnome_askpass 0/%define no_gnome_askpass 1/g" ${SPECS}/openssh.spec
    sed -i -e "s/%define no_x11_askpass 0/%define no_x11_askpass 1/g" ${SPECS}/openssh.spec
    # 注释掉 BuildRequires: openssl-devel < 1.1 因为目前安装的版本都低于1.1
    sed -i -e "s/BuildRequires: openssl-devel < 1.1/#BuildRequires: openssl-devel < 1.1/" ${SPECS}/openssh.spec

    rpmbuild -bb ${SPECS}/openssh.spec
}

function install_rpm() {
    # 备份这两个文件
    cp /etc/pam.d/sshd /tmp/
    cp /etc/ssh/sshd_config /tmp/

    rpm -Uvh $(rpm --eval "%{_rpmdir}")/$(uname -m)/{openssh-8.1p1-1.el7.centos.x86_64.rpm,openssh-clients-8.1p1-1.el7.centos.x86_64.rpm,openssh-server-8.1p1-1.el7.centos.x86_64.rpm}

    cat /tmp/sshd >  /etc/pam.d/sshd
    cat /tmp/sshd_config > /etc/ssh/sshd_config

    sed -i '/#UsePAM no/a\UsePAM yes' /etc/ssh/sshd_config
    chmod 0600 /etc/ssh/ssh_host_*key
}

build_openssh_rpm
