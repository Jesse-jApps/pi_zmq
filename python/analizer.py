import zmq 
import logging 
import json

context = zmq.Context()
pull_socket = context.socket(zmq.PULL)
pull_socket.bind('tcp://127.0.0.1:5003')

data = {}

while True:
	try:
		data.update(pull_socket.recv_json())

		print data
	except Exception, e: 
		error_logger.error(e) 
	
pull_socket.close() 
context.term()
