#!/usr/bin/env python3
import serial, time
import serial.tools.list_ports

device_vid = 1155
device_pid = 22336

def list_serial_ports():
	return serial.tools.list_ports.comports()

def select_serial_port(ports=None):
	if ports == None:
		ports = list_serial_ports()
	if len(ports) == 0:
		raise RuntimeError('No serial port available')
	else:
	    devs = []
	    for dev in ports:
	        if dev.vid == device_vid and dev.pid == device_pid:
	            devs.append(dev)
	    if len(devs) == 1:
	        device = devs[0]
	    elif len(devs) == 0:
	        raise RuntimeError('Could not locate device')
	    else:
	        p = 0
	        for port in ports:
	            print(p, port)
	            p += 1
	        while True:
	            try:
	                choice = int(input('Select a port: '))
	                if choice in list(range(len(ports))):
	                    device = ports[choice]
	                    break
	            except KeyboardInterrupt:
	                raise
	            except:
	                continue
	return device.device

def main():
	ports = list_serial_ports()
	port = select_serial_port(ports)
	print('Found:', port)
	ser = serial.Serial(port)

	print("--- Sending command to jump to DFU mode")

	ser.write(b'\xDF')
	time.sleep(0.1)

	ser.close()

if __name__ == '__main__':
	main()