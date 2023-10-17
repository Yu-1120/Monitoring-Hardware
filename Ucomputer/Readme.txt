# 1需要python的环境



# 2需要安装的库

pip  install  psutil

pip install PyQt-Fluent-Widgets


pip install "PyQt-Fluent-Widgets[full]" -i https://mirrors.aliyun.com/pypi/simple/


# 3我也有编译好的程序，如果不能运行，需要自己下载一个库文件

编译命令


1. 安装PyInstaller：首先，你需要安装PyInstaller。你可以使用pip来安装它：

```

pip install pyinstalle
```

1. 打包你的Python程序：在命令行中，进入包含你的Python脚本的目录，然后运行PyInstaller，指定你的Python脚本作为输入：

```

pyinstaller your_script.py

```