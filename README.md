# xdolisten
Listening keyboard and to do something. The sever "xdolisten" gets the input of keyboard and mouse.  If meeting  some key, it will  executive command "xdocmd".  "xdocmd" operates firefox with vim-likely shortcut  by the well-known command “xdotool”.  That's an interesting idea rather than code.  This idea can set shortcut for any application program! At least， save me from the update of firefox. 


usage method in Ubuntu 14.04：

1, "cat /proc/bus/input/devices" find the keyboard event num X,then chang "/dev/input/eventX" in xdolisten.c

2, change the key mapping to satisfy your custom in xdolisten.c and xdocmd.

3, gcc xdolisten.c -o xdolisten

4, move "xdolisten" and "xdocmd" to /usr/local/bin/

5, sudo xdolisten &
