import pandas
import matplotlib.pyplot as plt
import numpy as np
import datetime
from matplotlib.backends.backend_pdf import PdfPages

R=8.31432 
Po=102500   #Preasure of refere (sea level)
g=9.80665
ho=0    #Altitude of reference (sea level)
M=0.0289644 

data = pandas.read_csv('test2.csv', sep = ';',)

#print(data.describe())

T= data["temp"]+273.15
preasure=data["preasure"]
data["altitude"]=-T*R*np.log(preasure/Po)/(g*M)+ho


print(data.describe())

def makeGraph(data):
    #Datos de temperatura
    y_temp = data["temp"]
    time = data["time"]/60000
    # Datos de presión
    y_pressure = data["preasure"]/100   #Hpa

    # Crear la figura y los ejes
    fig, ax1 = plt.subplots(1,1,figsize=(10,4))

    # Configurar el primer eje (temperatura)
    color = 'tab:red'
    ax1.set_xlabel('time(min)')
    ax1.set_ylabel('temperature(ºC)', color=color)
    ax1.plot(time, y_temp, color=color)
    ax1.tick_params(axis='y', labelcolor=color)

    # Crear el segundo eje (presión)
    ax2 = ax1.twinx()
    color = 'tab:blue'
    ax2.set_ylabel('pressure(Hpa)', color=color)
    ax2.plot(time, y_pressure, color=color)
    ax2.tick_params(axis='y', labelcolor=color)
    ax2.ticklabel_format(style='plain')
    ax2.ticklabel_format(useOffset=False)

    # Ajustar el diseño

    #fig.tight_layout()

    plt.title("Time/Temperature/Pressure")  # Agregar título

    plt.figure(figsize=(10, 4))
    plt.plot(time,data["altitude"])
    plt.xlabel("time(min)")  # add X-axis label
    plt.ylabel("Calculated Altitude(m)")  # add Y-axis label
    plt.title("Time/altitude")  # add title
    plt.ticklabel_format(useOffset=False)
    plt.show()

    # Mostrar la gráfica
    plt.show()
makeGraph(data)
