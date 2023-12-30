import mysql.connector
import tkinter as tk
from tkinter import ttk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from scipy.interpolate import make_interp_spline
import matplotlib.dates as mdates
import numpy as np

# Replace these with your actual MySQL database credentials
db_config = {
    'host': 'localhost',
    'user': 'root',
    'password': 'hafizalihamza9',
    'database': 'soilmoisture_db',
}

# Create the main Tkinter window with a blue color theme
window = tk.Tk()
window.title("Moisture Time-Series Smooth Plots")

# Set a blue color theme
window.configure(bg='lightblue')

# Display the original data on the right side with a vertical scrollbar
text_frame = ttk.Frame(window)
text_frame.pack(side=tk.RIGHT, fill=tk.BOTH, expand=1)

# Create a Treeview widget for the last 25 entries
tree = ttk.Treeview(text_frame, columns=("Moisture", "DateTime", "ID"), show="headings")
tree.heading("Moisture", text="Moisture")
tree.heading("DateTime", text="DateTime")
tree.heading("ID", text="ID")
tree.pack(side=tk.LEFT, pady=10, fill=tk.BOTH, expand=1)

# Add a scrollbar only if it doesn't exist
scrollbar = ttk.Scrollbar(text_frame, orient=tk.VERTICAL, command=tree.yview)
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)
tree.configure(yscrollcommand=scrollbar.set)

# Configure the column to stretch
text_frame.columnconfigure(0, weight=1)

# Create a canvas for the plot of the last 25 entries
plot_frame_25 = tk.Frame(window)
plot_frame_25.pack(side=tk.TOP, fill=tk.BOTH, expand=1)

# Create a Figure and Axes for the plot of the last 25 entries
fig_25 = Figure(figsize=(8, 4), dpi=100)
ax_25 = fig_25.add_subplot(111)

# Create a canvas to display the plot of the last 25 entries
canvas_25 = FigureCanvasTkAgg(fig_25, master=plot_frame_25)
canvas_25.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)

# Create a canvas for the plot of the last 500 entries
plot_frame_500 = tk.Frame(window)
plot_frame_500.pack(side=tk.BOTTOM, fill=tk.BOTH, expand=1)

# Create a Figure and Axes for the plot of the last 500 entries
fig_500 = Figure(figsize=(8, 4), dpi=100)
ax_500 = fig_500.add_subplot(111)

# Create a canvas to display the plot of the last 500 entries
canvas_500 = FigureCanvasTkAgg(fig_500, master=plot_frame_500)
canvas_500.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)

def fetch_last_entries_and_show_smooth_plots():
    try:
        with mysql.connector.connect(**db_config) as connection:
            with connection.cursor() as cursor:
                # Execute a query to retrieve the last 25 Moisture, DateTime, and ID values
                query_25 = "SELECT Moisture, DateTime, ID FROM dht11 ORDER BY ID DESC LIMIT 39"
                cursor.execute(query_25)
                data_25 = cursor.fetchall()

                # Reverse the lists to display in chronological order
                data_25.reverse()

                # Clear existing data in the tree
                for item in tree.get_children():
                    tree.delete(item)

                # Display the new data in the tree
                for row in data_25:
                    tree.insert("", "end", values=row)

                # Convert datetime objects to numeric values
                date_numeric_25 = mdates.date2num([row[1] for row in data_25])

                # Convert lists to NumPy arrays
                date_numeric_25 = np.array(date_numeric_25)
                moisture_values_25 = np.array([row[0] for row in data_25])

                # Smooth the curve using interpolation
                spline_25 = make_interp_spline([row[2] for row in data_25], moisture_values_25, k=3)

                # Clear existing plot
                ax_25.clear()

                # Plot the smooth curve for the last 25 entries
                xnew_25 = np.linspace(min([row[2] for row in data_25]), max([row[2] for row in data_25]), 300)
                ax_25.plot(xnew_25, spline_25(xnew_25), color='b')

                ax_25.set_xlabel('ID')
                ax_25.set_ylabel('Moisture Values')

                # Set y-axis range from 0 to 100
                ax_25.set_ylim(0, 100)

                # Draw the updated plot on the canvas
                canvas_25.draw()

                # Execute a query to retrieve the last 500 Moisture, DateTime, and ID values
                query_500 = "SELECT Moisture, DateTime, ID FROM dht11 ORDER BY ID DESC LIMIT 500"
                cursor.execute(query_500)
                data_500 = cursor.fetchall()

                # Reverse the lists to display in chronological order
                data_500.reverse()

                # Convert datetime objects to numeric values
                date_numeric_500 = mdates.date2num([row[1] for row in data_500])

                # Convert lists to NumPy arrays
                date_numeric_500 = np.array(date_numeric_500)
                moisture_values_500 = np.array([row[0] for row in data_500])

                # Smooth the curve using interpolation
                spline_500 = make_interp_spline([row[2] for row in data_500], moisture_values_500, k=3)

                # Clear existing plot
                ax_500.clear()

                # Plot the smooth curve for the last 500 entries
                xnew_500 = np.linspace(min([row[2] for row in data_500]), max([row[2] for row in data_500]), 300)
                ax_500.plot(xnew_500, spline_500(xnew_500), color='r')

                ax_500.set_xlabel('ID')
                ax_500.set_ylabel('Moisture Values')

                # Set y-axis range from 0 to 100
                ax_500.set_ylim(0, 100)

                # Draw the updated plot on the canvas
                canvas_500.draw()

                # Schedule the function to run again after 5000 milliseconds (5 seconds)
                window.after(1000, fetch_last_entries_and_show_smooth_plots)

    except mysql.connector.Error as e:
        print(f"Error: {e}")

# Button to fetch last entries and show smooth plots
fetch_button = ttk.Button(window, text="Refresh Plots", command=fetch_last_entries_and_show_smooth_plots, style="TButton")
fetch_button.pack(pady=10)

# Run the Tkinter event loop
window.mainloop()