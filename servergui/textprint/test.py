from kivy.app import App
from kivy.uix.boxlayout import BoxLayout

class MainWindow(BoxLayout):

    # We create a dictionary of all our possible methods to call, along with keys
    def command_dict(self):
        return {
            'one': self.command_one,
            'two': self.command_two,
            'three': self.command_three
        }

    def process_command(self):
        # We grab the text from the user text input as a key
        command_key = self.ids.fetch_key_and_process_command.text

        # We then use that key in the command's built in 'get_method' because it is a dict
        # then we store it into a variable for later use
        called_command = self.command_dict().get(command_key, 'default')

        try:
            # The variable is a method, so by adding we can call it by simple adding your typical () to the end of it.
            called_command()

        except TypeError:
            # However we use an exception clause to catch in case people enter a key that doesn't exist
            self.ids.fetch_key_and_process_command.text = 'Sorry, there is no command key: ' + command_key

    # These are the three commands we call from our command dict.
    def command_one(self):
        self.ids.fetch_key_and_process_command.text = 'Command One has Been Processed'

    def command_two(self):
        self.ids.fetch_key_and_process_command.text = 'Command Two has Been Processed'

    def command_three(self):
        self.ids.fetch_key_and_process_command.text = 'Command Three has been Processed'

class MainApp(App):

    def build(self):
        return MainWindow()

if __name__ == '__main__':
    MainApp().run()