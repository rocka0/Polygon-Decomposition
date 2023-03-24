import pandas as pd
import matplotlib.pyplot as plt
import math

df = pd.read_csv("../plotData/firstPlot.csv")
x = df["Number_Of_Vertices"].tolist()
y = df["Running_Time_In_Microseconds"].tolist()
plt.plot(x, y)
plt.title("Running time vs Number of vertices")
plt.xlabel("Number of vertices")
plt.ylabel("Running time in microseconds")
plt.savefig("../img/analysis/RunningTime_vs_N.png")
plt.close()

df = pd.read_csv("../plotData/secondPlot.csv")
x = df["Number_Of_Vertices"].tolist()
y1 = df["Number_Of_Polygons_Before_Merging"].tolist()
y2 = df["Number_Of_Polygons_After_Merging"].tolist()
plt.plot(x, y1, label="Number of polygons before merging")
plt.plot(x, y2, label="Number of polygons after merging")
plt.title("Number of polygons after decomposition vs Number of vertices")
plt.legend()
plt.savefig("../img/analysis/Before_and_After_Merge_vs_N.png")
plt.close()
