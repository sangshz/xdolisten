//sudo gcc xdolisten.c -o xdolisten
//xdolisten 实现监听键盘; 通过调用脚本xdocmd来做任何想做的事，其中开关设定为Shift键。xdolisten需要管理员权限
//目前xdocmd通过xdotool实现firefox等窗体软件的快捷键功能
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <linux/input.h>

//get_event_num("Vendor=1997 Product=2433",eventnum);   通过Vendor和Product找到输入设备的事件编号
void get_event_num(const char *matchstring0,char * eventnum)
{
	int devices=open("/proc/bus/input/devices",O_RDONLY);
	//const char matchstring0[]="Vendor=1997 Product=2433";
	const char *matchstring1="event";
	char res;
	int i=0;
	int j=0;
	int k=0;
	//char eventnum[4]="";
	while(read(devices,&res,1)){
		if( i<strlen(matchstring0) ){
			(matchstring0[i]==res) ? (i++) : (i=0);
		}else if( j<strlen(matchstring1) ){
			(matchstring1[j]==res) ? (j++) : (j=0);
		}else{
			if(isdigit(res)){
				eventnum[k]=res;
				k++;
			}else{
				break;
			}
		}
	}
	close(devices);
}

int main()
{
	//ubuntu14.04可通过"cat /proc/bus/input/devices"确定键盘事件"/dev/input/eventx" (外接usb设备有时需要借用lsusb)
	//const char * VDPD = "Vendor=1997 Product=2433";
	//char eventnum[4]="";get_event_num(VDPD,eventnum);
	//char eventx[30]="/dev/input/event";  strcat(eventx,eventnum);//printf("%s\n",eventx);
	char * eventx="/dev/input/event3";

	int keys_fd = open(eventx, O_RDONLY);
	if(keys_fd <= 0){
		printf("open device error!\n");
		return 0;
	}

	int sleeptimes=0;
	bool DOOR=false;
	struct input_event t;
	__u16 code_old = 0;
	bool Shift = false;
	bool LeftShift = false;
	bool RightShift = false;
	bool Alt = false;
	bool Ctrl = false;
	char buf[32]; 
	while(1){
		if(read(keys_fd, &t, sizeof(t)) == sizeof(t)){
			if(t.type == EV_KEY){
				//printf("t.code = %d\n",t.code);
				if(t.code == KEY_LEFTALT | t.code == KEY_RIGHTALT)Alt=t.value;
				if(t.code == KEY_LEFTCTRL | t.code == KEY_RIGHTCTRL)Ctrl=t.value;
				if(t.code == KEY_LEFTSHIFT | t.code == KEY_RIGHTSHIFT)Shift=t.value;
				if(t.code == KEY_LEFTSHIFT)LeftShift=t.value;
				if(t.code == KEY_RIGHTSHIFT)RightShift=t.value;
			}

			if(t.type == EV_KEY && t.value == 1){
				//printf("key %d %s, time: %ld:%ld\n", t.code, (t.value) ? "Pressed" : "Released",t.time.tv_sec,t.time.tv_usec);
				sprintf(buf, "echo %d > /tmp/xdolisten  ", t.code); system(buf);
				if(DOOR){
					bool FUNC = Shift || Alt || Ctrl;
					switch(t.code){
						case KEY_U: 
							if(!FUNC)system("xdocmd u ");
							break;
						case KEY_R:
							if(!FUNC)system("xdocmd r");
							break;
						case KEY_D: 
							if(!FUNC)system("xdocmd d ");
							break;
						case KEY_T:
							if(!FUNC)system("xdocmd t ");
							break;
						case KEY_Y: 
							if(!FUNC)system("xdocmd y ");
							break;
						case KEY_J: 
							if(!FUNC)system("xdocmd j ");
							break;
						case KEY_K: 
							if(!FUNC)system("xdocmd k ");
							break;
						case KEY_G:
							if(Shift){
								system("xdocmd SHIFTg ");
							} else if (code_old == KEY_G){
								if(!FUNC)system("xdocmd gg ");
							}
							break;
						case KEY_1: 
							if(Ctrl){
								system("xdocmd CTRL1 ");
							}
							if(Alt){
								system("xdocmd ALT1 ");
							}
							break;
						case KEY_2: 
							if(Ctrl){
								system("xdocmd CTRL2 ");
							}
							if(Alt){
								system("xdocmd ALT2 ");
							}
							break;
						case KEY_3: 
							if(Ctrl){
								system("xdocmd CTRL3 ");
							}
							if(Alt){
								system("xdocmd ALT3 ");
							}
							break;
						case KEY_4: 
							if(Ctrl){
								system("xdocmd CTRL4 ");
							}
							if(Alt){
								system("xdocmd ALT4 ");
							}
							break;
						case 63:
							if(RightShift){
								system("echo $((`cat /sys/class/backlight/intel_backlight/brightness`-200)) > /sys/class/backlight/intel_backlight/brightness");
							}
							break;
						case 64:
							if(RightShift){
								system("echo $((`cat /sys/class/backlight/intel_backlight/brightness`+200)) > /sys/class/backlight/intel_backlight/brightness");
							}
							break;
						default:
							break;
					}
				}

				if(t.code == KEY_ESC){
					//DOOR=!DOOR;
					DOOR=true;
				}
				if(LeftShift){
					DOOR=false;
				}

				if(!DOOR){
					Shift=false;
					RightShift=false;
					LeftShift=false;
					Alt=false;
					Ctrl=false;
				}

				code_old = t.code;
			}

		} else {
			close(keys_fd);
			//strcpy(eventnum,"");get_event_num(VDPD,eventnum);
			//strcpy(eventx,"/dev/input/event");strcat(eventx,eventnum);
			keys_fd = open(eventx, O_RDONLY);
			if(keys_fd <= 0){
				printf("open device error!\n");
				return 0;
				sleep(1);
				sleeptimes++;
				if(sleeptimes>60)return 0;
			} else {
				sleeptimes=0;
			}
		}
		//fflush(stdin);
	}

	close(keys_fd);

	return 0;
}
