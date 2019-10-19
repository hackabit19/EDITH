import serial
import time
import math
import cv2


back = cv2.imread('black.jpg', 1)

ser = serial.Serial('COM3',115200,timeout = 1) #object for taking lidar readings via serial communication

bot = serial.Serial('COM11', 9600, timeout =1 ) #object for bot
 
ser.write(0x42) # insturctions for lidar working
ser.write(0x57)
ser.write(0x02)
ser.write(0x00)
ser.write(0x00)
ser.write(0x00)
ser.write(0x01)
ser.write(0x06)

while(True):
    while(ser.in_waiting >= 9):
        #print "a"
        if(('Y' == ser.read()) and ('Y' == ser.read())): # lidar sensor readings via serial communication

            Dist_L = ser.read()
            Dist_H = ser.read()
            r = (ord(Dist_H) * 256) + (ord(Dist_L)) # converting distance from hex to dec
            for i in range (0,5):
                 ser.read()
        print (r)


        angle = bot.readline()        #servo angle 
        k = bytearray(angle,'utf-8')
        k=int(k)
        k=float(k)
        x = math.cos(k) 
        y = r * math.sin(k)
        x=r*x
        print(x,y)


        encx = bot.readline()
        encx = bytearray(encx, 'utf-8') # x coordinate of bot

        ency = bot.readline()
        ency = bytearray(ency, 'utf-8') # y coordinate of bot


        for i in range (0,100,2):
            cv2.line(bck, (x,y), (encx,ency), [0,0,255], thickness=2)
            cv2.imshow("Image",bck)
            time.sleep(0.1)
            cv2.waitKey(300)
            cv2.destroyAllWindows()
        




   





