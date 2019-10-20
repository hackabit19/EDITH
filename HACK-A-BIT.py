import serial
import time
import math
import cv2
import matplotlib.pyplot as plt

x1 = []
y1 = []
x2 = []
y2 = []

a = 0
v=0
bck = cv2.imread('black.jpg', 1) #background image

ser = serial.Serial('COM3',115200,timeout = 1) #object for taking lidar readings via serial communication

bot = serial.Serial('COM5', 9600, timeout = 1 ) #object for bot
 
ser.write(0x42) # insturctions for lidar working
ser.write(0x57)
ser.write(0x02)
ser.write(0x00)
ser.write(0x00)
ser.write(0x00)
ser.write(0x01)
ser.write(0x06)
a=0
while(v<200):
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


        if(r < 10000):
            x = math.cos(a) 
            y = r * math.sin(a)
            x=r*x
            print(x,y)
            x = int(x)
            y = int(y)
            x1.append(x)
            y1.append(y)



        encx = bot.readline()

        encx=encx.strip("b")
        encx=encx.rstrip()
        if (encx.isdigit() == True):
              encx = (int(encx))
              print(encx)
              x2.append(encx)

        ency = bot.readline()

        ency=ency.strip("b")
        ency=ency.rstrip()
        if (ency.isdigit() == True):
              ency = (int(ency))
              print(ency)
              y2.append(ency)
              print("*******************************")
      
        v += 1
       
        
      #   p = isinstance(x, (int, long))
      #   q = isinstance(y, (int, long))
      #   w = isinstance(encx, (int, long))
      #   z = isinstance(ency, (int, long))  

      

      #   if(p and q and w and z):                                              # method of plotting using opencv (faced some issues)
      #       cv2.line(bck, (encx,ency), (x,y), [0,0,255], thickness=2) 
      #       cv2.imshow("Image",bck)
      #       cv2.waitKey(20000)
      #       cv2.destroyAllWindows() 
           
        


for i in range (0,100):   #method of plotting using matplot lib
      A = [x1[i],x2[i]]
      B = [y1[i],y2[i]]
      plt.plot(A,B,'b')

plt.show()     
            




   





