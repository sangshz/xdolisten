# xdolisten  --  shortcuts of everything !
Listening keyboard and to do something. The sever "xdolisten" gets the input of keyboard and mouse.  If meeting  some key, it will  executive command "xdocmd".  "xdocmd" operates firefox with vim-likely shortcuts  by the well-known command “xdotool”.  That's an interesting idea rather than code.  This idea can set shortcuts for any application program! At least， save me from the update of firefox. 
The program records the last pressed key in file /tmp/xdolisten which can be used by your other program


usage method in Ubuntu 14.04：

1, "cat /proc/bus/input/devices" find the keyboard event num X,then chang "/dev/input/eventX" in xdolisten.c/xdolisten_mini.c. xdolisten_mini.c can find the keyboard event num X only if you input "Vendor" and "Product" for the usb device (usb keyboard)

2, change the key mapping to satisfy your custom in xdolisten.c/xdolisten_mini.c and xdocmd.

3, gcc xdolisten.c -o xdolisten

4, move "xdolisten" and "xdocmd" to /usr/local/bin/

5, sudo xdolisten &



ESC:  shortcuts mode

Shift: normal mode

in Firefox or Chromium,

u: Undo Close Tab 

d: Close Tab

r: Reload

t: New Tab

y: Copy web links of current Tab

gg: Home

RightShift+g: End

CTRL+1: goto the web "https://arxiv.org/list/hep-ph/new"

CTRL+2: goto the web ""

CTRL+3: goto the web ""




in skypeforlinux :

CTRL+1: Download file under cursor


in system :
RightShift + F6/F5 : brightness

recording pressed key:
/tmp/xdolisten
