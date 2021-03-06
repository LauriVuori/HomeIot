
from kivy import Config
from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.floatlayout import FloatLayout


#text window
from kivy.core.window import Window
from kivy.uix.widget import Widget
from kivy.uix.slider import Slider

#Call c
import ctypes

#threads
import threading

from time import sleep


"""
A class used to represent an Animal
...
Attributes
----------
Methods
-------
"""
"""
A class used to represent an Animal
...
Parameters
----------
Return
-------
"""
Config.set('graphics', 'width', '700')
Config.set('graphics', 'height', '900')


def thread():
    c_types_array[0] = 0
    c_types_array[1] = 1
    c_types_array[2] = 2
    c_funtions = ctypes.CDLL("./Cfunc.so")
    c_funtions.print(c_types_array)
    for i in range(len(c_types_array)):
        print(c_types_array[i])
    # num = ctypes.POINTER(ctypes.c_int * 10)
    # print(type(num))
    
    # num.restype = ctypes.POINTER(ctypes.c_int * 10)

    # num.print()
    print("Thread closed")

def printti():
    while 1:
        print("terve111")
        sleep(0.5)


class ServerApp(App):
    """
    Top left buttons
    ...
    Attributes
    ----------
    Methods
    -------
    """
    def build(self):
        layoutsize = ((300, 300))
        layout = FloatLayout(size=(layoutsize))
        # layout = AnchorLayout(anchor_x='left', anchor_y='top',size=(layoutsize))
        layout = self.init_buttons(layout)

        return layout

    def press_button1(self, instance):
        print("Start Threading")
        try:
            c_thread = threading.Thread(target=thread, args=())
            c_thread.start()
        except BaseException:
            print('Error: unable to start thread')
        print("c_thread join")
        

    def press_button2(self, instance):
        print("kakkosfunc")


    def init_buttons(self, layout):
        button1 = Button(text="Button1", size_hint=(.1, .1),
                         pos_hint={'x': .0, 'y': .9})
        button2 = Button(text="Button2", size_hint=(.1, .1),
                         pos_hint={'x': .0, 'y': .8})
        # s = Slider(min=-100, max=100, value=25)
        # button1.background_color = (5, 5, 1, 1)
        button1.bind(on_press=self.press_button1)
        button2.bind(on_press=self.press_button2)
        layout.add_widget(button1)
        layout.add_widget(button2)
        return layout


if __name__ == "__main__":
    c_types_array = ((ctypes.c_int*3))()

    ServerApp().run()
