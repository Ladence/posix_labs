#!/usr/bin/env bash
gnome-terminal -e "./cncr_rdr_0 in.txt"
sleep 1s
gnome-terminal -e "./cncr_rdr_1 in.txt"
sleep 1s
gnome-terminal -e "./cncr_rdr_2 in.txt"
read -n 1 -p "finish"
ipcrm --queue-key 0xdead
