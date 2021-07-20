#!/usr/bin/env bash

set -e

# Locate shell script path
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

# use tar tools
. ../../tools/tar_process.sh

# Download and install Maven
if [ ! -n "${VERSION}" ]; then
    VERSION="3.6.3"
fi

MAVEN_VERSION="apache-maven-${VERSION}"
MAVEN_PACKAGE="${MAVEN_VERSION}-bin.tar.gz"

# https://mirrors.aliyun.com/apache/maven/maven-3
MAVEN_MIRROR_URL="http://mirrors.tuna.tsinghua.edu.cn/apache/maven/maven-3"
wget ${MAVEN_MIRROR_URL}/${VERSION}/binaries/${MAVEN_PACKAGE}

tar_decompress ${MAVEN_PACKAGE} /opt

chown -R root:root /opt/${MAVEN_VERSION}

ln -s /opt/${MAVEN_VERSION} /opt/apache-maven

# Use Aliyun Maven Repo
command cp ${SCRIPT_DIR}/settings.xml /opt/${MAVEN_VERSION}/conf/

# Set PATH system variable
cat > /etc/profile.d/maven.sh <<EOF
export M2_HOME=/opt/apache-maven
export PATH=\$PATH:\$M2_HOME/bin
EOF

source /etc/profile.d/maven.sh


# Check Maven
mvn -version
