import serial
import time

class control():
  def __init__(self):
    self.esp32_serial = serial.Serial(port='/dev/serial0', baudrate=115200, timeout=.01)

  def read(self):
    data = self.esp32_serial.readline()
    return data

  def write(self, msg):
    self.esp32_serial.write(bytes(msg, 'utf-8'))

  def send_to_esp32(self, msg):
    self.write(msg)