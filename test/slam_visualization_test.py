import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from matplotlib.widgets import Button

# Set up serial port (adjust port name and baudrate according to your setup)
SERIAL_PORT = 'COM13'  # Change this to your Teensy port
BAUD_RATE = 9600  # Make sure the Teensy sends data at this baud rate

# Initialize serial connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

# Lists to store coordinates and angles
x_coords = []
y_coords = []
angles = []  # List to store angles (headings)

# Set up the plot
fig, ax = plt.subplots()
line, = ax.plot([], [], 'bo-', markersize=5)
ax.set_title("Real-time Path Display")
ax.set_xlabel("X Coordinates")
ax.set_ylabel("Y Coordinates")

# Text object to display the angle (heading)
angle_text = ax.text(0.05, 0.95, '', transform=ax.transAxes, fontsize=12, verticalalignment='top')

# Function to dynamically update the plot limits based on incoming data
def adjust_limits(x, y):
    """Adjust plot limits based on new data, ensuring equal scaling"""
    x_min, x_max = min(x_coords), max(x_coords)
    y_min, y_max = min(y_coords), max(y_coords)
    
    # Find the maximum range for equal scaling
    x_range = x_max - x_min
    y_range = y_max - y_min
    max_range = max(x_range, y_range)
    
    # Set both axes to have the same range
    ax.set_xlim(x_min - max_range * 0.1, x_max + max_range * 0.1)  # Add 10% margin
    ax.set_ylim(y_min - max_range * 0.1, y_max + max_range * 0.1)  # Add 10% margin
    ax.set_aspect('equal', adjustable='box')  # Ensure equal scaling

def update_plot(frame):
    """Update plot with new coordinates from serial data"""
    try:
        # Read new data from serial (expects "angle,x,y" format)
        data = ser.readline().decode('utf-8').strip()
        if data:
            # Split the data into angle, x, and y coordinates
            angle, x, y = map(float, data.split(','))
            x_coords.append(x)
            y_coords.append(y)
            angles.append(angle)

            # Update plot limits dynamically
            adjust_limits(x, y)

            # Update the plot with the new points
            line.set_data(x_coords, y_coords)

            # Update the angle (heading) text on the plot
            angle_text.set_text(f'Heading: {angle:.2f}°')

    except Exception as e:
        print(f"Error reading from serial: {e}")

    return line, angle_text  # Return both the line and angle text to update

def reset_data(event):
    """Reset the coordinate arrays and update the plot"""
    global x_coords, y_coords, angles
    x_coords = []
    y_coords = []
    line.set_data([], [])  # Clear the plot
    plt.draw()  # Redraw the plot

# Create a reset button
reset_ax = plt.axes([0.8, 0.01, 0.1, 0.075])  # Position of the button on the plot
reset_button = Button(reset_ax, 'Reset')
reset_button.on_clicked(reset_data)

# Create animation to update plot
ani = FuncAnimation(fig, update_plot, blit=True, interval=100)  # Update every 100ms

# Show the plot
plt.show()

# Close serial connection when the program ends
ser.close()
