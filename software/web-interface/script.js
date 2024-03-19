let piSocket = null;
let piSocketInterval = null;

const connectToPiZero2 = () => {
  piSocket = new WebSocket('ws://192.168.1.248:5678'); // localhost

  // connection opened, send messages to robot
  piSocket.addEventListener('open', function (event) {
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

    console.log(robotMsg);
  });
 
  piSocket.addEventListener('close', function (event) {
    console.log('pi connection lost');
    clearInterval(piSocketInterval);
    connectToPiZero2();
 });
}

connectToPiZero2();

let recording = false;
let recordTimeSecs = 0;
let recordingInterval;

const recordBtn = document.getElementById('record-btn');
const timeDisp = document.getElementById('time-elapsed');

const startClock = () => {
  if (recording) {
    recordingInterval = setInterval(() => {
      recordTimeSecs += 1;
      timeDisp.innerText = `${recordTimeSecs} + seconds`; // can prettify later
    }, 1000);
  } else {
    clearInterval(recordingInterval);
    timeDisp.innerText = '0:00';
  }
}

recordBtn.addEventListener('click', () => {
  recording = !recording;

  piSocket.send(recording ? 'stop' : 'record');

  startClock();
});