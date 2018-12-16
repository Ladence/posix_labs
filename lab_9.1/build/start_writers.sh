#!/usr/bin/env bash
rm out.txt
gnome-terminal -e "./cncr_wrtr_0 out.txt 1 5"
sleep 1s
gnome-terminal -e "./cncr_wrtr_1 out.txt 2 10"
sleep 1s
gnome-terminal -e "./cncr_wrtr_2 out.txt 0 2"
read -n 1 -p "finish"
ipcrm --shmem-key 0x36000
cat out.txt
