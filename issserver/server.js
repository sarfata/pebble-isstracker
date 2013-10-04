var express = require('express');
var http = require('http');

var app = express();

app.get('/iss/', function(req, res) {
  console.log("got request");

  console.log(JSON.stringify(req.query));

  // Get next ISS passes over Boston
  var http_request = http.get('http://api.open-notify.org/iss-pass.json?lat=42.3646&lon=-71.1028', function(http_response) {
    console.log("Status: " + http_response.statusCode);

    http_response.on('data', function(data) {
      console.log("Got and parsed reply from webservice: " + data);
      var issdata = JSON.parse(data);
      var next_passage = issdata.response[0].risetime;

      // Adjust UTC Time to Boston time
      next_passage += 5 * 3600;

      var response = {
        0: next_passage
      };
      console.log("Reply: " + JSON.stringify(response));
      res.end(JSON.stringify(response));
    });
  });
  http_request.on('error', function() {
    console.log("HTTP Request failed.");
    res.end('{ "0": -1 } ');
  });

});

app.listen(8083);
console.log("Listening on port 8083");
