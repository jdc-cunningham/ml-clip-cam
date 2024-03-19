import asyncio
import websockets

class WebSocket():
  def __init__(self):
    self.socket = None

  async def recvd_msg(self, msg) -> bool:
    print(msg)

  async def socket_listener(self, socket):
    while True:
      msg = await socket.recv()
      await self.recvd_msg(msg)
      await asyncio.sleep(0.1)

  async def socket_main(self):
    async with websockets.serve(self.socket_listener, "192.168.1.248", 5678):
      await asyncio.Future()

  def start(self):
     asyncio.run(self.socket_main())
