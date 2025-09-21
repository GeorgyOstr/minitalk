#!/bin/bash
echo "Testing"

cc server.c -o server && ./server &
pid=$(exif ... | tail -1)
echo "Server PID = $pid"
sleep 1

cc client.c -o client && ./client $pid ""
