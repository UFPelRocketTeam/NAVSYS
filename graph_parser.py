import socket
import serial
import time
import sys
import thread
import getopt

z1baudrate = 115200
z1port = '/dev/ttyACM0'

sampling_t = []
sampling_data = []

# logger, escreve pro arquivo on time

def serial_logger():
	z1serial = serial.Serial(port=z1port, baudrate=z1baudrate)
	z1serial.timeout = 2

	print z1serial.is_open
	if z1serial.is_open:
		L = []
		thread.start_new_thread(input_thread, (L,))
		f = open('out.csv', 'w')
		while True:
			size = z1serial.inWaiting()
			if size:
				new_data = str(z1serial.read(size))
				f.write(new_data)
				print new_data

			else:
				print ("STDBY")
			if L: 
				z1serial.close()
				f.close()
				break
	return;



def input_thread(L):
	pudim = raw_input()
	L.append(pudim)

#essa merda tem que funcionar
def main(argv):
	try:
		opts, args = getopt.getopt(argv,"wd", ["wireless","debug"])
	except getopt.GetoptError:
		print 'test.py -w --wireless or -d --debug'
		sys.exit(2)
	for opt, arg in opts:
		if opt in ("-w", "--wireless"):
			internet_logger()
			sys.exit()
		elif opt in ("-d", "--debug"):
			serial_logger()
			sys.exit()


#esse pedaco aqui n sei pqq serve 
if __name__ == "__main__":
	main(sys.argv[1: ])