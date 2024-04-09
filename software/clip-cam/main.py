from threading import Thread
from video.video import Video
from control.control import Control

import time

control = Control()
video = Video(control)

def start():
  while True:
    msg = control.read() # msg from ESP32

    if (msg):
      video.handle_msg(msg)

    time.sleep(0.05)

Thread(target=start).start()
