import os
import time

from picamera2 import Picamera2
from picamera2.encoders import H264Encoder
from libcamera import controls

class Video():
  def __init__(self, control):
    self.picam2 = Picamera2()
    self.video_config = self.picam2.create_video_configuration(main={"size": (1920, 1080)}, controls={'FrameRate': 30})
    self. picam2.configure(self.video_config)
    self.picam2.set_controls({'AfMode': controls.AfModeEnum.Manual, 'LensPosition': 0.0})
    self.encoder = H264Encoder(10000000)
    self.recording = False
    self.recording_time = 5 * 60 # 5 mins
    self.control = control
    self.msg = ""
  
  def start_recording(self):
    if (self.recording): return

    self.recording = True
    base_path = os.getcwd()
    file_name = base_path + "/videos/" + str(time.time()) + '.h264'
    self.picam2.start_recording(self.encoder, file_name)

  def stop_recording(self):
    self.picam2.stop_recording()
    self.recording = False

  # https://stackoverflow.com/a/2632251
  def get_file_count(self):
    base_path = os.getcwd()
    capture_path = base_path + "/videos/"
    # -1 for gitkeep file
    return len([name for name in os.listdir(capture_path) if os.path.isfile(os.path.join(capture_path, name))]) - 1
  
  def handle_msg(self):
    while True:
      if (self.msg == 'start'):
        self.start_recording()
      if (self.msg == 'stop'):
        self.stop_recording()
      if (self.msg == 'file count'):
        self.control.send_to_esp32(str(self.get_file_count()) + ' files')

      self.msg = ''

      time.sleep(0.05)