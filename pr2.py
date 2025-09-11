class Temperature:

    unit = "Celsius"

    def __init__(self, value):
        self.value = value


    def display(self):
        print(self.value, Temperature.unit)

    @classmethod
    def change_unit(cls, new_unit):
        cls.unit = new_unit

    @staticmethod
    def to_fahrenheit(celsius):
        return (celsius * 9 / 5) + 32


temp = Temperature(100)
temp.display()

print(temp.to_fahrenheit(100))

temp.change_unit('Kelvin')
temp.display()




