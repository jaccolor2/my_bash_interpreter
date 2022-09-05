#!/usr/bin/env bash

git add --all

function a() {
    git commit -m $1
    #git tag -a exercises-$1-tag23 -m $1
    git push --follow-tags
}

a $@