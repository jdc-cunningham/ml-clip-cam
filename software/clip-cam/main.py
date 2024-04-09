from threading import Thread
from video.video import Video
from control.control import Control

import time

control = Control()
video = Video(control)

control.send_to_esp32('ready')

def start():
  while True:
    msg = control.read().decode('utf-8').replace('\r\n', '') # msg from ESP32

    if (msg):
      video.msg = msg

    time.sleep(0.05)

Thread(target=video.handle_msg).start()
Thread(target=start).start()
