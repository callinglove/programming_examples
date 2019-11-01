#!/bin/bash
#
# install jar on local mvn respository

MVN=$(which mvn 2>/dev/null)
if [[ -z "${MVN}" && -n "${M2_HOME}" && -x "${M2_HOME}/bin/mvn" ]]; then
    MVN="${M2_HOME}/bin/mvn"
elif [[ -z "${MVN}" && -n "${MAVEN_HOME}" && -x "${MAVEN_HOME}/bin/mvn" ]]; then
    MVN="${MAVEN_HOME}/bin/mvn"
elif [[ -z "${MVN}" && -x "/opt/apache-maven-3.6.1/bin/mvn" ]]; then
    MVN=/opt/apache-maven-3.6.1/bin/mvn
elif [[ -z "${MVN}" ]]; then
    echo "cannot find mvn, exit!!" >&2
    exit 1
fi

function install_jar() {
    local tar_file=$1
    local version groupId artifactId
    TEMPFILE=$(mktemp -d -t ins_jar.XXXXXX)
    unzip "${tar_file}" -d "${TEMPFILE}" > /dev/null
    local POMFILE=$(find "${TEMPFILE}/META-INF" -name "pom.properties")
    if [ -z "${POMFILE}" ]; then
        version=$(basename "${tar_file}" | grep -oP "(?<=-)\d.*(?=.jar)")
        local CURPATH=${TEMPFILE}
        while true
        do
            child=($(ls "${CURPATH}" | grep -v 'META-INF'))
            if [ $? -ne 0 ]; then
                break
            fi
            if [ ${#child[@]} -ne 1 ]; then
                break
            fi
            field=${child[0]}
            if [ -z "${groupId}" ]; then
                groupId=${field}
            else
                groupId=${groupId}.${field}
            fi
            artifactId=${field}
            CURPATH=${CURPATH}/${field}
        done
    else
        POMFILE=${TEMPFILE}/META-INF/${POMFILE}
        version=$(awk -F"=" /version/ '{print $2}')
        groupId=$(awk -F"=" /groupId/ '{print $2}')
        artifactId=$(awk -F"=" /artifactId/ '{print $2}')
    fi

    echo "${MVN} install:install-file -Dfile=${tar_file} -DgroupId=${groupId} -DartifactId=${artifactId} -Dversion=${version} -Dpackaging=jar"
    ${MVN} install:install-file -Dfile="${tar_file}" -DgroupId="${groupId}" -DartifactId="${artifactId}" -Dversion="${version}" -Dpackaging=jar

    rm -rf "${TEMPFILE}"
    
    return 0
}

until [[ $# -eq 0 ]]
do
install_jar "$1"
shift
done
