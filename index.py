import vlc
import time

song = 'Music (mp3)/S10 - De Diepte - Netherlands 🇳🇱 - Official Music Video - Eurovision 2022.mp3'

playSong = vlc.MediaPlayer(song)
playSong.play()
time.sleep(500)
playSong.stop()