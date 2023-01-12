import tkinter as tk
import numpy as np
import tensorflow as tf
from keras.models import load_model
import requests
import json
put_header = {'Content-Type': 'application/json'}
r1 = requests.get('https://blr1.blynk.cloud/external/api/get?token=4NFZzThvWfDpS65W2AQ3XXczD-kTYa0K&v3&v6&v6&v10&v5',put_header)
print(r1.text)
response = json.loads(r1.text)
print(type(response))
L = []
for i in response:
    L.append(float(response[i]))
print(L)
# response_list = response.split(',')
# values = [item.split(':')[1] for item in response_list]
# print(values)


arr = np.zeros((1,9))
fields = 'MEDICATION', 'COLD', 'COUGH', 'ACIDIOUS'

def fetch(entries):
    i = 0
    for entry in entries:
        field = entry[0]
        text  = entry[1].get()
        print(int(text))
        arr[0][i] = int(text)
        i = i + 1
    # print(arr)

    arr[0][4] = L[0]
    arr[0][5] = L[1]
    arr[0][6] = L[1]
    arr[0][7] = L[2]
    arr[0][8] = L[3]
    print(arr)
    model = load_model("Apna_Model.h5")
    d = model.predict(arr)
    a = np.argmax(d , axis = 1 )
    print(a)


def makeform(root, fields):
    entries = []
    for field in fields:
        row = tk.Frame(root)
        lab = tk.Label(row, width=15, text=field, anchor='w')
        ent = tk.Entry(row)
        row.pack(side=tk.TOP, fill=tk.X, padx=5, pady=5)
        lab.pack(side=tk.LEFT)
        ent.pack(side=tk.RIGHT, expand=tk.YES, fill=tk.X)
        entries.append((field, ent))
    return entries

if __name__ == '__main__':
    root = tk.Tk()
    root.geometry("750x250")
    ents = makeform(root, fields)
    root.bind('<Return>', (lambda event, e=ents: fetch(e)))
    b1 = tk.Button(root, text='ENTER',
                  command=(lambda e=ents: fetch(e)))
    b1.pack(side=tk.LEFT, padx=5, pady=5)
    b2 = tk.Button(root, text='Quit', command=root.quit)
    b2.pack(side=tk.LEFT, padx=5, pady=5)
    root.mainloop()