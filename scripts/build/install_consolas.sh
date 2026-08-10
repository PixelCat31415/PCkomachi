#!/usr/bin/env bash

set -e

mkdir -p /tmp/fonttemp
cd /tmp/fonttemp

wget https://web.archive.org/web/20171225132744/http://download.microsoft.com/download/E/6/7/E675FFFC-2A6D-4AB0-B3EB-27C9F8C8F696/PowerPointViewer.exe --no-check-certificate

cabextract -F ppviewer.cab PowerPointViewer.exe
cabextract -L -F "CONSOL*.TTF" ppviewer.cab

mkdir -p /usr/share/fonts/consolas
cp *.ttf /usr/share/fonts/consolas
rm -rf /tmp/fonttemp

fc-cache -r -v 
