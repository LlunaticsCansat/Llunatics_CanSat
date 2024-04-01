from serial import Serial
from tkinter import *
from tkinter import Frame, Label
import threading
from threading import Thread
import tkinter as tk
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np
        
class GUI(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Llunatics GUI")
        
        self.sat_frame = Frame(self)
        self.sat_frame.grid(row=0, column=0)


        self.create_labels()
        self.create_plots()
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
        
        Label(self.sat_frame,text="Acc X (m/s^2): ").grid(row=3,column=0,sticky=E)
        self.accX_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.accX_var).grid(row=3,column=1)

        Label(self.sat_frame,text="Acc Y (m/s^2): ").grid(row=4,column=0,sticky=E)
        self.accY_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.accY_var).grid(row=4,column=1)

        Label(self.sat_frame,text="Acc Z (m/s^2): ").grid(row=5,column=0,sticky=E)
        self.accZ_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.accZ_var).grid(row=5,column=1)
        
        Label(self.sat_frame,text="Velocity Rotation X (deg/s): ").grid(row=6,column=0,sticky=E)
        self.wX_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.wX_var).grid(row=6,column=1)
        
        Label(self.sat_frame,text="Velocity Rotation Y (deg/s): ").grid(row=7,column=0,sticky=E)
        self.wY_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.wY_var).grid(row=7,column=1)

        Label(self.sat_frame,text="Velocity Rotation Z (deg/s): ").grid(row=8,column=0,sticky=E)
        self.wZ_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.wZ_var).grid(row=8,column=1)

        Label(self.sat_frame,text="Magnetic Field X (µT): ").grid(row=9,column=0,sticky=E)
        self.magX_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.magX_var).grid(row=9,column=1)
        
        Label(self.sat_frame,text="Magnetic Field Y (µT): ").grid(row=10,column=0,sticky=E)
        self.magY_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.magY_var).grid(row=10,column=1)
        
        Label(self.sat_frame,text="Magnetic Field Z (µT): ").grid(row=11,column=0,sticky=E)
        self.magZ_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.magZ_var).grid(row=11,column=1)
        
        Label(self.sat_frame,text="Latitude: ").grid(row=12,column=0,sticky=E)
        self.latitude_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.latitude_var).grid(row=12,column=1)
        
        Label(self.sat_frame,text="Longitude: ").grid(row=13,column=0,sticky=E)
        self.longitude_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.longitude_var).grid(row=13,column=1)

        Label(self.sat_frame,text="Rectenna Intensity (mA): ").grid(row=14,column=0,sticky=E)
        self.intensity_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.intensity_var).grid(row=14,column=1)

        Label(self.sat_frame,text="Rectenna Voltage (mV): ").grid(row=15,column=0,sticky=E)
        self.voltage_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.voltage_var).grid(row=15,column=1)
        
        Label(self.sat_frame,text="Cansat Brightness: ").grid(row=16,column=0,sticky=E)
        self.brightness_var = tk.DoubleVar()
        Label(self.sat_frame,textvariable=self.brightness_var).grid(row=16,column=1)

        
    def create_plots(self):
        self.fig, (self.ax_temp, self.ax_pressure) = plt.subplots(2, 1, figsize=(12, 6))
        self.canvas = FigureCanvasTkAgg(self.fig, master=self)
        self.canvas.get_tk_widget().grid(row=0, column=5)
        
        # Customize subplots
        self.ax_temp.set_ylabel("Temperature (Cº)")
        self.ax_temp.set_title("Time vs. Temperature")
        
        self.ax_pressure.set_xlabel("Time (ms)")
        self.ax_pressure.set_ylabel("Pressure (Pa)")
        self.ax_pressure.set_title("Time vs. Pressure")
    def startLoop(self):
        thread = Thread(target=self.update_data)
        thread.daemon = True
        thread.start()

    def update_data(self):
        ser = Serial("COM10", 9600, timeout=0.01)
        ser.reset_input_buffer()
        
        time_data, temp_data, pressure_data = [], [], []

        while True:
            val = ser.readline().decode("utf-8").strip()
            if val.startswith("Llunatics"):
                pharsed = val.split(",")
                
                self.time_var.set(pharsed[1])
                self.temperature_var.set(pharsed[2])
                self.pressure_var.set(pharsed[3])
                self.accX_var.set(pharsed[4])
                self.accY_var.set(pharsed[5])
                self.accZ_var.set(pharsed[6])
                self.wX_var.set(pharsed[7])
                self.wY_var.set(pharsed[8])
                self.wZ_var.set(pharsed[9])
                self.magX_var.set(pharsed[10])
                self.magY_var.set(pharsed[11])
                self.magZ_var.set(pharsed[12])
                self.latitude_var.set(pharsed[16])
                self.longitude_var.set(pharsed[17])
                self.intensity_var.set(pharsed[18])
                self.voltage_var.set(pharsed[19])
                self.brightness_var.set(pharsed[20])
                
                # Append data for plotting
            
                time_data.append(float(pharsed[1]))
                temp_data.append(float(pharsed[2]))
                pressure_data.append(float(pharsed[3]))

                # Update plots
                self.ax_temp.clear()
                self.ax_temp.plot(time_data, temp_data, label="Temperature", color="blue")

                self.ax_pressure.clear()
                self.ax_pressure.plot(time_data, pressure_data, label="Pressure", color="orange")

                self.fig.tight_layout()
                self.canvas.draw()
    


if __name__ == "__main__":
    app = GUI()
    app.mainloop()