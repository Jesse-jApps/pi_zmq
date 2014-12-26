import json, random
import time

# Create random Int and return if its in or out
def calculatePi(*args, **kwargs):

	r = kwargs["max"]

	x = random.randint(kwargs["min"], kwargs["max"])
	y = random.randint(kwargs["min"], kwargs["max"])

	#print x**2 + y**2, r**2

	if x**2 + y**2 < r**2:
		return 1
	return 0


def saveTime(*args, **kwargs):
	ts = time.time()

	return {kwargs["identifier"] : ts}


