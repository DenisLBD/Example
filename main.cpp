#include <iostream>
#include <cmath>
#include <string>
#include <cassert>

class Vector
{
private:

    double x, y, z;
    
public:
    
    Vector (double input_x = 0, double input_y = 0, double input_z = 0) : 
    x(input_x), y(input_y), z(input_z) {}
    
    double vec_length () // длина вектора
    {
        double length = 0;
        length = sqrt(x*x + y*y + z*z);
        
        return length;
    }
    
    Vector vec_multiply(Vector& vec2) // векторное произведение
    {
        Vector result;
        result.x = this->y*vec2.z - this->z*vec2.y;
        result.y = -(this->x*vec2.z - this->z*vec2.x);
        result.z = this->x*vec2.y - this->y*vec2.x;
        
        return result;
    }
    
    
    double operator * (Vector& vec2)
    {
        double result = 0;
        result = this->x * vec2.x + this->y * vec2.y + this->z * vec2.z;
        
        return result;
    }
    
    Vector operator * (double num)
    {
        this->x = this->x*num;
        this->y = this->y*num;
        this->z = this->z*num;
        
        return *this;
    }

	Vector operator + (Vector& vec2)
	{
		Vector result;
		result.x = this->x + vec2.x;
		result.y = this->y + vec2.y;
		result.z = this->z + vec2.z;
		
		return result;
	}

	Vector operator - (Vector& vec2)
	{
		Vector result;
		result.x = this->x - vec2.x;
		result.y = this->y - vec2.y;
		result.z = this->z - vec2.z;
		
		return result;
	}
	
	friend std::ostream& operator << (std::ostream &out, Vector& my_vector);
	
	friend std::istream& operator >> (std::istream &in, Vector& my_vector);
	
	friend void get_angle (Vector vec1, Vector vec2);
    friend void get_distance (Vector vec1, Vector vec2);
    friend void get_distance (Vector vec1, double point_x, double point_y, double point_z);
    
};



std::ostream& operator << (std::ostream &out, Vector& my_vector)
{
    out << "(" << my_vector.x << ", " << my_vector.y << ", " << my_vector.z << ")\n";
    	    
    return out;
}
	
std::istream& operator >> (std::istream &in, Vector& my_vector)
{
    in >> my_vector.x;
    in >> my_vector.y;
    in >> my_vector.z;
    	    
    return in;
}



void get_angle (Vector vec1, Vector vec2) // угол между плоскостями и прямыми
{
    double numenator, denominator;
    numenator = std::abs(vec1*vec2);
    denominator = vec1.vec_length()*vec2.vec_length();
    
    assert (denominator != 0);
    
    std::cout << "cos(a) = " << numenator/denominator << std::endl;
    std::cout << "a = " << acos(numenator/denominator)*(180/3.14159) << std::endl;
}

void get_distance (Vector vec1, Vector vec2) // vec1 - вектор нормали, расстояние между прямыми
{
    assert (vec1.vec_length() != 0);
    
    double numenator;
    numenator = std::abs(vec1*vec2);
    
    std::cout << "r = " << numenator/vec1.vec_length() << std::endl;
}

void get_distance (Vector vec1, double point_x, double point_y, double point_z) // vec1 - вектор нормали. Рассчет 
                                                                                // расстояния для точки и плоскости,
                                                                                // также для прямой и точки
{
    assert (vec1.vec_length() != 0);
    
    std::cout << "Enter a point belonging the plane or line:" << std::endl;
    double point_x_in_plane, point_y_in_plane, point_z_in_plane;
    std::cin >> point_x_in_plane;
    std::cin >> point_y_in_plane;
    std::cin >> point_z_in_plane;
    
    Vector connecting(point_x - point_x_in_plane,
                      point_y - point_y_in_plane,
                      point_z - point_z_in_plane);
    
    double numenator;
    numenator = std::abs(vec1*connecting);
    
    std::string your_choice;
    std::cout << "Choose line or plane:" << std::endl;
	std::getline(std::cin, your_choice);
	std::getline(std::cin, your_choice);
    
    if (your_choice == "plane")
    {
        std::cout << "r = " << numenator/vec1.vec_length() << std::endl;
    } else
    {
        double r;
        r = sqrt(pow(connecting.vec_length()*vec1.vec_length(), 2) - vec1*connecting)/vec1.vec_length();
        std::cout << "r = " << r << std::endl;
    }
        
}


int main()
{
    std::cout << "Do you need angle or distance?" << std::endl;
    std::string choice;
    std::getline(std::cin, choice);
    
    if (choice == "angle")
    {
        Vector vec1, vec2;
        std::cout << "Enter vector 1 and vector 2:" << std::endl;
        std::cin >> vec1;
        std::cin >> vec2;
        get_angle(vec1, vec2);
        
    } else
    {
        std::cout << "Do you need distance between lines? (yes or no)" << std::endl;
        std::getline(std::cin, choice);
        
        if (choice == "yes")
        {
            Vector vec1, vec2;
            std::cout << "Enter vector 1 and vector 2:" << std::endl;
            std::cin >> vec1;
            std::cin >> vec2;
            get_distance(vec1, vec2);
            
        } else
        {
            Vector vec1;
            double x1, y1, z1;
            std::cout << "Enter vector and point coordinates:" << std::endl;
            std::cin >> vec1;
            std::cin >> x1 >> y1 >> z1;
            get_distance(vec1, x1, y1, z1);
            
        }
    }
    
    return 0;
}
