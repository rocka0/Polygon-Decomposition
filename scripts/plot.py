import matplotlib.pyplot as plt

# Read input file
with open("./input.txt", "r") as f:
    # Read the number of vertices
    n = int(f.readline())
    x = []
    y = []

    # Read the coordinates of the vertices of the original polygon
    for i in range(n):
        line = f.readline().split()
        x.append(float(line[0]))
        y.append(float(line[1]))
    # Add the first vertex to the end to close the polygon
    x.append(x[0])
    y.append(y[0])

# Plot the original polygon
plt.scatter(x, y, color="red", marker=".", zorder=2)
plt.plot(x, y, color="dimgrey", linewidth=2, zorder=1)
plt.title("Original Polygon")
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.grid(color="gray", linestyle="--", linewidth=0.5)

# Save the plot to a file
plt.savefig("polygon.png", dpi=300)

# Clear the figure
plt.clf()

# Define colors for different decompositions
colors = [
    "blueviolet",
    "dodgerblue",
    "darkkhaki",
    "lightcoral",
    "hotpink",
    "lawngreen",
    "royalblue",
    "orange",
    "green",
    "saddlebrown",
]
l = len(colors)

def make_plot(file_name):
    # Get the name of the file
    name = file_name.split(".")[0].title()

    # Read the decomposition from the file
    with open(file_name, "r") as f:
        # Clear the figure
        plt.clf()

        # Get the number of decompositions
        m = int(f.readline())

        # Plot each decomposition
        for i in range(m):
            # Get the number of vertices in the i-th decomposition
            m_i = int(f.readline())

            x_i = []
            y_i = []

            # Read the coordinates of the vertices
            for j in range(m_i):
                line = f.readline().split()
                x_i.append(float(line[0]))
                y_i.append(float(line[1]))
            # Add the first vertex to the end to close the polygon
            x_i.append(x_i[0])
            y_i.append(y_i[0])

            # Plot the i-th decomposition
            plt.fill(x_i, y_i, color=colors[i % l], alpha=0.5)
            plt.plot(x_i, y_i, color=colors[i % l], linewidth=2)

        # Plot the original polygon
        plt.scatter(x, y, color="red", marker=".", zorder=m)

        # Set the title, labels and grid
        plt.title(f"{name} Merging: {m} Polygons")
        plt.xlabel("X-axis")
        plt.ylabel("Y-axis")
        plt.grid(color="gray", linestyle="--", linewidth=0.5)

        # Save the plot to a file
        name = name.lower()
        plt.savefig(f"{name}.png", dpi=300)

# Plot the decompositions before merging
make_plot("before.txt")

# Plot the decompositions after merging
make_plot("after.txt")

# Clear the figure
plt.clf()
