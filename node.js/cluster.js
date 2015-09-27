var cluster = require('cluster');
var http = require('http');
var numCPUs = require('os').cpus().length;
//
if (cluster.isMaster) {
 cluster.fork();
 cluster.fork();
 cluster.fork();
 cluster.fork();
 cluster.fork();
 cluster.fork();
 cluster.fork();
} else {
 http.createServer(function(req, res) {
  res.writeHead(200);
  res.end(&amp;amp;quot;hello worldn&amp;amp;quot;);
 }).listen(8000);
}


