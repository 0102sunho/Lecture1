
class Vector:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        sum_x = self.x + other.x
        sum_y = self.y + other.y
        return Vector(sum_x, sum_y)

    def __sub__(self, other):
        sub_x = self.x - other.x
        sub_y = self.y - other.y
        return Vector(sub_x, sub_y)

    def __mul__(self, scalar):
        mul_x = self.x * scalar
        mul_y = self.y * scalar
        return Vector(mul_x, mul_y)

    def __eq__(self, other):
        if self.x == other.x and self.y == other.y:
            return True
        else:
            return False

    def __str__(self):
        return '('+str(self.x)+', '+str(self.y)+')'

v1 = Vector(1,2 )
v2 = Vector(3, 4)

print (v1+v2, v1-v2, v1==v2)