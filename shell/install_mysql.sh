#!/bin/bash

function install_mysql {
    yum -y remove mysql mysql-* > /dev/null 2>&1
    rpm -qa | grep mysql-community-release > /dev/null 2>&1 || rpm -Uvh http://repo.mysql.com/mysql-community-release-el6-5.noarch.rpm
    yum -d 1 -y install mysql-community-server
    yum -d 1 -y install mysql-community-devel

    service mysqld start
    chkconfig mysqld on
    /usr/bin/mysqladmin -u root password 'szdhp1211'
    mysql -u root -pszdhp1211 -e "GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY 'szdhp1211' WITH GRANT OPTION;"
    mysql -u root -pszdhp1211 -e "CREATE DATABASE androidscanner;"
    mysql -u root -pszdhp1211 androidscanner < ./androidscanner-need.sql
}

install_mysql

