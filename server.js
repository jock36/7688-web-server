var http = require("http");
var url = require('url');
var fs = require('fs');
var io = require('socket.io');

var SerialPort = require("serialport").SerialPort
var serialPort = new SerialPort("/dev/ttyS0",
{baudrate: 57600
});

var sensor = new Array(8);

console.log('Start Program!');

var server = http.createServer(function(request, response) {
  console.log('Connection');
  var path = url.parse(request.url).pathname;

  switch (path) {
    case '/':
      response.writeHead(200, {'Content-Type': 'text/html'});
      response.write('Hello, World.');
      response.end();
      break;
    case '/socket.html':
      fs.readFile(__dirname + path, function(error, data) {
        if (error){
          response.writeHead(404);
          response.write("opps this doesn't exist - 404");
        } else {
          response.writeHead(200, {"Content-Type": "text/html"});
          response.write(data, "utf8");
        }
        response.end();
      });
      break;
    default:
      response.writeHead(404);
      response.write("opps this doesn't exist - 404");
      response.end();
      break;
  }
});

server.listen(8001);

io.listen(server);

serialPort.on("open", function () {
        receivedData ="";
        serialPort.on('data',function(data)
        {
                receivedData =data.toString();
                console.log(receivedData);

                if(receivedData.indexOf('x')>=0 &&
                        receivedData.indexOf('y')>=0 &&
                        receivedData.indexOf('z')>=0
                        ){
			sensor[0] = receivedData.substring(receivedData.indexOf('x')+1,receivedData.indexOf('y'));
			sensor[1] = receivedData.substring(receivedData.indexOf('y')+1, receivedData.indexOf('z'));
                        sensor[2] = receivedData.substring(receivedData.indexOf('z')+1, receivedData.indexOf('e'));


                }
	   if(receivedData.indexOf('a')>=0 &&
                    receivedData.indexOf('d')>=0
		){
		sensor[7] = receivedData.substring(receivedData.indexOf('a')+1, receivedData.indexOf('d'));
		}
                 if(receivedData.indexOf('t')>=0 &&
                    receivedData.indexOf('h')>=0 &&
                    receivedData.indexOf('i')>=0 &&
                    receivedData.indexOf('u')>=0
                    ){
                        sensor[3] = receivedData.substring(receivedData.indexOf('t')+1, receivedData.indexOf('h'));
                        sensor[4] = receivedData.substring(receivedData.indexOf('h')+1, receivedData.indexOf('i'));
                        sensor[5] = receivedData.substring(receivedData.indexOf('i')+1, receivedData.indexOf('u'));
                        sensor[6] = receivedData.substring(receivedData.indexOf('u')+1, receivedData.indexOf('e'));

                }

        });
});

var serv_io = io.listen(server);

serv_io.sockets.on('connection', function(socket) {
    setInterval(function() {
    socket.emit('date', {'date': new Date(),'compass_x':sensor[0],
                'compass_y':sensor[1],'compass_z':sensor[2],
                'temp':sensor[3],'humi':sensor[4],
                'ir':sensor[5],'ultra':sensor[6],'angke':sensor[7]
                });
    }, 500);

});