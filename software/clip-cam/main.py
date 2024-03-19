
from threading import Thread
from websocket.websocket import WebSocket

# update_camera_values from videostream
socket = WebSocket()

Thread(target=socket.start).start()