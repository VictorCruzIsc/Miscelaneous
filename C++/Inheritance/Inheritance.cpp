#include <iostream>

using namespace std;

// Abstract class
class Polygon{
	protected:
		int _width;
		int _heigth;
		int _totalSides;
	public:
		Polygon():_width(0), _heigth(0), _totalSides(0){
			cout << "Calling Polygon default constructor, with all values in 0" << endl;
		}
		Polygon(int width, int heigth, int totalSides):_width(width), _heigth(heigth), _totalSides(totalSides){
			cout << "Calling Polygon parametrized constructor, with values for width and heigth" << endl;
		}

		// Pure virtual functions: Need to be implemented in subclasses
		virtual double getArea() = 0;
		virtual double getPerimeter() = 0;
};

// Class that inherits from Polygon, implements pure virtual methods.
// This class may have instances
class Rectangle:public Polygon{
	public:
		Rectangle(){
			cout << "Calling rectangle default constructor width: " << _width << " heigth: " << _heigth << endl;
		}
		Rectangle(int width, int heigth, int totalSides):Polygon(width, heigth, totalSides){
			cout << "Calling rectangle parametrized constructor width: " << _width << " heigth: " << _heigth << endl;
		}
		double getArea(){
			cout << "Rectangle getArea()" << endl;
                	return _width * _heigth;
        	}
		double getPerimeter(){
			cout << "Rectangle getPerimeter()" << endl;
			return (_width * 2) + (_heigth *2);
		}
};

// Class that inherits from Polygon, implements pure virtual methods.
// Does not override getArea() or getPerimeter() so any object that use those methods
// will call Rectangle implementation
// This class may have instances
class Square:public Rectangle{
	public:
		Square(){
			cout << "Calling Square default constructor" << endl;
		}
		Square(int side):Rectangle(side, side, 4){
			cout << "Calling Square parametrized constructor width: " << _width << " heigth: " << _heigth << endl;
		}
};

// Class that inherits from Polygon, implements just one pure virtual funtion
// pure virtual function getArea() needs to be implemented and is not so it will not cause compilation errors
// but no instances can be called due pure virtual method behavior is not overwritten.
class Triangle:public Polygon{
	protected:
		double _sideA;
		double _sideB;
		double _sideC; 
	public:
		Triangle(){
			cout << "Calling Triangle default constructor width:" << _width << " heigth: " << _heigth << endl;
			_sideA = 0;
			_sideB = 0;
			_sideC = 0;
		}

		Triangle(double a, double b, double c):_sideA(a), _sideB(b), _sideC(c), Polygon(a, b, 3){
			cout << "Calling Triangle parametrized constructor width:" << _width << " heigth: " << _heigth << endl;
		} 
		double getPerimeter(){
			cout << "Triangle getPerimeter()" << endl;
			return (_sideA + _sideB + _sideC);
		}
};

// Class that inherits from Triangle, implements only getArea pure virtual method.
// This class may have instances
class RectangularTriangle:public Triangle{	
	public:
		RectangularTriangle(){
			cout << "Calling RectangleTriangle default constructor" << endl;
		}
		RectangularTriangle(int a, int b, int c):Triangle(a, b, c){
			cout << "Calling RectangularTriangle parametrized constructor" << endl;
			
		}
                double getArea(){
                        cout << "Rectangular Triangle getArea()" << endl;
                        return (_width * _heigth)/2;
                }
};

int main(){
	Rectangle rectangle;
	Rectangle rectangle2{5, 10, 4};

	RectangularTriangle triangle;
	RectangularTriangle triangle2{10, 20, 22};

	Polygon *pPolygon1 = &rectangle;
	Polygon *pPolygon2 = &rectangle2;
	Polygon *pPolygon3 = &triangle;
	Polygon *pPolygon4 = &triangle2;

	cout << pPolygon1->getArea() << endl;
	cout << pPolygon1->getPerimeter() << endl;
	cout << pPolygon2->getArea() << endl;
        cout << pPolygon2->getPerimeter() << endl;
	cout << pPolygon3->getArea() << endl;
        cout << pPolygon3->getPerimeter() << endl;
	cout << pPolygon4->getArea() << endl;
        cout << pPolygon4->getPerimeter() << endl;
}
