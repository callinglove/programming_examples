#!/bin/bash
set -e

echo -e "\e[032mWhere would you like to install jdk(for example: /usr/lib/jvm):\e[0m"
read -t 10 input
jdkPath=${input:-/usr/lib/jvm}
if [ ! -d $jdkPath ]
then
    mkdir $jdkPath
fi
curl -OLC - -H "Cookie: oraclelicense=accept-securebackup-cookie"  -H "Connection: keep-alive" 'http://download.oracle.com/otn-pub/java/jdk/8u121-b13/e9e7ea248e2c4826b92b3f075a80e441/jdk-8u121-linux-x64.tar.gz'
wget --no-check-certificate -c --header "Cookie: oraclelicense=accept-securebackup-cookie" http://download.oracle.com/otn-pub/java/jdk/8u121-b13/e9e7ea248e2c4826b92b3f075a80e441/jdk-8u121-linux-x64.tar.gz -O jdk-8u121-linux-x64.tar.gz

tar -xzvf jdk-8u121-linux-x64.tar.gz -C $jdkPath

cat >> /etc/profile << EOF
export JAVA_HOME=$jdkPath/jdk1.8.0_121
export PATH=\$JAVA_HOME/bin:\$PATH
export CLASSPATH=.:\$JAVA_HOME/lib/dt.jar:\$JAVA_HOME/lib/tools.jar
EOF
