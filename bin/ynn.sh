#!/bin/bash
#Program:
#	This prtgram shows the user's choice
#History:
#2016/07/19	VBird First release




read -p "Please input (Y/N):" yn
[ "${yn}" == "Y" -o "${yn}" == "y" ] && echo "OK, continue" && exit 0
[ "${yn}" == "N" -o "${yn}" == "n" ] && echo "Oh, interrupt!" && exit 0
echo "I don't know what you choice is" && exit 0
