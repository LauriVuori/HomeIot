import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot

def make_button(x, y, button_text):
    button = QPushButton("Button_1", self)
    button.setToolTip("Button 1")
    button.move(0, 5)
    button.clicked.connect(self.on_click_1)

class App(QWidget):
    def __init__(self):
        super().__init__()
        self.title = "TCP server"
        self.left = 450
        self.top = 450
        self.width = 320
        self.height = 200
        self.initUI()
  
    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)
        self.create_button(0, 5, "button1", "tooltip1", self.on_click_1)
        self.create_button(0, 30, "button2", "tooltip2", self.on_click_2)

        self.show()

    def create_button(self, x, y, button_text, tool_tip_text, function):
        button = QPushButton(button_text, self)
        button.setToolTip(tool_tip_text)
        button.move(x, y)
        button.clicked.connect(function)

    # @pyqtSlot()
    def on_click_1(self):
        print("Button 1")
   
    def on_click_2(self):
        print("Button 2")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())