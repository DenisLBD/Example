#include <iostream>
#include <cmath>
#include <string>
#include <cassert>

class Vector
{
private:

    double x, y, z; // координаты вектора
    
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
    
    
    double operator * (Vector& vec2) // скалярное произведение векторов
    {
        double result = 0;
        result = this->x * vec2.x + this->y * vec2.y + this->z * vec2.z;
        
        return result;
    }
    
    Vector operator * (double num) // умножение вектора на число
    {
        this->x = this->x*num;
        this->y = this->y*num;
        this->z = this->z*num;
        
        return *this;
    }
    
    Vector operator / (double num) // деление вектора на число
    {
        this->x = this->x/num;
        this->y = this->y/num;
        this->z = this->z/num;
        
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
	
	friend void get_angle (Vector& vec1, Vector& vec2);
	friend void get_angle (Vector& vec1, Vector& vec2, Vector& vec3);
	friend void get_angle (Vector& vec1, Vector& vec2, Vector& vec3, Vector& vec4);
	
    friend void get_distance (Vector& vec1, Vector& vec2, Vector& vec3);
    friend void get_distance (Vector& vec1, double point_x, double point_y, double point_z);
    friend void get_distance (Vector& vec1, Vector& vec2, double point_x, const double point_y, double point_z);
    
};



std::ostream& operator << (std::ostream &out, Vector& my_vector)
{
    out << "(" << my_vector.x << ", " << my_vector.y << ", " << my_vector.z << ")" << std::endl;
    	    
    return out;
}
	
std::istream& operator >> (std::istream &in, Vector& my_vector)
{
    in >> my_vector.x;
    in >> my_vector.y;
    in >> my_vector.z;
    	    
    return in;
}



void get_angle (Vector& vec1, Vector& vec2) // угол между прямыми
{
    double numenator, denominator;
    numenator = std::abs(vec1*vec2);
    denominator = vec1.vec_length()*vec2.vec_length();
    
    assert (denominator != 0);
    
    std::cout << "cos(a) = " << numenator/denominator << std::endl;
    std::cout << "a = " << acos(numenator/denominator)*(180/3.14159) << std::endl;
}

void get_angle (Vector& vec1, Vector& vec2, Vector& vec3) // угол между прямой и плоскостью
{
    Vector vec_norm;
    vec_norm = vec2.vec_multiply(vec3);
    
    double numenator, denominator;
    numenator = std::abs(vec1*vec_norm);
    denominator = vec1.vec_length()*vec_norm.vec_length();
    
    assert (denominator != 0);
    
    std::cout << "sin(a) = " << numenator/denominator << std::endl;
    std::cout << "a = " << asin(numenator/denominator)*(180/3.14159) << std::endl;
}

void get_angle (Vector& vec1, Vector& vec2, // угол между плоскостями 
                Vector& vec3, Vector& vec4) 
{
    Vector vec_norm_pl1, vec_norm_pl2;
    vec_norm_pl1 = vec1.vec_multiply(vec2);
    vec_norm_pl2 = vec3.vec_multiply(vec4);
    
    double numenator, denominator;
    numenator = std::abs(vec_norm_pl1*vec_norm_pl2);
    denominator = vec_norm_pl1.vec_length()*vec_norm_pl1.vec_length();
    
    assert (denominator != 0);
    
    std::cout << "cos(a) = " << numenator/denominator << std::endl;
    std::cout << "a = " << acos(numenator/denominator)*(180/3.14159) << std::endl;
}

void get_distance (Vector& vec1, Vector& vec2, Vector& vec3) // vec1, vec2 - направляющие векторы, 
                                                                               // vec3 - соединяющий
{
    Vector vec_norm;
    vec_norm = vec1.vec_multiply(vec2);
    
    assert (vec_norm.vec_length() != 0);
    
    double numenator;
    numenator = std::abs(vec_norm*vec3);
    
    std::cout << "r = " << numenator/vec_norm.vec_length() << std::endl;
}

void get_distance (Vector& vec1, double point_x,   //между точкой и прямой
                   double point_y, double point_z) //vec1 - направляющий вектор прямой
{
    assert (vec1.vec_length() != 0);
    
    std::cout << "Enter a point belonging the line:" << std::endl;
    double point_x_in_line, point_y_in_line, point_z_in_line;
    
    std::cin >> point_x_in_line;
    std::cin >> point_y_in_line;
    std::cin >> point_z_in_line;
    
    Vector connecting(point_x - point_x_in_line,
                      point_y - point_y_in_line,
                      point_z - point_z_in_line);
    
    double numenator;
    numenator = std::abs(vec1*connecting);
    
    double r;
    r = sqrt(pow(connecting.vec_length()*vec1.vec_length(), 2) - vec1*connecting)/vec1.vec_length();
    std::cout << "r = " << r << std::endl;
}

void get_distance (Vector& vec1, Vector& vec2,                      //между точкой и плоскостью                                                               
                   double point_x, double point_y, double point_z)  //vec1 и vec2 лежат в плоскости
{
    Vector vec_norm;
    vec_norm = vec1.vec_multiply(vec2);
    
    assert (vec_norm.vec_length() != 0);
    
    std::cout << "Enter a point belonging the plane:" << std::endl;
    double point_x_in_plane, point_y_in_plane, point_z_in_plane;
    
    std::cin >> point_x_in_plane;
    std::cin >> point_y_in_plane;
    std::cin >> point_z_in_plane;
    
    Vector connecting(point_x - point_x_in_plane,
                      point_y - point_y_in_plane,
                      point_z - point_z_in_plane);
    
    double numenator;
    numenator = std::abs(vec_norm*connecting);
    
    std::cout << "r = " << numenator/vec_norm.vec_length() << std::endl;
}



int main()
{
    std::cout << "Do you need angle or distance?" << std::endl;
    std::string choice;
    std::getline(std::cin, choice);
    
    if (choice == "angle")
    {
        std::cout << "Between lines/planes/line and planes?" << std::endl;
        std::string angle_choice;
        std::getline(std::cin, angle_choice);
        
        if (angle_choice == "lines")
        {
            Vector vec1, vec2;
            
            std::cout << "Enter vector 1 and vector 2:" << std::endl;
            std::cin >> vec1;
            std::cin >> vec2;
            
            get_angle(vec1, vec2);
            
        } else
        
            if (angle_choice == "planes")
            {
                Vector vec1_in_pl1, vec2_in_pl1;
                Vector vec1_in_pl2, vec2_in_pl2;
                
                std::cout << "Enter two vectors in plane one" << std::endl;
                std::cin >> vec1_in_pl1 >> vec2_in_pl1;
                std::cout << "Enter two vectors in plane two" << std::endl;
                std::cin >> vec1_in_pl2 >> vec2_in_pl2;
                
                get_angle(vec1_in_pl1, vec2_in_pl1, vec1_in_pl2, vec2_in_pl2);
                
            } else
            
            {
                Vector vec_line;
                Vector vec1_in_pl, vec2_in_pl;
                
                std::cout << "Enter line vector" << std::endl;
                std::cin >> vec_line;
                std::cout << "Enter two vectors in plane" << std::endl;
                std::cin >> vec1_in_pl >> vec2_in_pl;
                
                get_angle(vec_line, vec1_in_pl, vec2_in_pl);
            }
        
    } else
    
    {
        std::cout << "Distance between lines/point and line/point and plane" << std::endl;
        std::getline(std::cin, choice);
        
        if (choice == "lines")
        {
            Vector vec1, vec2, vec3;
            
            std::cout << "Enter line vector 1 and line vector 2:" << std::endl;
            std::cin >> vec1 >> vec2;
            std::cout << "Enter connecting vector:" << std::endl;
            std::cin >> vec3;
            get_distance(vec1, vec2, vec3);
            
        } else
        
            if (choice == "point and line")
            {
                Vector vec1;
                double x1, y1, z1;
                
                std::cout << "Enter line vector:" << std::endl;
                std::cin >> vec1;
                std::cout << "Enter point coordinates:" << std::endl;
                std::cin >> x1 >> y1 >> z1;
                get_distance(vec1, x1, y1, z1);
                
            } else
            
            {
                Vector vec1, vec2;
                double x1, y1, z1;
                
                std::cout << "Enter two vectors in plane:" << std::endl;
                std::cin >> vec1 >> vec2;
                std::cout << "Enter point coordinates:" << std::endl;
                std::cin >> x1 >> y1 >> z1;
                
                get_distance(vec1, vec2, x1, y1, z1);
            }
    }
    
    return 0;
}
