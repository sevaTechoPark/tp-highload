Simple HTTP Server
=====================

## Requirements ##

* Respond to `GET` with status code in `{200,404}`
* Respond to `HEAD` with status code in `{200,404}`
* Respond to all other request methods with status code `405`
* Directory index file name `index.html`
* Respond to requests for `/<file>.html` with the contents of `DOCUMENT_ROOT/<file>.html`
* Requests for `/<directory>/` should be interpreted as requests for `DOCUMENT_ROOT/<directory>/index.html`
* Respond with the following header fields for all requests:
  * `Server`
  * `Date`
  * `Connection`
* Respond with the following additional header fields for all `200` responses to `GET` and `HEAD` requests:
  * `Content-Length`
  * `Content-Type`
* Respond with correct `Content-Type` for `.html, .css, js, jpg, .jpeg, .png, .gif, .swf`
* Respond to percent-encoding URLs
* Correctly serve a 2GB+ files
* No security vulnerabilities

## Testing environment ##

* Put `Dockerfile` to web server repository root
* Prepare docker container to run tests:
  * Read config file `/etc/httpd.conf`
  * Expose port 80

Config file spec:
```
listen 80         # port number
cpu_limit 4       # maximum CPU count to use (for non-blocking servers)
thread_limit 256  # maximum simultaneous connections (for blocking servers)
document_root /var/www/html
```

Run tests:
```
git clone https://github.com/init/http-test-suite.git
cd http-test-suite
./httptest.py
```

## Success criteria ##

* Must pass test suite
* Must pass load test
* Must use all CPUs
* Perfomance must inrease with increasing number of CPUs
* Perfomance must be comparable with nginx (same order of magnitude)
* No errors allowed

## acquired skills
* For testing at an early stage
  * curl http://localhost:8000/hello/world
  * telnet localhost 8000
* Stop the server:
 ```
 sudo kill $(sudo lsof -t -i:8000)
 ```
* Check the server run:
```
sudo netstat -lnp | grep 8000
```
* Test performance:
```
ab -n 100000 -c 100 localhost:1996/httptest/wikipedia_russia.html
```
* Profile:
```
    g++ src/*.cpp -pg -lboost_thread -lboost_filesystem -std=c++14 -lboost_system -o httpd
    and programm must stop itself, then
    ./httpd
    gprof a.out gmon.out > analysis.txt
    
```
# Build and run
* ```
  cmake .
  make
  ./httpd
  ```
* ```
    g++ src/*.cpp --lboost_thread -lboost_filesystem -std=c++14 -lboost_system -o httpd
    ./httpd
  ```
To use post < 1234 ```sudo ./httpd```
Nginx:
```
sudo nginx -c ~/dev/technopark/highload/nginx/nginx.conf
service nginx start
```
change worker_processes in nginx.conf to use CPU cores
Docker:
```
docker build -t papadyk-httpd https://github.com/sevaTechoPark/tp-highload
```
