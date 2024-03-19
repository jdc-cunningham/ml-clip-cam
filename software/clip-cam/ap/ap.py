import subprocess
import time

class AP():
  def __init__(self):
    # you could put this in a .env file
    # no way to stop this unless reboot
    # need thread so not blocking
    print('ap')

  def start():
    cmd = "sudo nmcli device wifi hotspot ssid rpi_wifi password 1234test"

    # https://stackoverflow.com/questions/52231021/execute-shell-command-using-python-subprocess
    subprocess.Popen(cmd, stdout = subprocess.PIPE, shell = True)

    while True():
      print('ap running')
      time.sleep(1)