#!/usr/bin/python

from secrets import randbelow


def randInt(a, b):
    """
    Returns a random integer between a and b inclusive.

    Parameters:
    a (int): Lower bound of the range (inclusive).
    b (int): Upper bound of the range (inclusive).

    Returns:
    A random integer between a and b (inclusive).
    """
    assert a <= b
    return randbelow(b - a + 1) + a


def orientation(p1, p2, p3):
    """
    Returns the orientation of the points (p1, p2, p3), that is the angle between the vector (p2-p1)
    and vector (p3-p1).

    Parameters:
    p1 (tuple): The first point.
    p2 (tuple): The second point.
    p3 (tuple): The third point.

    Returns:
    The cross product of vector (p2-p1) and (p3-p1).
    """
    a = (p2[0] - p1[0], p2[1] - p1[1])
    b = (p3[0] - p1[0], p3[1] - p1[1])
    return a[0] * b[1] - b[0] * a[1]


def polygonFromPoints(points):
    """
    Returns a simple polygon from a collection of points.

    Parameters:
    points ([int]): The input point set.

    Returns:
    The vertex list of polygon sorted in clockwise order.
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
    """
    Generates a random simple polygon and prints its vertex list in clockwise order.

    Returns:
    0 upon successful execution.
    """
    n = randInt(3, 100)

    BOUND = 1000

    points = []
    chosen = set([])

    for _ in range(n):
        point = (randInt(0, BOUND), randInt(0, BOUND))
        while point in chosen:
            point = (randInt(0, BOUND), randInt(0, BOUND))
        chosen.add(point)
        points.append(point)

    polygon = polygonFromPoints(points)

    print(str(n))
    print("\n".join([f"{x[0]} {x[1]}" for x in polygon]))

    return 0


if __name__ == "__main__":
    main()
