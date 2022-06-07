from tkinter import *
from tracemalloc import stop
from turtle import width
from numpy import tile
import pygame
from tkinter import filedialog

root = Tk()
root.title('MP3 Player')

# Initialize Pygame Mixer
pygame.mixer.init()

# Add Song Function
def add_song():
    song = filedialog.askopenfilename(initialdir='Music (mp3)/', title="Choose A Song", filetypes=(("mp3 Files", "*.mp3"), ))
    
    # Delete Directory & Extension
    song = song.replace("C:/Users/bryan/source/repos/Robotica/Music/mp3", "")
    song = song.replace(".mp3", "")
    
    # Add Song To Listbox
    song_box.insert(END, song)

# Play Selected Song
def play():
    song = song_box.get(ACTIVE)
    song = f'C:/Users/bryan/source/repos/Robotica/Music/mp3/{song}.mp3'
    
    pygame.mixer.music.load(song)
    pygame.mixer.music.play(loops=0)

# Stop PLaying Current Song
def stop():
    pygame.mixer.music.stop()
    song_box.select_clear(ACTIVE)

# Create PLaylist Box
song_box = Listbox(root, bg="black", fg="green", width=60, selectbackground="gray", selectforeground="black")
song_box.pack(pady=20)

# Create Player Control Button Pictures
back_btn_img = PhotoImage(file='Pictures (png)/fast_backward.png')
forward_btn_img = PhotoImage(file='Pictures (png)/fast_forward.png')
play_btn_img = PhotoImage(file='Pictures (png)/play.png')
pause_btn_img = PhotoImage(file='Pictures (png)/pause.png')
stop_btn_img = PhotoImage(file='Pictures (png)/stop.png')

# Create Player Control Frame
controls_frame = Frame(root)
controls_frame.pack()

# Create Player Control Buttons
play_btn = Button(controls_frame, image=play_btn_img, borderwidth=0, command=play)
stop_btn = Button(controls_frame, image=stop_btn_img, borderwidth=0, command=stop)

play_btn.grid(row=0, column=2, padx=10)
stop_btn.grid(row=0, column=4, padx=10)

# Create Menu
my_menu = Menu(root)
root.config(menu=my_menu)

# Add 'Add Song' Menu
add_song_menu = Menu(my_menu)
my_menu.add_cascade(label="Add Songs", menu=add_song_menu)
add_song_menu.add_command(label="Add 1 Song To Playlist", command=add_song)

root.mainloop()