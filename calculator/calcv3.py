import tkinter as tk
import math

class Calculator:
    def __init__(self, root):
        self.root = root
        self.root.title("Calculator")

        self.entry = tk.Entry(root, width=30
        , borderwidth=5)
        self.entry.grid(row=0, column=0, columnspan=4)

        self.buttons = [
            '7', '8', '9', '/',
            '4', '5', '6', '*',
            '1', '2', '3', '-',
            '0', '.', '=', '+',
            'sin', 'cos', 'log', 'ln',
            'History'
        ]

        row_val = 1
        col_val = 0

        for button in self.buttons:
            if button == '=':
                tk.Button(root, text=button, padx=30
                , pady=30
                , command=self.calculate).grid(row=row_val, column=col_val)
            elif button in ('sin', 'cos', 'log', 'ln'):
                tk.Button(root, text=button, padx=30
                , pady=30
                , command=lambda button=button: self.trig_log_function(button)).grid(row=row_val, column=col_val)
            elif button == 'History':
                tk.Button(root, text=button, padx=30
                , pady=30
                , command=self.open_new_window).grid(row=row_val, column=col_val)
            else:
                tk.Button(root, text=button, padx=30
                , pady=30
                , command=lambda button=button: self.button_click(button)).grid(row=row_val, column=col_val)
            col_val += 1
            if col_val > 3:
                col_val = 0
                row_val += 1

        clear_button = tk.Button(root, text="Clear", padx=30
        , pady=30
        , command=self.clear)
        clear_button.grid(row=row_val, column=col_val, columnspan=2)

        self.history = []  # Initialize an empty list for history log

    def button_click(self, value):
        current = self.entry.get()
        self.entry.delete(0, tk.END)
        self.entry.insert(0, current + str(value))

    def clear(self):
        self.entry.delete(0, tk.END)

    def calculate(self):
        current = self.entry.get()
        try:
            result = eval(current)
            self.history.append(current + ' = ' + str(result))  # Add calculation to history log
            self.entry.delete(0, tk.END)
            self.entry.insert(0, result)
        except:
            self.entry.delete(0, tk.END)
            self.entry.insert(0, "Error")

    def trig_log_function(self, function):
        current = self.entry.get()
        try:
            if function == 'sin':
                result = math.sin(eval(current))
            elif function == 'cos':
                result = math.cos(eval(current))
            elif function == 'log':
                result = math.log10(eval(current))
            elif function == 'ln':
                result = math.log(eval(current))
            self.history.append(function + '(' + current + ') = ' + str(result))  # Add calculation to history log
            self.entry.delete(0, tk.END)
            self.entry.insert(0, result)
        except:
            self.entry.delete(0, tk.END)
            self.entry.insert(0, "Error")

    def open_new_window(self):
        new_window = tk.Toplevel(self.root)
        new_window.title("History Log")
        log_text = tk.Text(new_window, height=20, width=40)
        log_text.pack()
        log_text.insert(tk.END, "\n".join(self.history))

if __name__ == "__main__":
    root = tk.Tk()
    app = Calculator(root)
    root.mainloop()
