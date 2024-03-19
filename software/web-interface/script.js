let piSocket = null;
let piSocketInterval = null;

const connectToPiZero2 = () => {
  piSocket = new WebSocket('ws://localhost:5678'); // localhost

  // connection opened, send messages to robot
  piSocket.addEventListener('open', function (event) {
    socketStatus.innerText = 'socket connected';
    updateFileCount();

    console.log('pi connected');
    piSocket.send('Hello robot!');
 
    // keep connection to esp01 alive
    piSocketInterval = setInterval(() => {
      piSocket.send('poll');
    }, 1000);
  });
 
  // listen for messages from robot
  piSocket.addEventListener('message', function (event) {
    const robotMsg = event.data;

    if (robotMsg.includes('file count: ')) {
      fileCountDisp.innerText = `File count: ${robotMsg.split(': ')[1]}`;
    }

    console.log(robotMsg);
  });
 
  piSocket.addEventListener('close', function (event) {
    socketStatus.innerText = 'socket disconnected';
    console.log('pi connection lost');
    clearInterval(piSocketInterval);
    connectToPiZero2();
 });
}

connectToPiZero2();

let recording = false;
let recordTimeSecs = 0;
let recordingInterval;

const socketStatus = document.getElementById('socket-status');
const recordBtn = document.getElementById('record-btn');
const timeDisp = document.getElementById('time-elapsed');
const fileCountDisp = document.getElementById('file-count');

const updateFileCount = () => {
  piSocket.send('get-file-count');
}

const startClock = () => {
  if (recording) {
    recordingInterval = setInterval(() => {
      recordTimeSecs += 1;
      timeDisp.innerText = `${recordTimeSecs} + seconds`; // can prettify later
    }, 1000);
  } else {
    clearInterval(recordingInterval);
    timeDisp.innerText = '0:00';
    updateFileCount();
  }
}

recordBtn.addEventListener('click', () => {
  recording = !recording;

  piSocket.send(recording ? 'record' : 'stop');

  startClock();
});