# coding:utf-8
import sys
from PyQt5.QtCore import Qt, QEvent
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QApplication, QStackedWidget, QHBoxLayout, QLabel, QWidget, QVBoxLayout, QTableWidgetItem
from qfluentwidgets import (NavigationInterface, NavigationItemPosition, NavigationWidget, MessageBox,
                            isDarkTheme, setTheme, Theme, setThemeColor, NavigationToolButton, NavigationPanel)
from qfluentwidgets import FluentIcon as FIF
from qframelesswindow import FramelessWindow, StandardTitleBar
from qfluentwidgets import PushButton, LineEdit, InfoBar, InfoBarPosition, TableWidget, TableWidget, TableItemDelegate

import psutil  # pip  install  psutil
import socket # pip install socket
# 获取内存占用率
memory_usage = psutil.virtual_memory()

class TcpWidget(QWidget):

    def __init__(self, text: str, parent=None):
        super().__init__(parent=parent)
        self.label = QLabel(text, self)
        self.hBoxLayout = QHBoxLayout(self)

        self.label.setAlignment(Qt.AlignCenter)
        self.hBoxLayout.addWidget(self.label, 1, Qt.AlignCenter)

        self.setObjectName(text.replace(' ', '-'))
        self.IPAddress = PushButton('IP地址', self)
        self.IPAddress.move(120, 40)
        self.IPAddress.resize(100, 35)

        self.IPAddressLineEdit = LineEdit(self)
        self.IPAddressLineEdit.move(250, 40)
        self.IPAddressLineEdit.resize(200, 2500)
        self.IPAddressLineEdit.setClearButtonEnabled(True)

        self.setObjectName(text.replace(' ', '-'))
        self.PortName = PushButton('端口', self)
        self.PortName.move(120, 100)
        self.PortName.resize(100, 35)

        self.PortNameLineEdit = LineEdit(self)
        self.PortNameLineEdit.move(250, 100)
        self.PortNameLineEdit.resize(200, 2500)
        self.PortNameLineEdit.setClearButtonEnabled(True)

        self.TCPconnectSuccessButton = PushButton('连接', self)
        self.TCPconnectSuccessButton.clicked.connect(self.TCPconnectSuccess)
        self.TCPconnectSuccessButton.move(250, 200)
        self.TCPconnectSuccessButton.resize(200, 60)

        self.loginButton = PushButton('断开', self)
        self.loginButton.clicked.connect(self.TCPconnectRejust)
        self.loginButton.move(250, 300)
        self.loginButton.resize(200, 60)

    tcp_client_1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    def TCPconnectSuccess(self):
        print(self.IPAddressLineEdit.text())
        InfoBar.success(
            title='TCP',
            content="TCP通道已建立",
            orient=Qt.Horizontal,
            isClosable=True,
            position=InfoBarPosition.TOP,
            duration=2000,
            parent=self
        )
        # 192.168.137.169  2333
        # 打印内存占用率
        print(f"内存占用率: {memory_usage.percent}%")
        # 获取CPU使用率
        cpu_usage = psutil.cpu_percent(interval=1)  # 可以指定时间间隔
        print(f"CPU使用率: {cpu_usage}%")

        total_memory_gb = round(memory_usage.total / (2 ** 30), 2)
        used_memory_gb = round(memory_usage.used / (2 ** 30), 2)
        free_memory_gb = round(memory_usage.free / (2 ** 30), 2)
        percent_memory = round(memory_usage.percent, 2)
        print(f"GPU总内存: {total_memory_gb} GB")
        print(f"GPU已使用: {used_memory_gb} GB")
        print(f"GPU可用内存: {free_memory_gb} GB")
        print(f"GPU使用率: {percent_memory}%")
        message = "GPU使用率: " + str(percent_memory) + "%"
        print(message)
        # 1 创建客户端套接字对象tcp_client_1
        # 参数介绍：AF_INET 代表IPV4类型, SOCK_STREAM代表tcp传输协议类型 ,注：AF_INET6代表IPV6
        tcp_client_1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # 2 通过客户端套接字的connect方法与服务器套接字建立连接
        # 参数介绍：前面的ip地址代表服务器的ip地址，后面的61234代表服务端的端口号 。
        tcp_client_1.connect(("192.168.137.169", 2333))
        # tcp_client_1.connect((self.IPAddressLineEdit.text(), self.PortNameLineEdit.text()))
        # 将编号好的数据存到变量send_data中，注：encode(encoding='utf-8)是将数据转换成utf-8的格式发送给服务器
        send_data = ("CPU use:" + str(cpu_usage) + "%\n"+"GPU use"+ str(percent_memory) + "%\n\r").encode(encoding='utf-8')
        # send_data = ("GPU\r").encode(encoding='utf-8')
        # 3 通过客户端套接字的send方法将数据发送给服务器
        tcp_client_1.send(send_data)
        # 4 通过客户端套接字的recv方法来接受服务器返回的数据存到变量recv_data中，1024是可接收的最大字节数。
        recv_data = tcp_client_1.recv(1024)
        # 将接收到的服务器数据recv_data通过decode方法解码为utf-8
        print(recv_data.decode(encoding='utf-8'))
        # # 5 最后关闭客户端套接字连接

        # # 5 最后关闭客户端套接字连接
        # tcp_client_1.close()

    def TCPconnectRejust(self):
        print(self.IPAddressLineEdit.text())
        InfoBar.success(
            title='TCP',
            content="TCP通道关闭",
            orient=Qt.Horizontal,
            isClosable=True,
            position=InfoBarPosition.TOP,
            duration=2000,
            parent=self
        )

        # 打印内存占用率
        print(f"内存占用率: {memory_usage.percent}%")


