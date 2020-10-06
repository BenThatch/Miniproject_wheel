# Christopher Hartsen
# EENG 350: SEED Lab
# Assignment 2, Exercise 2
# Send a string to the Audrino and display what it sends back
# Display info thru the LCD
# Connect the LCD to the Pi and
#            : Ground (GND on Arduino to pin 6 on LCD)
#            : SDA (A4 on Arduino to pin 3 on LCD)
#            : SCL (A5 on Arduino to pin 5 on LCD)

"""Simple test for I2C RGB character LCD shield kit"""
import time
import board
import busio
import adafruit_character_lcd.character_lcd_rgb_i2c as character_lcd
import smbus

# Modify this if you have a different sized Character LCD
lcd_columns = 16
lcd_rows = 2

# Initialise I2C bus.
i2c = busio.I2C(board.SCL, board.SDA)

# Initialise the LCD class
lcd = character_lcd.Character_LCD_RGB_I2C(i2c, lcd_columns, lcd_rows)

# for RPI version 1, use “bus = smbus.SMBus(0)”
bus = smbus.SMBus(1)

# This is the address we setup in the Arduino Program
address = 0x04

def writeNumber(value):
    bus.write_byte(address, value)
# bus.write_byte_data(address, 0, value)
    return -1

def readNumber():
    number = bus.read_byte(address)
# number = bus.read_byte_data(address, 1)
    return number

lcd.clear()
# Set LCD color to red
lcd.color = [100, 0, 0]

# Ask user to enter a number
lcd.message = "Enter a number: " # Display on LCD
var = input("Enter a number: ") # int enterd by user, displayed in IED
varSend = int(var) # change var from a string to an int
writeNumber(varSend)
lcd.clear()

# DIsplay enterd number on LCD and IED
lcd.message = "You enterd: " + var
print ("RPI: Hi Arduino, I sent you ", varSend)
time.sleep(1)
lcd.clear()

number = readNumber()
numberRecieve = str(number) # change number from an int to a string
lcd.message = "Now it's: " + numberRecieve
print ("Arduino: Hey RPI, I added 5 to your digit, now it's ", number)
time.sleep(1)
lcd.clear()

# Give a pleasant send off
lcd.message = "Have a nice day!"
time.sleep(1)
lcd.clear()

lcd.color = [0, 0, 0]
lcd.clear()