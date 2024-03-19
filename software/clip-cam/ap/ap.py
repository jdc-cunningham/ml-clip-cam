import os
import time

class AP():
  def __init__(self):
    # you could put this in a .env file
    # no way to stop this unless reboot
    # need thread so not blocking
    print('ap')

  def start():
    os.system("sudo nmcli device wifi hotspot ssid rpi_wifi password 1234test")

    while True():
      print('ap running')
      time.sleep(1)