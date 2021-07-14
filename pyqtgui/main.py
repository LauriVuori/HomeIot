# Import QtWidgets

from PyQt5 import QtWidgets

# Import sys

import sys

# Import login form ui

import gui_module

# Define a class to setup the UI

class MyApp (QtWidgets.QMainWindow, gui_module.Ui_tcp_server):

    def __init__(self, parent=None):

        super(MyApp, self).__init__(parent)

        # Load the login form

        self.setupUi(self)

        
        # Call loginClicked() method

        # self.btnLogin.clicked.connect(self.loginClicked)
        

        # Call cancelClicked() method

        # self.btnCancel.clicked.connect(self.cancelClicked)


    # Declare method to check username and password when Login button will click
    def pretend_something_happened(self):
        # User Did something
        self.lineEdit.setText("User Entered Something")

    def button1_press(self):
        print("FUNC1")
        self.pretend_something_happened(self)

    def button2_press(self):
        print("FUNC2")

    #     if self.textEdit.toPlainText() == 'admin' and self.textEdit_2.toPlainText() == 'superuser':

    #         print('Authenticated User')

    #     else:

    #         print('Unauthenticated User')


    # Declare method to terminate the script when Cancel button will click

    # def cancelClicked(self):

    #     exit()



app = QtWidgets.QApplication(sys.argv)

# Create class object

form = MyApp()

# Display the form

form.show()

# Start the event loop of the app or dialog box

app.exec()