import sys, os, numpy as np
from time import sleep
import zmq 
import json 

def main():

	ctx = zmq.Context() 
	task_socket = ctx.socket(zmq.PUSH) 
	task_socket.connect('tcp://127.0.0.1:5000') 

	y = 5

	x = 1

	#Send starttime
	task_socket.send_json({
		'task' : 'saveTime',
		'task_kwargs': {
			"identifier" : "startTime"
		}
	})

	count = 0
	while x <= y:
		task_kwargs = { 
			'min': 0, 
			'max': y
		} 
		
		task_socket.send_json({ 
			'task': 'calculatePi',
			'task_kwargs': task_kwargs
		})

		if x == y:
			task_socket.send_json({
				'task' : 'saveTime',
				'task_kwargs': {
					"identifier" : "stopTime"
				}
			})
		count = count + 1
		x = x + 1
		#sleep(0.0005)


	task_socket.close() 
	ctx.term()
	print count

	sys.exit(0)
if __name__ == "__main__":
	main()
