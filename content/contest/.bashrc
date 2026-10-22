alias c='g++ -Wall -Wconversion -Wfatal-errors -g -std=c++17 -fsanitize=undefined,address'
alias co='g++ -O2 -std=c++17'
ulimit -s unlimited
xmodmap -e 'clear lock' -e 'keycode 66 = Control_L' -e 'add Control = Control_L'
setxkbmap -option ctrl:nocaps
gsettings set org.gnome.desktop.input-sources xkb-options "['ctrl:nocaps']"
