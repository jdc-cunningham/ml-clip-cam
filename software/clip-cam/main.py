from threading import Thread
from video.video import Video
from control.control import Control
from system.system import System

video = Video()
control = Control()
system = System(video, control)

Thread(target=system.start).start()