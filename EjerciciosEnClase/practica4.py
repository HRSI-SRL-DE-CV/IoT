"""
Author: HRSI
Curso IoT
Práctica4 - Raspberry Pi
"""
import RPi.GPIO as GPIO
import time
import curses
damn = curses.initscr()
damn.nodelay(1)
GPIO.setmode(GPIO.BCM) #Utiliza los números de pines GPIO en lugar de los físicos
GPIO.setwarnings(False)
a = True
while a:
    c = damn.getch()
    print(c)
    if (c == 27):
        a = False
    GPIO.setup(18,GPIO.OUT)
    print("Led ON")
    GPIO.output(18,GPIO.HIGH)
    time.sleep(1)
    print("Led OFF")
    GPIO.output(18,GPIO.LOW)
    time.sleep(0.5)