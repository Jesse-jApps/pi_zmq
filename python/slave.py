import zmq 
import tasks 

context = zmq.Context() 
pull_socket = context.socket(zmq.PULL) 
pull_socket.connect('tcp://127.0.0.1:5001')

push_socket = context.socket(zmq.PUSH)
push_socket.connect('tcp://127.0.0.1:5002')

count = 0;

while True: 
	try: 
		task_data = pull_socket.recv_json()
		task = task_data.pop('task') 
		task_kwargs = task_data.pop('task_kwargs')

		result = getattr(tasks, task)(**task_kwargs)
		count = count + 1
		print result
		print count

		push_socket.send_json({"result" : result})

	except Exception, e: 
		print e

pull_socket.close() 
push_socket.close() 
context.term()
