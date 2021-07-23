from PyQt5 import QtWidgets
import sys
# qt designer module
import gui_module
#Call c
import ctypes
#threads
import threading

import const

from time import sleep

# self.textBrowser.append("tever"), https://www.w3schools.com/python/python_ref_list.asp


def thread():
    c_types_array[0] = 0
    c_types_array[1] = 1
    c_types_array[2] = 2
    c_flags[const.TCP_SERVER_RUNNING] = True
    c_flags[1] = True
    c_flags[2] = True
    c_funtions = ctypes.CDLL("./Cfunc.so")
    c_funtions.print(c_types_array, c_flags)
    # print("C IN PYTHON")
    # for i in range(len(c_types_array)):
    #     print(c_types_array[i])
    
    
    
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


    def start_threading(self):
        print("Threading started")
        try:
            self.c_thread.start()
        except BaseException:
            print('Error: unable to start thread')
        print("c_thread join")

    def setup_button_actions(self):
        # self.push_button_1.connect(self.button1_press)
        self.button_print_to_box.clicked.connect(self.print_to_box)
        self.button_stop_server.clicked.connect(self.stop_server)
        self.button_start_server.clicked.connect(self.start_server)
        self.button_clear_box.clicked.connect(self.clear_textbox)

    def write_to_textbox(self, string):
        self.textBrowser.append(string)
    
    def clear_textbox(self):
        self.textBrowser.clear()

    def ui_components(self):
        pass

    def print_to_box(self):
        text = "numbers from c func:" + str(c_types_array[0]) + " " + str(c_types_array[1]) + " " + str(c_types_array[2])
        self.write_to_textbox(text)

    def start_server(self):
        self.button_start_server.setStyleSheet("background-color : green")
        self.button_stop_server.setStyleSheet("background-color : light gray")
        self.c_thread = threading.Thread(target=thread, args=())
        self.start_threading()


    def stop_server(self):
        self.button_stop_server.setStyleSheet("background-color : red")
        self.button_start_server.setStyleSheet("background-color : light gray")
        c_flags[const.TCP_SERVER_RUNNING] = False
        self.c_thread.join()



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
    

