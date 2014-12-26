import zmq 
import logging 

context = zmq.Context()
pull_socket = context.socket(zmq.PULL)
pull_socket.bind('tcp://127.0.0.1:5002')

push_socket = context.socket(zmq.PUSH)
push_socket.connect('tcp://127.0.0.1:5003')

hits = 0
tries = 0



while True:
	try:
		result = pull_socket.recv_json()["result"]

		#Assume Integer (Hit or Not <=> 1 or 0)
		try:
			hits = hits + result
		except TypeError:
			#Its not --> analyze
			#print result
			push_socket.send_json(result)
		
		tries = tries + 1
		#print 4 * hits / float(tries)
		
		#print hits, tries

	except Exception, e: 
		print e

pull_socket.close() 
push_socket.close() 
context.term()
