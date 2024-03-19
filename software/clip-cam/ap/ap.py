import os

class AP():
  def __init__():
    # you could put this in a .env file
    # no way to stop this unless reboot
    # need thread so not blocking
    os.system("sudo nmcli device wifi hotspot ssid rpi_wifi password 1234test")