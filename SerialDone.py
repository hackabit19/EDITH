import serial
import time
import math
import cv2

a = 0
bck = cv2.imread('black.jpg', 1) #background image

ser = serial.Serial('COM3',115200,timeout = 1) #object for taking lidar readings via serial communication

bot = serial.Serial('COM11', 9600, timeout = 1 ) #object for bot
 
ser.write(0x42) # insturctions for lidar working
ser.write(0x57)
ser.write(0x02)
ser.write(0x00)
ser.write(0x00)
ser.write(0x00)
ser.write(0x01)
ser.write(0x06)
a=0
while(True):
        #print "a"
        if(('Y' == ser.read()) and ('Y' == ser.read())): # lidar sensor readings via serial communication

            Dist_L = ser.read()
            Dist_H = ser.read()
            r = (ord(Dist_H) * 256) + (ord(Dist_L)) # converting distance from hex to dec
            for i in range (0,5):
                 ser.read()
        print (r)


        angle = bot.readline()        #servo angle   
        
        s=angle.strip("b")
        s1=s.rstrip()
        if (s1.isdigit() == True):
              a = (int(s1))
              print(a)



        x = math.cos(a) 
        y = r * math.sin(a)
        x=r*x
        print(x,y)



        encx = bot.readline()
        encx = bytearray(encx, 'utf-8') # x coordinate of bot

        ency = bot.readline()
        ency = bytearray(ency, 'utf-8') # y coordinate of bot


    
        x=int(x)
        y=int(y)
        cv2.line(bck, (x,y), (10,10), [0,0,255], thickness=2)
        cv2.imshow("Image",bck)
        # time.sleep(0.1)
        cv2.waitKey(100)
        cv2.destroyAllWindows()
        




   





