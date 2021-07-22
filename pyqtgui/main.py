from PyQt5 import QtWidgets
import sys
# qt designer module
import gui_module

# self.textBrowser.append("tever"), https://www.w3schools.com/python/python_ref_list.asp


class MyApp (QtWidgets.QMainWindow, gui_module.Ui_tcp_server):

    def __init__(self, parent=None):

        super(MyApp, self).__init__(parent)

        # Load the login form

        self.setupUi(self)
        self.setup_button_actions()


    def setup_button_actions(self):
        # self.push_button_1.connect(self.button1_press)
        self.push_button_1.clicked.connect(self.button1_press)
        self.push_button_2.clicked.connect(self.button2_press)

    def write_to_textbox(self, string):
        self.textBrowser.append(string)
    
    def clear_textbox(self):
        self.textBrowser.clear()

    def ui_components(self):
        pass

    def button1_press(self):
        print("FUNC1, write")

        text = "moro"
        self.write_to_textbox(text)

    def button2_press(self):
        print("FUNC2, clear")
        self.clear_textbox()
        # self.text.setText("fun2")

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