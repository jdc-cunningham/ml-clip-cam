
from threading import Thread
from websocket.websocket import WebSocket
from video.video import Video
from ap.ap import AP

ap = AP()
video = Video()
socket = WebSocket(video)

Thread(target=ap.start).start()
Thread(target=socket.start).start()