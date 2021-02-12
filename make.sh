#!/bin/bash
curPath=$(cd `dirname $BASH_SOURCE`;pwd)
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
    local localBuildDir="${curPath}/localBuild"
    if [[ "$1" =~ ^ems(scripten)? ]]
    then
        echo "em"
        emscripten=1
    elif [ "$1" = "local" ]
    then
        localPlatform=1
    elif [ "$1" = 'clean' ]
    then
        rm -rvf "$emscriptenBuildDir"
        rm -rvf "$localBuildDir"
    else
        echo "all"
        emscripten=1
        localPlatform=1
    fi

    if [ "$emscripten"  = "1" ]
    then
        checkCmds emcmake emmake emcc || return -1
        createDirectoryIfNotExists "$emscriptenBuildDir"
        pushd "$emscriptenBuildDir"
        emcmake cmake .. || return -1
        emmake make  || return -1
        emcc libthree.a -o three.js || return -1
        popd
    fi
    if [ "$localPlatform" = "1" ]
    then
        checkCmds cmake make || return -1
        createDirectoryIfNotExists "$localBuildDir"
        pushd "$localBuildDir"
        cmake .. || return -1
        make  || return -1
        popd
    fi
}

main $*