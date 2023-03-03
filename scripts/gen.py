#!/usr/bin/python

from random import randint


def getInt(a, b):
    """
    Returns a random integer x which lies in the range [a,b].
        Parameters:
            a (int): Lower bound
            b (int): Upper bound
        Returns:
            x (int): The random number
    """

    assert a <= b, f"getInt({a},{b}) has a > b"
    a = int(a)
    b = int(b)
    return randint(a, b)


def getPair(a, b, way=1):
    """
    Returns a random pair of integers (x,y) such that x and y lie in the range [a,b].
        Parameters:
            a (int):    Lower bound
            b (int):    Upper bound

            way (int):  Decides the ordering of the pairs:

                (way = 1) => random

                (way = 2) => strictly increasing

                (way = 3) => weakly increasing

                (way = 4) => strictly decreasing

                (way = 5) => weakly decreasing
        Returns:
            (x,y): Randomly generated pair of integers
    """

    a = int(a)
    b = int(b)
    way = int(way)

    x = getInt(a, b)

    if way == 1:
        y = getInt(a, b)
    elif way == 2:
        assert a < b, "a < b for strictly increasing"
        while x == b:
            x = getInt(a, b)
        y = getInt(x + 1, b)
    elif way == 3:
        y = getInt(x, b)
    elif way == 4:
        assert a < b, "a < b for strictly decreasing"
        while x == a:
            x = getInt(a, b)
        y = getInt(a, x - 1)
    elif way == 5:
        y = getInt(a, x)
    else:
        raise RuntimeError("Invalid way passed")

    return (x, y)


def orientation(p1, p2, p3):
    """
    Returns the orientation of the points (p1, p2, p3), that is the angle between the vector (p2-p1)
    and vector (p3-p1)
        Parameters:
            p1(tuple): Point One
            p2(tuple): Point Two
            p3(tuple): Point Three
        Returns:
            cross product of vector (p2-p1) and (p3-p1)
    """
    a = (p2[0] - p1[0], p2[1] - p1[1])
    b = (p3[0] - p1[0], p3[1] - p1[1])
    return a[0] * b[1] - b[0] * a[1]


def genPolygonFromPoint(points):
    """
    Returns a simple polygon from a collection of points
        Parameters:
            points([int]): Input point set
        Returns:
            polygon([int]): Vertex list of polygon sorted in clockwise order
    """
    points = sorted(points)

    leftMostPoint = points[0]
    rightMostPoint = points[-1]

    upperPoints = []
    lowerPoints = []

    for i in points[1:-1]:
        if orientation(leftMostPoint, rightMostPoint, i) > 0:
            upperPoints.append(i)
        else:
            lowerPoints.append(i)

    upperPoints = sorted(upperPoints)
    lowerPoints = sorted(lowerPoints)[::-1]

    polygon = [leftMostPoint] + upperPoints + [rightMostPoint] + lowerPoints

    return polygon


def main():
    n = getInt(1, 50)

    points = []

    for _ in range(n):
        x, y = getPair(1, 500)
        points.append((x, y))

    polygon = genPolygonFromPoint(points)

    with open("input.txt", "w") as file:
        file.write(str(n) + "\n")
        file.write("\n".join([f"{x[0]} {x[1]}" for x in polygon]))

    with open("inputDesmos.txt", "w") as file:
        for vertex in polygon:
            file.write(f"{vertex[0]}, {vertex[1]}\n")
        file.write(f"{polygon[0][0]}, {polygon[0][1]}")

    return 0


if __name__ == "__main__":
    main()
