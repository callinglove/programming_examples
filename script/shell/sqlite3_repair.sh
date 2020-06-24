#!/bin/bash 
#
#   修复sqlite3数据库
#
#   database disk image is malformed
#
usage="\
script to repair sqlite3 db.

    $0 old_db new_db
"

function repair_sqlite3_db() {
    local db_to_repair=$1
    local db_to_save=$2
    local tmp_sql_file=tmp.$$.sql
    if [[ -f "${db_to_save}" ]]
    then
        rm -rvf "${db_to_save}"
    fi

    if [[ "$(file ${db_to_repair})" =~ SQLite ]]
    then
        sqlite3 "${db_to_repair}" << EOF
.output ${tmp_sql_file}
.dump
.quit
EOF

        echo "${db_to_repair} has error info following:"        
        grep -P "/\*{4} ERROR: .* \*{5}/" "${tmp_sql_file}"
        sed -i 's/ROLLBACK;/COMMIT;/g' ${tmp_sql_file}
        sqlite3 "${db_to_save}" << EOF
.read ${tmp_sql_file}
.quit
EOF
        rm -rf ${tmp_sql_file}
    else
        echo "${db_to_repair} is not SQLite 3.x database"
    fi
}

if [[ $# -ne 2 ]]
then
    echo "${usage}"
else
    repair_sqlite3_db "$1" "$2"
fi
