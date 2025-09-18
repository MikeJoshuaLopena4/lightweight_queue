#!/bin/bash
/usr/local/bin/server /tmp/.queue 2600 &
/usr/local/bin/websocketd --dir /usr/local/etc/shp/ --cgidir /usr/local/etc/shp/ --port 81
/usr/local/bin/printer