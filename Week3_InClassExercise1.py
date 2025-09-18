from abc import ABC, abstractmethod
import math

class Shape3D:
    def __init__(self, volume, surface_area):
        self.volume = volume
        self.surface_area = surface_area
    def describe(self):
        print(f"Shape3D object name: {self.__class__.__name__}")


class Cube(Shape3D):
    def __init__(self, side):
        self.side = side
        self.volume = side**3
        self.surface_area = 6 * side**2
        super().__init__(self.volume, self.surface_area)


class Sphere(Shape3D):
    def __init__(self, radius):
        self.radius = radius
        self.volume = (4/3) * 3.14 * radius**3
        self.surface_area = 4 * 3.14 * radius**2
        super().__init__(self.volume, self.surface_area)

class Cylinder(Shape3D):
    def __init__(self, radius, height):
        self.radius = radius
        self.height = height
        self.volume = 3.14 * radius**2 * height
        self.surface_area = 2 * 3.14 * radius * height + 2 * 3.14 * radius**2
        super().__init__(self.volume, self.surface_area)


shapes = [Cube(2), Sphere(3), Cylinder(2, 5)]

for s in shapes:
    s.describe()
    print("Volume:", s.volume)
    print("Surface area:", s.surface_area)
    print("---")
