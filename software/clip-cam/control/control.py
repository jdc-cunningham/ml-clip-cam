import serial
import time

class control():
  def __init__(self, handle_msg):
    self.esp32_serial = serial.Serial(port='/dev/serial0', baudrate=115200, timeout=.01)
    self.emit = handle_msg

  def read(self):
    data = self.esp32_serial.readline()
    return data

  def write(self, msg):
    self.esp32_serial.write(bytes(msg, 'utf-8'))

  def listen(self):
    while True:
      msg = self.read()

      if (msg):
        self.emit(msg)

      time.sleep(0.05)