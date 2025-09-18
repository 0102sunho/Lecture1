
class A:
    def hello(self):
        print("Hello from A")

class B(A):
    def hello(self):
        print("Hello from B")
        super().hello()

class C(A):
    def hello(self):
        print("Hello from C")
        super().hello()

class D(B, C):
    def hello(self):
        print("Hello from D")
        super().hello()
# 1.
class E(C):
    def hello(self):
        print("Hello from E")
        super().hello()

class F(B, E):
    def hello(self):
        print("Hello from F")
        super().hello()



# 2.
print('\n'*2)

print(F.mro())

print('\n'*2)
'''
# child before parent, left to right, inheritance order preserved
# F(B, E) -> [B, A, object] / [E, C, A, object]
### F

# B and E both not inherited to each other, B is chosen (left to right), and then E
### F -> B -> E

# [A, object] and [C, A, object] remains, C is not in the tail of A, object while A is tail of C.
### F -> B -> E -> C

# all that's left is [A, object] (x2)
### F -> B -> E -> C -> A -> object

'''

'''[<class '__main__.F'>, <class '__main__.B'>, <class '__main__.E'>, <class '__main__.C'>, <class '__main__.A'>, <class 'object'>]'''



# 3.
'''
mro conflict error happens when ordering rule conflicts itself
'''
class evil_D(C, B):
    def hello(self):
        print("Hello from evil_D")
        super().hello()

class MROerror(D, evil_D):
    def hello(self):
        print("MROerror")
        super().hello()

print(MROerror.mro())

