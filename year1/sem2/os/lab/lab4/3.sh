#!/bin/bash

ps -ef |\
grep -e "vim" -e "emacs" -e "nano" -e "pico" |\
awk 'BEGIN{sum = 0} {sum += $2} END{print sum}'
