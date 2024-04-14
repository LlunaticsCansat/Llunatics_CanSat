from serial import Serial
from tkinter import *
from tkinter import Frame, Label
import threading
from threading import Thread
import tkinter as tk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np
from datetime import datetime


        
class GUI(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Llunatics GUI")
        
        self.sat_frame = Frame(self)
        self.sat_frame.grid(row=0, column=0)


        self.create_labels()
        self.create_plots()
        self.created_file = False
        self.startLoop()
                    
    
    def create_labels(self):
        Label(self.sat_frame,text="Time (ms): ").grid(row=0,column=0,sticky=E)
        self.time_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.time_var).grid(row=0,column=1)
        
        Label(self.sat_frame,text="Temperature (Cº): ").grid(row=1,column=0,sticky=E)
        self.temperature_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.temperature_var).grid(row=1,column=1)
        
        Label(self.sat_frame,text="Pressure (Pa): ").grid(row=2,column=0,sticky=E)
        self.pressure_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.pressure_var).grid(row=2,column=1)
        
        Label(self.sat_frame,text="Altitude (m): ").grid(row=3,column=0,sticky=E)
        self.altitude_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.altitude_var).grid(row=3,column=1)
        
        Label(self.sat_frame,text="Acc X (m/s^2): ").grid(row=4,column=0,sticky=E)
        self.accX_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.accX_var).grid(row=4,column=1)

        Label(self.sat_frame,text="Acc Y (m/s^2): ").grid(row=5,column=0,sticky=E)
        self.accY_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.accY_var).grid(row=5,column=1)

        Label(self.sat_frame,text="Acc Z (m/s^2): ").grid(row=6,column=0,sticky=E)
        self.accZ_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.accZ_var).grid(row=6,column=1)
        
        Label(self.sat_frame,text="Velocity Rotation X (deg/s): ").grid(row=7,column=0,sticky=E)
        self.wX_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.wX_var).grid(row=7,column=1)
        
        Label(self.sat_frame,text="Velocity Rotation Y (deg/s): ").grid(row=8,column=0,sticky=E)
        self.wY_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.wY_var).grid(row=8,column=1)

        Label(self.sat_frame,text="Velocity Rotation Z (deg/s): ").grid(row=9,column=0,sticky=E)
        self.wZ_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.wZ_var).grid(row=9,column=1)

        Label(self.sat_frame,text="Magnetic Field X (µT): ").grid(row=10,column=0,sticky=E)
        self.magX_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.magX_var).grid(row=10,column=1)
        
        Label(self.sat_frame,text="Magnetic Field Y (µT): ").grid(row=11,column=0,sticky=E)
        self.magY_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.magY_var).grid(row=11,column=1)
        
        Label(self.sat_frame,text="Magnetic Field Z (µT): ").grid(row=12,column=0,sticky=E)
        self.magZ_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.magZ_var).grid(row=12,column=1)
        


        Label(self.sat_frame,text="Yaw (deg)").grid(row=13,column=0,sticky=E)
        self.yaw_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.yaw_var).grid(row=13,column=1)
        
        Label(self.sat_frame,text="Pitch (deg)").grid(row=14,column=0,sticky=E)
        self.pitch_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.pitch_var).grid(row=14,column=1)

        Label(self.sat_frame,text="Roll (deg)").grid(row=15,column=0,sticky=E)
        self.roll_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.roll_var).grid(row=15,column=1)



        Label(self.sat_frame,text="Latitude: ").grid(row=16,column=0,sticky=E)
        self.latitude_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.latitude_var).grid(row=16,column=1)
        
        Label(self.sat_frame,text="Longitude: ").grid(row=17,column=0,sticky=E)
        self.longitude_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.longitude_var).grid(row=17,column=1)

        Label(self.sat_frame,text="Rectenna Voltage (mV): ").grid(row=18,column=0,sticky=E)
        self.voltage_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.voltage_var).grid(row=18,column=1)
        
        Label(self.sat_frame,text="Cansat Brightness: ").grid(row=19,column=0,sticky=E)
        self.brightness_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.brightness_var).grid(row=19,column=1)

        
    def create_plots(self):
        self.fig, (self.ax_temp, self.ax_pressure, self.ax_altitude) = plt.subplots(3, 1, figsize=(10, 8))
        self.canvas = FigureCanvasTkAgg(self.fig, master=self)
        self.canvas.get_tk_widget().grid(row=0, column=4)
        
        # Customize subplots
        self.ax_temp.set_ylabel("Temperature (Cº)")
        self.ax_temp.set_title("Time - Temperature")

        self.ax_pressure.set_ylabel("Pressure (Pa)")
        self.ax_pressure.set_title("Time - Pressure")

        self.ax_altitude.set_xlabel("Time (s)")
        self.ax_altitude.set_ylabel("Altitude (m)")
        self.ax_altitude.set_title("Time - Altitude")
        
    def startLoop(self):
        thread = Thread(target=self.update_data)
        thread.daemon = True
        thread.start()

    def update_data(self):
        ser = Serial("COM6", 9600, timeout=0.01)
        ser.reset_input_buffer()
        
        self.time_data, self.temp_data, self.pressure_data, self.altitude_data = [], [], [], []

        while True:
            val = ser.readline().decode("utf-8").strip()
            if val.startswith("Llunatics"):
                pharsed = val.split(",")
                
                self.time_var.set(pharsed[1])
                self.temperature_var.set(pharsed[2])
                self.pressure_var.set(pharsed[3])
                self.altitude_var.set(pharsed[4])
                self.accX_var.set(pharsed[5])
                self.accY_var.set(pharsed[6])
                self.accZ_var.set(pharsed[7])
                self.wX_var.set(pharsed[8])
                self.wY_var.set(pharsed[9])
                self.wZ_var.set(pharsed[10])
                self.magX_var.set(pharsed[11])
                self.magY_var.set(pharsed[12])
                self.magZ_var.set(pharsed[13])
                self.yaw_var.set(pharsed[14])
                self.pitch_var.set(pharsed[15])
                self.roll_var.set(pharsed[16])
                self.latitude_var.set(pharsed[17])
                self.longitude_var.set(pharsed[18])
                self.voltage_var.set(pharsed[19])
                self.brightness_var.set(pharsed[20])
                
                # Append data for plotting
            
                self.time_data.append(float(pharsed[1])/1000)
                self.temp_data.append(float(pharsed[2]))
                self.pressure_data.append(float(pharsed[3]))
                self.altitude_data.append(float(pharsed[4]))
                
                # Update plots
                self.ax_temp.clear()
                self.ax_temp.plot(self.time_data, self.temp_data, label="Temperature (ºC)", color="blue")
                self.ax_temp.legend()

                self.ax_pressure.clear()
                self.ax_pressure.plot(self.time_data, self.pressure_data, label="Pressure (Pa)", color="orange")
                self.ax_pressure.legend()

                self.ax_altitude.clear()
                self.ax_altitude.plot(self.time_data, self.altitude_data, label="Altitude (m)", color="green")
                self.ax_altitude.legend()

                self.fig.tight_layout()
                self.canvas.draw()
                
                # Save datas
                if self.created_file == False:
                    date_time_now = datetime.now()
                    date = date_time_now.strftime("%d/%m/%Y %H:%M:%S")
                    file_name = date_time_now.strftime("%d_%m_%Y_%H_%M_%S")
                    
                    with open(f"{file_name}.csv", "w") as my_file:
                        my_file.write("time,temperature,pressure,altitude,accelerationX,accelerationY,accelerationZ,velocityRotationX,velocityRotationY,velocityRotationZ,magneticFieldX,magneticFieldY,magneticFieldZ,yaw,pitch,roll,latitude,longitude,rectennaVoltage,cansatBrightness")
                    with open(f"{file_name}.txt", "w") as my_file:
                        my_file.write("time,temperature,pressure,altitude,accelerationX,accelerationY,accelerationZ,velocityRotationX,velocityRotationY,velocityRotationZ,magneticFieldX,magneticFieldY,magneticFieldZ,yaw,pitch,roll,latitude,longitude,rectennaVoltage,cansatBrightness")

                    self.created_file = True

                with open(f"{file_name}.csv", "a") as my_file:
                    my_file.write(val)
                    my_file.write("\n")
                
                with open(f"{file_name}.txt", "a") as my_file:
                    my_file.write(val)
                    my_file.write("\n")

 


if __name__ == "__main__":
    app = GUI()
    w = app. winfo_screenwidth()
    h = app.winfo_screenheight()
    app. geometry ("%dx%d" %(w, h))
    app.mainloop()