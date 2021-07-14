from kivy.app import App
from kivy.uix.label import Label

class NewLabel(App):
   def build(self):
      # Label text to be edited
      lbl = Label(text ="Hello Label Text ! ")
      return lbl

NewLabel().run()