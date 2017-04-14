#!/bin/bash
# boundle relevant boost part

test -e "include" || mkdir "include"
bcp --boost=/usr/include asio include
