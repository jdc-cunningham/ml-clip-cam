
from threading import Thread
from websocket.websocket import WebSocket
from video.video import Video

# update_camera_values from videostream
video = Video()
socket = WebSocket(video)

Thread(target=socket.start).start()