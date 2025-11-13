#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>


class Vector3D {

private:
    double m_x;
    double m_y;
    double m_z;

public:
    // Stream output declaration (friend function for printing)
    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v);

    // Declaration of the "magnitude" function
    double magnitude() const;

    // TODO: Write the declaration of the parameterized constructor.
    Vector3D(double x, double y, double z);

    // TODO: Declare the "innerProduct" function with friend access.
    // - Parameters: two Vector3D references, v1 and v2.
    // - Returns: a double-type scalar.
    friend double innerProduct(const Vector3D& v1, const Vector3D& v2);
    

    // TODO: Declare the "crossProduct" function with friend access.
    // - Parameters: two Vector3D references, v1 and v2.
    // - Returns: a new Vector3D object.
	friend Vector3D crossProduct(const Vector3D& v1, const Vector3D& v2);

};

#endif // VECTOR3D_H
