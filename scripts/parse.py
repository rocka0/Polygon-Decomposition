M = int(input())

with open("output.txt", "w") as file:
    for _ in range(M):
        N = int(input())
        polygon = [0] * N
        for i in range(N):
            polygon[i] = tuple([int(x) for x in input().split()])
        file.write("polygon(" + ",".join([f"({x[0]}, {x[1]})" for x in polygon]) + ")")
        file.write("\n")
