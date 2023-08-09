#!/bin/bash
first_param=$1
xmake build -v $first_param
xmake r $first_param