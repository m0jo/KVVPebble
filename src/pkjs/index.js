// Listen for when the watchface is opened
// Durlacher tor https://live.kvv.de/webapp/departures/bystop/de:8212:3102?maxInfos=10&key=377d840e54b59adbe53608ba1aad70e8&_=1503921716334
// Hagsfeld      https://live.kvv.de/webapp/departures/bystop/de:8212:3?maxInfos=10&key=377d840e54b59adbe53608ba1aad70e8&_=1503764256683
// Kronenplatz   https://live.kvv.de/webapp/departures/bystop/de:8212:80?maxInfos=10&key=377d840e54b59adbe53608ba1aad70e8&_=1503921716337
Pebble.addEventListener('ready', 
  function(e) {
    console.log('PebbleKit JS ready!');
  }
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
  function(e) {
    console.log('Received stopID: '+e.payload[0]);
    getTrains(e.payload[0]);
  }                     
);

function sendToWatch(data){
  Pebble.sendAppMessage(data,
    function(e) {
      console.log('Sent to Pebble successfully!');
    },
    function(e) {
      console.log('Error sending to Pebble!');
    }
  );
}

function getTrains(stopid){
  var xml =  new XMLHttpRequest();
  if (xml) {
    xml.onload = function(){
      var response = this.responseText;
      console.log(response);
      for(var i=0;i<10;i++)
        sendToWatch(JSON.parse(response)["departures"][i]);
    }
    xml.open('GET', 'https://live.kvv.de/webapp/departures/bystop/de:8212:'+stopid+'?maxInfos=10&key=377d840e54b59adbe53608ba1aad70e8&_=1503764256683', true);
    xml.send();
  }
}