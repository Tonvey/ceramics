#!/bin/bash
curPath=$(cd `dirname $BASH_SOURCE`;pwd)
# getopt

function usage
{
    cat >&2 <<EOF
usage : $0 [options]
      -p <emspcripten|local> specify plantform.
      -t <debug|release> specify build type.
      -c clean build directory.
      -h Show this usage.
EOF
}

function cout
{
    echo $*
}
function cerr
{
    echo $* >&2
}
function checkCmd
{
    if [ $# -eq 0 ] 
    then
        cerr 'checkCmd no args'
        return -1
    fi
    which "$1" > /dev/null 2>&1
}
function createDirectoryIfNotExists
{
    local dir="$1"
    if [ ! -d "$dir" ]
    then
        mkdir -p "$dir"
    fi
    return 0
}
function checkCmds
{
    local flag=0
    while [ $# -ne 0 ] 
    do
        checkCmd "$1"
        if [ $? -ne 0 ]
        then
            cerr "command not found : " "$1"
            flag=-1
        fi
        shift
    done
    return $flag
}

function main
{
    local localPlatform=0
    local emscripten=0
    local emscriptenBuildDir="${curPath}/emBuild"
    local buildType="Release"
    local clean=0
    local localBuildDir="${curPath}/localBuild"
    while getopts p:t:c opt
    do
        case "$opt" in 
            p)
                if [ "$OPTARG" = "local" ] 
                then
                    localPlatform=1
                fi
                if [[ "$1" =~ ^ems(scripten)? ]]
                then
                    emscripten=1
                fi
                ;;
            t)
                buildType="$OPTARG"
                ;;
            c)
                clean=1
                ;;
            *)
                usage
                exit -1
                ;;
        esac
    done || exit -1
    if [ "$clean" = 1 ]
    then
        rm -rvf "$emscriptenBuildDir"
        rm -rvf "$localBuildDir"
    fi

    if [ "$localPlatform" = 0 -a "$emscripten" = 0 ]
    then
        localPlatform=1
        emscripten=1
    fi

    if [ "$emscripten"  = "1" ]
    then
        checkCmds emcmake emmake emcc || return -1
        createDirectoryIfNotExists "$emscriptenBuildDir"
        pushd "$emscriptenBuildDir"
        emcmake cmake -DCMAKE_BUILD_TYPE="$buildType" .. || return -1
        emmake make  || return -1
        emcc libceramics.a -o ceramics.js || return -1
        popd
    fi
    if [ "$localPlatform" = "1" ]
    then
        checkCmds cmake make || return -1
        createDirectoryIfNotExists "$localBuildDir"
        pushd "$localBuildDir"
        cmake -DCMAKE_BUILD_TYPE="$buildType" .. || return -1
        make  || return -1
        popd
    fi
}

main $*
