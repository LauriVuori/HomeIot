from PyQt5 import QtWidgets
import sys
# qt designer module
import gui_module
#Call c
import ctypes
#threads
import threading

from time import sleep

# self.textBrowser.append("tever"), https://www.w3schools.com/python/python_ref_list.asp


def thread():
    c_types_array[0] = 0
    c_types_array[1] = 1
    c_types_array[2] = 2
    c_flags[0] = 0
    c_flags[1] = 0
    c_flags[2] = 0
    c_funtions = ctypes.CDLL("./Cfunc.so")
    c_funtions.print(c_types_array, c_flags)
    for i in range(len(c_types_array)):
        print(c_types_array[i])
    
    
    
    # num = ctypes.POINTER(ctypes.c_int * 10)
    # print(type(num))
    
    # num.restype = ctypes.POINTER(ctypes.c_int * 10)

    # num.print()
    # print("Thread closed")

class MyApp (QtWidgets.QMainWindow, gui_module.Ui_tcp_server):
    c_thread = threading.Thread(target=thread, args=())

    def __init__(self, parent=None):

        super(MyApp, self).__init__(parent)

        # Load the login form

        self.setupUi(self)
        self.setup_button_actions()

        self.start_threading()

    def start_threading(self):
        print("Threading started")
        try:
            self.c_thread.start()
        except BaseException:
            print('Error: unable to start thread')
        print("c_thread join")

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
        print("func1 print")
        text = str(self.c_types_array[0] + " " + self.c_types_array[1])
        self.write_to_textbox(text)
        

    def button2_press(self):
        print("FUNC2, clear")
        self.clear_textbox()
        c_flags[0] = 1
        print("closing gui")
        self.c_thread.join()
        
        
        
        # self.text.setText("fun2")

    #     if self.textEdit.toPlainText() == 'admin' and self.textEdit_2.toPlainText() == 'superuser':

    #         print('Authenticated User')

    #     else:

    #         print('Unauthenticated User')


    # Declare method to terminate the script when Cancel button will click

    # def cancelClicked(self):

    #     exit()



if __name__ == "__main__":
    c_types_array = ((ctypes.c_int*3))()
    c_flags = ((ctypes.c_int*3))()
    app = QtWidgets.QApplication(sys.argv)

    # Create class object
    form = MyApp()

    # Display the form
    form.show()

    # Start the event loop of the app or dialog box
    app.exec()
    

