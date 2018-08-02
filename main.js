var express = require('express');
var socket = require('socket.io');

// Setup for processing JSON files using fetch in the HTML
var bodyParser = require("body-parser");

//App Setup
var app = express();
var server = app.listen(4000, function(){
	console.log('Waiting on browser to connect.....')
});

//Prep for Serial Comms on the server
var SerialPort = require('serialport')
var Readline = require('@serialport/parser-readline')

//Prepare the bodyparser to handle JSON
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

//Static files in the public directory
app.use(express.static('public'));


//Respond to HTML page load with list of connected serial devices.
app.get('/ListSerialPorts', function(reg, res)
{
	SerialPort.list(function (err, ports)
	{
		ports.forEach(function(port)
		{
			console.log('Serial Port = ', port.comName);
			//var SerialPortName = port.comName;
    		res.send(JSON.stringify(ports));
  		});
	});
	
});		

//Set the serial port to the selected serial device from index.html
app.post('/SetSerialPort', function(reg, res)
{
	console.log('SetSerialPort!')
	var newport = reg.body.port;
	console.log('port', newport)
	
	var sp = new SerialPort(newport, { baudRate: 57600 });
	var parser = sp.pipe(new Readline({ delimiter: '\r\n' }));

	sp.on('open', function(){
	console.log('Serial Port Opened');  //This code is ran when data is received on the serial port
	parser.on('data', function(data){
      console.log(data);
      io.emit('scanData', (data));
  });
});

	sp.on('close', function(){
	console.log('Serial Port Closed');  //This code is ran when data is received on the serial port
	process.exit(1);  //Kill main.js when the serial device is unplugged.
});

});		

//Socket Setup
var io = socket(server);

var brightness = 0;

io.on('connection', function (socket)
{
	console.log('A browser is connected...')
	socket.on ('disconnect', function() {
		console.log('Session is disconnected')
		//process.exit(1);
	});
});

console.log("running");
