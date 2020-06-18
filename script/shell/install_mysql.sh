#!/bin/bash

usage="\
install mysql by this script, and after that set password.

-v, --version=name special the version of mysql to install.
-p, --password=name special the password after install.
-e, --enable whether start mysql on system boot, default no."

function install_mysql() {
    # install mysql repo
    rpm -Uvh "${rpm_url}"

    if [[ "${MYSQL_VERSION}" = "57" ]]; then
        yum --enablerepo=mysql57-community --disablerepo=mysql80-community insatll mysql-community-server
    else
        yum --enablerepo=mysql80-community --disablerepo=mysql57-community insatll mysql-community-server
    fi

    return $?
}

function set_mysql() {
    # 开机启动设置
    if [[ "${MYSQL_ONBOOT}" = "yes" ]]; then
        if [[ "${release}" =~ el6.x86_64 ]] # CentOS6
        then
            chkconfig mysqld on
        elif [[ "${release}" =~ el7.x86_64 ]] # CentOS7
        then
            systemctl enable mysqld
        fi
    fi

    # start mysqld, then set password
    if [[ "${release}" =~ el6.x86_64 ]] # CentOS6
    then
        service mysqld start
        sleep 2

        /usr/bin/mysqladmin -u root password '${MYSQL_PW}'
        mysql -u root -p"${MYSQL_PW}" -e "GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY '${MYSQL_PW}' WITH GRANT OPTION;"
        # mysql -u root -p${MYSQL_PW} -e "CREATE DATABASE androidscanner;"
        # mysql -u root -p${MYSQL_PW} androidscanner < ./androidscanner-need.sql
    elif [[ "${release}" =~ el7.x86_64 ]] # CentOS7
    then
        systemctl start mysqld
        sleep 2

        # 没有这个文件或者密码错误,rm -rvf  /var/lib/mysql,然后systemctl restart mysqld
        temp_pw=$(grep 'temporary password' /var/log/mysqld.log | awk '{print $NF}' | tail -1)
        mysql -uroot -p"$temp_pw" --connect-expired-password << EOF
set global validate_password.policy=LOW;
set global validate_password.length=1;
ALTER USER "root"@"localhost" IDENTIFIED  BY "${MYSQL_PW}";
use mysql;
update user set host= '%' where user = 'root';
#update user set plugin='mysql_native_password' where user ='root';
flush privileges;
EOF
    fi
}

release=$(uname -r)
if [[ "${release}" =~ el6.x86_64 ]] # CentOS6
then
    rpm_url=https://repo.mysql.com/mysql80-community-release-el6.rpm
elif [[ "${release}" =~ el7.x86_64 ]] # CentOS7
then
    rpm_url=https://repo.mysql.com/mysql80-community-release-el7.rpm
else
    echo "this script only works on centos6 and centos7"
    exit 1
fi

# 默认密码
MYSQL_PW=golden
# 默认版本
MYSQL_VERSION=80
# 默认不开启开机启动
MYSQL_ONBOOT=no

TEMP=$(getopt -o hp:v:e --long help,password:,version:,enable -n 'install_mysql' -- "$@")
if [ $? != 0 ]; then exit 1; fi
eval set -- "$TEMP"

while true
do
    case "$1" in
        -h|--help)
            echo $usage
            exit 0
            ;;
        -v|--version)
            case "$2" in
                "80"|"57") MYSQL_VERSION=$2; shift 2 ;;
                *) echo "this script on support install mysql5.7 and mysql8.0" >&2; exit 1; shift 2 ;;
            esac
            # case "$2" in
                # ""|"57") MYSQL_VERSION=57; shift 2 ;;
                # "80") MYSQL_VERSION=80; shift 2 ;;
                # *) echo "this script on support install mysql5.7 and mysql8.0" >&2; exit 1; shift 2 ;;
            # esac
            ;;
        -p|--password)
            MYSQL_PW="$2"
            shift 2
            ;;
        -e|--enable)
            MYSQL_ONBOOT=yes
            shift
            ;;
        --) shift; break;;
        *) echo "internal error"; exit 1;;
    esac
done

if rpm -qa | grep -q mysql-community-server; then
    echo "You have already install mysql-community-server"
    echo "Please remove mysql-community-server, then install mysql by this script"
    exit 1
fi

install_mysql && set_mysql