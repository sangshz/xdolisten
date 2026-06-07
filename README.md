> [English](README.md) | [中文版](README.zh.md)

# xdolisten – Shortcuts for Everything!

`xdolisten` listens to keyboard and mouse input and triggers actions based on key presses. When a specified key or key combination is detected, it executes the `xdocmd` command.  
`xdocmd` uses the well-known `xdotool` to control Firefox (and other apps) with Vim‑like shortcuts.

This is more than just code – it's a powerful idea: **set custom shortcuts for any application!**  
At the very least, it saves me from the hassle of keeping up with Firefox updates.

The program also records the last pressed key in `/tmp/xdolisten`, which can be used by your own scripts or programs.

---

## Usage (Ubuntu 14.04)

1. **Find your keyboard event number**  
   Run:  
   `cat /proc/bus/input/devices`  
   Locate your keyboard and note the `eventX` number.  
   Then update `/dev/input/eventX` in `xdolisten.c` / `xdolisten_mini.c`.  

   *For USB keyboards*: `xdolisten_mini.c` can find the event number automatically if you provide `Vendor` and `Product` IDs.

2. **Customize key mappings**  
   Edit `xdolisten.c` / `xdolisten_mini.c` and `xdocmd` to define your own shortcuts.

3. **Compile**  
   `gcc xdolisten.c -o xdolisten`

4. **Install**  
   Move `xdolisten` and `xdocmd` to `/usr/local/bin/`

5. **Run**  
   `sudo xdolisten &`

---

## Shortcut Modes

- **ESC** – Shortcuts mode  
- **Shift** – Normal mode

---

## Application Shortcuts

### Firefox / Chromium

| Shortcut         | Action                |
|------------------|-----------------------|
| `u`              | Undo Close Tab        |
| `d`              | Close Tab             |
| `r`              | Reload                |
| `t`              | New Tab               |
| `y`              | Copy current tab’s URL|
| `gg`             | Go to top (Home)      |
| `RightShift + g` | Go to bottom (End)    |
| `CTRL+1`         | Open `https://arxiv.org/list/hep-ph/new` |
| `CTRL+2`         | *(custom URL)*        |
| `CTRL+3`         | *(custom URL)*        |

### Skype for Linux

| Shortcut | Action                     |
|----------|----------------------------|
| `CTRL+1` | Download file under cursor |

### System

| Shortcut           | Action       |
|--------------------|--------------|
| `RightShift + F6`  | Decrease brightness |
| `RightShift + F5`  | Increase brightness |

---

## Recorded Key

The last pressed key is written to `/tmp/xdolisten` – usable by your other programs.
