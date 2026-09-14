#!/bin/bash

if [ -z "$1" ]; then
    target="scripts/test.nue"
else
    target="$1"
fi

./obj/NextUnitEngine "$target"
