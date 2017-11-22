//sudo gcc xdolisten.c -o xdolisten
//xdolisten 实现监听键盘; 通过调用脚本xdocmd来做任何想做的事，其中开关设定为ESC键。xdolisten需要管理员权限
//目前xdocmd通过xdotool实现firefox快捷键功能
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <linux/input.h>

int main()
{
	//ubuntu14.04可通过"cat /proc/bus/input/devices"确定键盘事件"/dev/input/eventx"
	int keys_fd = open("/dev/input/event4", O_RDONLY);
	if(keys_fd <= 0)
	{
		printf("open /dev/input/event4 device error!\n");
		return 0;
	}


	bool DOOR=false;
	char ret[2];
	struct input_event t;
	__u16 code_old = 0;
	bool Shift=false;
	bool Alt=false;
	bool Ctrl=false;
	while(1)
	{
		if(read(keys_fd, &t, sizeof(t)) == sizeof(t))
		{
			if(t.type == EV_KEY)
			{
				if(t.code == KEY_LEFTSHIFT | t.code == KEY_RIGHTSHIFT)Shift=t.value;
				if(t.code == KEY_LEFTALT | t.code == KEY_RIGHTALT)Alt=t.value;
				if(t.code == KEY_LEFTCTRL | t.code == KEY_RIGHTCTRL)Ctrl=t.value;
			}

			if(t.type == EV_KEY && t.value == 1)
			{
				//printf("key %d %s, time: %ld:%ld\n", t.code, (t.value) ? "Pressed" : "Released",t.time.tv_sec,t.time.tv_usec);
				if(DOOR)
				{
					switch(t.code)
					{
						case KEY_U: 
							system("xdocmd u ");
							break;
						case KEY_R:
							system("xdocmd r");
							break;
						case KEY_D: 
							system("xdocmd d ");
							break;
						case KEY_T: 
							system("xdocmd t ");
							break;
						case KEY_Y: 
							system("xdocmd y ");
							break;
						case KEY_G:
							if(Shift)
							{
								system("xdocmd SHIFTg ");
							}
							else if (code_old == KEY_G)
							{
								system("xdocmd gg ");
							}
							break;
						case KEY_1: 
							if(Ctrl)
							{
								system("xdocmd CTRL1 ");
							}
							if(Alt)
							{
								system("xdocmd ALT1 ");
							}
							break;
						case KEY_2: 
							if(Ctrl)
							{
								system("xdocmd CTRL2 ");
							}
							if(Alt)
							{
								system("xdocmd ALT2 ");
							}
							break;
						case KEY_3: 
							if(Ctrl)
							{
								system("xdocmd CTRL3 ");
							}
							if(Alt)
							{
								system("xdocmd ALT3 ");
							}
							break;
						case KEY_4: 
							if(Ctrl)
							{
								system("xdocmd CTRL4 ");
							}
							if(Alt)
							{
								system("xdocmd ALT4 ");
							}
							break;
						case KEY_I: 
							DOOR=false;
							break;
						case KEY_A: 
							DOOR=false;
							break;
						default:
							break;
					}
				}

				if(t.code == KEY_ESC)
				{
					//DOOR=!DOOR;
					DOOR=true;
				}

				if(!DOOR)
				{
					Shift=false;
					Alt=false;
					Ctrl=false;
				}

				code_old = t.code;
			}

		}
		//fflush(stdin);
	}

	close(keys_fd);

	return 0;
}
