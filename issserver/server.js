var express = require('express');
var http = require('http');

var app = express();

app.post('/iss/', function(req, res) {
  console.log("got request");

  console.log(JSON.stringify(req.query));

  // Get next ISS passes over Boston
  var options = {
    hostname: 'api.open-notify.org',
    path: '/iss-pass.json?lat=42.3646&lon=-71.1028'
  };
  var http_request = http.request(options, function(http_response) {
    console.log("Status: " + http_response.statusCode);

    http_response.on('data', function(data) {
      console.log("Got and parsed reply from webservice: " + data);
      var issdata = JSON.parse(data);
      var next_passage = issdata.response[0].risetime;

      // Adjust UTC Time to Boston time
      next_passage -= 4 * 3600;

      var response = {
        0: next_passage
      };
      console.log("Reply: " + JSON.stringify(response));
      res.end(JSON.stringify(response));
    });
  });
  http_request.on('error', function(e) {
    console.log("HTTP Request failed: " + e.message);
    res.end('{ "0": -1 } ');
  });
  http_request.end();

});

app.listen(8083);
console.log("Listening on port 8083");
