#!/bin/bash

set -x # echo on
set -e # exit on error

cmake --test .
