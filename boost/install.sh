#!/bin/bash

test -e "include" || mkdir "include"
bcp --boost=/usr/include asio include
