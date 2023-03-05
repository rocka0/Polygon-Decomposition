import matplotlib.pyplot as plt

# create two plots
# fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(20, 10))

f = open("./input.txt", "r")
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

f.close()

# plot
plt.scatter(x, y, color="red", marker=".", zorder=2)
plt.plot(x, y, color="dimgrey", linewidth=2, zorder=1)
plt.title("Original Polygon")
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.grid(color="gray", linestyle="--", linewidth=0.5)

plt.savefig("polygon.png", dpi=300)

# Clear the figure
plt.clf()

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

try:
    f = open("./output.txt", "r")

    # number of decompositions
    m = int(f.readline())
    for i in range(m):
        # i_th decomposition
        m_i = int(f.readline())

        x_i = []
        y_i = []

        # read the coordinates
        for j in range(m_i):
            line = f.readline().split()
            x_i.append(float(line[0]))
            y_i.append(float(line[1]))
        x_i.append(x_i[0])
        y_i.append(y_i[0])

        plt.fill(x_i, y_i, color=colors[i % l], alpha=0.5)
        plt.plot(x_i, y_i, color=colors[i % l], linewidth=2)

    f.close()

    plt.scatter(x, y, color="red", marker=".", zorder=m)
    plt.title("Decompositions")
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")
    plt.grid(color="gray", linestyle="--", linewidth=0.5)
    plt.savefig("decompositions.png", dpi=300)

except FileNotFoundError:
    print("Output file name should be output.txt")

# plt.scatter(x, y, color='red', marker='x')
# fig.savefig('decompositions.png', dpi=300)
# plt.show()
