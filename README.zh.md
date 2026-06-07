# xdolisten —— 为一切操作添加快捷键！

`xdolisten` 负责监听键盘和鼠标输入，并在检测到指定按键或组合键时触发相应动作。当设定的按键被按下时，它会执行 `xdocmd` 命令。  
`xdocmd` 利用著名的 `xdotool` 工具来控制 Firefox（以及其他应用），实现类似 Vim 的快捷键操作。

这不仅仅是代码，更是一个强大的理念：**为任意应用程序设置自定义快捷键！** 至少对我来说，它省去了为 Firefox 的每次更新而疲于调整快捷键的麻烦。

该程序还会将最后按下的按键记录在 `/tmp/xdolisten` 中，可供你自己的脚本或程序使用。

---

## 使用方法（Ubuntu 14.04）

1. **获取键盘设备号**  
   运行：  
   `cat /proc/bus/input/devices`  
   找到你的键盘，记下对应的 `eventX` 编号。  
   然后更新 `xdolisten.c` / `xdolisten_mini.c` 中的 `/dev/input/eventX` 路径。  

   *对于 USB 键盘*：如果你提供了 `Vendor`（供应商 ID）和 `Product`（产品 ID），`xdolisten_mini.c` 可以自动识别设备号。

2. **自定义按键映射**  
   编辑 `xdolisten.c` / `xdolisten_mini.c` 和 `xdocmd` 文件，按需定义自己的快捷键。

3. **编译**  
   `gcc xdolisten.c -o xdolisten`

4. **安装**  
   将 `xdolisten` 和 `xdocmd` 移动到 `/usr/local/bin/`

5. **运行**  
   `sudo xdolisten &`

---

## 快捷键模式

- **ESC** – 快捷键模式  
- **Shift** – 正常模式

---

## 应用程序快捷键

### Firefox / Chromium

| 快捷键            | 动作                   |
|------------------|------------------------|
| `u`              | 恢复已关闭的标签页      |
| `d`              | 关闭当前标签页          |
| `r`              | 刷新页面               |
| `t`              | 新建标签页             |
| `y`              | 复制当前标签页的 URL    |
| `gg`             | 回到页面顶部            |
| `RightShift + g` | 跳到页面底部            |
| `CTRL+1`         | 打开 `https://arxiv.org/list/hep-ph/new` |
| `CTRL+2`         | （自定义网址）          |
| `CTRL+3`         | （自定义网址）          |

### Skype for Linux

| 快捷键      | 动作                     |
|-------------|--------------------------|
| `CTRL+1`    | 下载光标所指的文件        |

### 系统

| 快捷键              | 动作           |
|---------------------|----------------|
| `RightShift + F6`   | 降低屏幕亮度    |
| `RightShift + F5`   | 提高屏幕亮度    |

---

## 记录的按键

最后按下的按键会被写入 `/tmp/xdolisten` 文件 —— 可供你的其他程序使用。
