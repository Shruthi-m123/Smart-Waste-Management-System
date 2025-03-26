import prediction as pred
import serial
import time



out_class = pred.predict_image('captured_images\captured_image.jpg')
print(out_class)
num_class=-1
if out_class=="PS":
    num_class=1
elif out_class=="HDPE":
    num_class=2
elif out_class=="PET":
    num_class=3
elif out_class=="LDPE":
    num_class=4
elif out_class=="PP":
    num_class=5





# arduino = serial.Serial('COM7', 9600)  # 9600 is the baud rate
# time.sleep(2)  # Wait for the Arduino to initialize


# number = num_class 
# arduino.write(str(number).encode()) 

# print(f"Sent integer: {number} to Arduino")
# arduino.close()  
