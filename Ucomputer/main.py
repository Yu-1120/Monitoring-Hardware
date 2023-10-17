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





class loginWidget(QWidget):

    def __init__(self, text: str, parent=None):
        super().__init__(parent=parent)
        self.label = QLabel(text, self)
        self.hBoxLayout = QHBoxLayout(self)

        self.label.setAlignment(Qt.AlignCenter)
        self.hBoxLayout.addWidget(self.label, 1, Qt.AlignCenter)

        self.setObjectName(text.replace(' ', '-'))
        self.loginName = PushButton('IP地址', self)
        self.loginName.move(100, 40)
        self.loginName.resize(100, 40)

        self.loginAccountLineEdit = LineEdit(self)
        self.loginAccountLineEdit.move(250, 40)
        self.loginAccountLineEdit.resize(600, 2500)
        self.loginAccountLineEdit.setClearButtonEnabled(True)

        self.setObjectName(text.replace(' ', '-'))
        self.loginPassword = PushButton('端口', self)
        self.loginPassword.move(100, 100)
        self.loginPassword.resize(100, 40)

        self.loginPasswordLineEdit = LineEdit(self)
        self.loginPasswordLineEdit.move(250, 100)
        self.loginPasswordLineEdit.resize(600, 2500)
        self.loginPasswordLineEdit.setClearButtonEnabled(True)

        self.loginButton = PushButton('登录Login', self)
        self.loginButton.clicked.connect(self.createLoginInfoBar)
        self.loginButton.move(400, 200)
        self.loginButton.resize(200, 33)

    def createLoginInfoBar(self):
        print("登录成功！")
        InfoBar.success(
            title='登录成功！',
            content="登录成功！",
            orient=Qt.Horizontal,
            isClosable=True,
            position=InfoBarPosition.TOP,
            duration=2000,
            parent=self
        )




class registerWidget(QWidget):

    def __init__(self, text: str, parent=None):
        super().__init__(parent=parent)
        self.label = QLabel(text, self)
        self.hBoxLayout = QHBoxLayout(self)

        self.label.setAlignment(Qt.AlignCenter)
        self.hBoxLayout.addWidget(self.label, 1, Qt.AlignCenter)

        self.setObjectName(text.replace(' ', '-'))

        self.registerName = PushButton('注册账号', self)
        self.registerName.move(100, 40)
        self.registerName.resize(100, 40)

        self.registerAccountLineEdit = LineEdit(self)
        self.registerAccountLineEdit.move(250, 40)
        self.registerAccountLineEdit.resize(600, 2500)
        self.registerAccountLineEdit.setClearButtonEnabled(True)

        self.registerPassword = PushButton('注册密码', self)
        self.registerPassword.move(100, 100)
        self.registerPassword.resize(100, 40)

        self.regiterPasswordLineEdit = LineEdit(self)
        self.regiterPasswordLineEdit.move(250, 100)
        self.regiterPasswordLineEdit.resize(600, 2500)
        self.regiterPasswordLineEdit.setClearButtonEnabled(True)

        self.regiterButton = PushButton('注册Resigter', self)

        self.regiterButton.move(400, 200)
        self.regiterButton.resize(200, 60)




class selectWidget(QWidget):

    def __init__(self, text: str, parent=None):
        super().__init__(parent=parent)
        self.label = QLabel(text, self)
        self.hBoxLayout = QHBoxLayout(self)








class deleteWidget(QWidget):

    def __init__(self, text: str, parent=None):
        super().__init__(parent=parent)
        self.label = QLabel(text, self)
        self.hBoxLayout = QHBoxLayout(self)

        self.label.setAlignment(Qt.AlignCenter)
        self.hBoxLayout.addWidget(self.label, 1, Qt.AlignCenter)

        self.setObjectName(text.replace(' ', '-'))

        self.deleteName = PushButton('删除账号名字', self)
        self.deleteName.move(100, 40)
        self.deleteName.resize(100, 40)

        self.deleteNameLineEdit = LineEdit(self)
        self.deleteNameLineEdit.move(250, 40)
        self.deleteNameLineEdit.resize(600, 2500)
        self.deleteNameLineEdit.setClearButtonEnabled(True)

        self.deleteButton = PushButton('确定删除', self)

        self.deleteButton.move(400, 200)
        self.deleteButton.resize(200, 33)






class updateWidget(QWidget):

    def __init__(self, text: str, parent=None):
        super().__init__(parent=parent)
        self.label = QLabel(text, self)
        self.hBoxLayout = QHBoxLayout(self)

        self.label.setAlignment(Qt.AlignCenter)
        self.hBoxLayout.addWidget(self.label, 1, Qt.AlignCenter)

        self.setObjectName(text.replace(' ', '-'))

        self.deleteName = PushButton('需要修改账号名字', self)
        self.deleteName.move(100, 40)
        self.deleteName.resize(100, 40)

        self.deleteAccountLineEdit = LineEdit(self)
        self.deleteAccountLineEdit.move(250, 40)
        self.deleteAccountLineEdit.resize(600, 2500)
        self.deleteAccountLineEdit.setClearButtonEnabled(True)

        self.deletePassword = PushButton('修改密码', self)
        self.deletePassword.move(100, 100)
        self.deletePassword.resize(100, 40)

        self.deletePasswordLineEdit = LineEdit(self)
        self.deletePasswordLineEdit.move(250, 100)
        self.deletePasswordLineEdit.resize(600, 2500)
        self.deletePasswordLineEdit.setClearButtonEnabled(True)

        self.deleteButton = PushButton('修改', self)

        self.deleteButton.move(400, 200)
        self.deleteButton.resize(200, 60)




#####################################  update method  END


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
        self.loginInterface = loginWidget('0', self)
        self.resgisterInterface = registerWidget('1', self)
        self.selectInterface = selectWidget('2', self)
        self.deleteInterface = deleteWidget('3', self)
        self.updateInterface = updateWidget('4', self)

        self.stackWidget.addWidget(self.loginInterface)
        self.stackWidget.addWidget(self.resgisterInterface)
        self.stackWidget.addWidget(self.selectInterface)
        self.stackWidget.addWidget(self.deleteInterface)
        self.stackWidget.addWidget(self.updateInterface)

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
        self.addSubInterface(self.loginInterface, FIF.VIDEO, 'TCP')
        self.addSubInterface(self.resgisterInterface, FIF.VIDEO, '')
        self.addSubInterface(self.selectInterface, FIF.VIDEO, '')
        self.addSubInterface(self.deleteInterface, FIF.VIDEO, '')
        self.addSubInterface(self.updateInterface, FIF.VIDEO, '')
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
        self.resize(1000, 500)
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