class Window(FramelessWindow):

    def __init__(self):
        super().__init__()
        self.setTitleBar(StandardTitleBar(self))

        # use dark theme mode
        setTheme(Theme.DARK)

        # change the theme color
        # setThemeColor('#0078d4')

        self.vBoxLayout = QVBoxLayout(self)
        self.navigationInterface = NavigationBar(self)
        self.stackWidget = QStackedWidget(self)

        # create sub interface
        self.TcpInterface = TcpWidget(' ', self)


        self.stackWidget.addWidget(self.TcpInterface)


        # initialize layout
        self.initLayout()

        # add items to navigation interface
        self.initNavigation()

        self.initWindow()

    def initLayout(self):
        self.vBoxLayout.setSpacing(0)
        self.vBoxLayout.setContentsMargins(0, self.titleBar.height(), 0, 0)
        self.vBoxLayout.addWidget(self.navigationInterface)
        self.vBoxLayout.addWidget(self.stackWidget)
        self.vBoxLayout.setStretchFactor(self.stackWidget, 1)

    def initNavigation(self):
        self.addSubInterface(self.TcpInterface, FIF.VIDEO, 'TCP')

        self.navigationInterface.addSeparator()
        self.stackWidget.currentChanged.connect(self.onCurrentInterfaceChanged)
        self.stackWidget.setCurrentIndex(1)

    def addSubInterface(self, w: QWidget, icon, text, position=NavigationItemPosition.TOP):
        self.stackWidget.addWidget(w)
        self.navigationInterface.addItem(
            routeKey=w.objectName(),
            icon=icon,
            text=text,
            onClick=lambda: self.switchTo(w),
            position=position
        )

    def initWindow(self):
        self.resize(500, 500)
        self.setWindowIcon(QIcon('resource/logo.png'))
        self.setWindowTitle('TCP上位机')
        self.titleBar.setAttribute(Qt.WA_StyledBackground)

        desktop = QApplication.desktop().availableGeometry()
        w, h = desktop.width(), desktop.height()
        self.move(w // 2 - self.width() // 2, h // 2 - self.height() // 2)

        self.setQss()

    def setQss(self):
        color = 'dark' if isDarkTheme() else 'light'
        with open(f'resource/{color}/demo.qss', encoding='utf-8') as f:
            self.setStyleSheet(f.read())

    def switchTo(self, widget):
        self.stackWidget.setCurrentWidget(widget)

    def onCurrentInterfaceChanged(self, index):
        widget = self.stackWidget.widget(index)
        self.navigationInterface.setCurrentItem(widget.objectName())


class NavigationBar(QWidget):
    """ Navigation widget """

    def __init__(self, parent=None):
        super().__init__(parent=parent)
        self.hBoxLayout = QHBoxLayout(self)
        self.menuButton = NavigationToolButton(FIF.MENU, self)
        self.navigationPanel = NavigationPanel(parent, True)
        self.titleLabel = QLabel(self)

        self.navigationPanel.move(0, 31)
        self.hBoxLayout.setContentsMargins(5, 5, 5, 5)
        self.hBoxLayout.addWidget(self.menuButton)
        self.hBoxLayout.addWidget(self.titleLabel)

        self.menuButton.clicked.connect(self.showNavigationPanel)
        self.navigationPanel.setExpandWidth(260)
        self.navigationPanel.setMenuButtonVisible(True)
        self.navigationPanel.hide()

        self.window().installEventFilter(self)

    def setTitle(self, title: str):
        self.titleLabel.setText(title)
        self.titleLabel.adjustSize()

    def showNavigationPanel(self):
        self.navigationPanel.show()
        self.navigationPanel.raise_()
        self.navigationPanel.expand()

    def addItem(self, routeKey, icon, text: str, onClick, selectable=True, position=NavigationItemPosition.TOP):
        def wrapper():
            onClick()
            self.setTitle(text)

        self.navigationPanel.addItem(
            routeKey, icon, text, wrapper, selectable, position)

    def addSeparator(self, position=NavigationItemPosition.TOP):
        self.navigationPanel.addSeparator(position)

    def setCurrentItem(self, routeKey: str):
        self.navigationPanel.setCurrentItem(routeKey)
        self.setTitle(self.navigationPanel.widget(routeKey).text())

    def eventFilter(self, obj, e: QEvent):
        if obj is self.window():
            if e.type() == QEvent.Resize:
                self.navigationPanel.setFixedHeight(e.size().height() - 31)

        return super().eventFilter(obj, e)


if __name__ == '__main__':
    QApplication.setHighDpiScaleFactorRoundingPolicy(
        Qt.HighDpiScaleFactorRoundingPolicy.PassThrough)
    QApplication.setAttribute(Qt.AA_EnableHighDpiScaling)
    QApplication.setAttribute(Qt.AA_UseHighDpiPixmaps)

    app = QApplication(sys.argv)
    w = Window()
    w.show()
    app.exec_()
