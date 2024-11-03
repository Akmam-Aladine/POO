#include <iostream>
using namespace std;

class Complex {
private:
    double real, imag;

public:
    Complex(double r = 0, double i = 0)
    {
        real = r;
        imag = i;
    }

    Complex operator+(Complex const& c2)
    {
        return Complex(real +  c2.real, imag  + c2.imag);
    }
    Complex operator-(Complex const& c2)
    {
        return Complex(real -  c2.real, imag  - c2.imag);
    }
    Complex operator*(Complex const& c2)
    {
        return Complex(
            (real * c2.real - imag * c2.imag), (real * c2.imag + imag * c2.real)
        );
    }
    Complex operator/(Complex const& c2)
    {
        //(ca+bd)/(a2+b2)+(ad−cb)i/(a2+b2)
        double den = c2.real * c2.real + real * real;
        
        return Complex(
            (real * c2.real + imag * c2.imag)/ den, (real * c2.imag - imag * c2.real)/den
        );
    }
    bool operator==(Complex const& c2)
    {
        return real == c2.real && imag == c2.imag;
    }
    
    void print() { cout << real << " + i" << imag << '\n'; }
    
};

int main()
{
    double r1, r2, im1, im2; 
    
    cout << "entrer la partie reel de c1"<< endl;
    cin >> r1;
    cout << "entrer la partie imaginaire de c1"<< endl;
    cin >> im1;
    cout << "entrer la partie reel de c2"<< endl;
    cin >> r2;
    cout << "entrer la partie imaginaire de c2"<< endl;
    cin >> im2;
        
    Complex c1 = Complex(r1, im1);
    Complex c2 = Complex(r2, im2);
    Complex c3;
    int op;
    bool test;
    while(true){
        cout << "select choix" << endl;
        cout << "1 : +"<< endl;
        cout << "2 : -"<< endl;
        cout << "3 : *"<< endl;
        cout << "4 : /"<< endl;
        cout << "5 : ="<< endl;
        cout << "autre : exit"<< endl;
        cin >> op;
        
        
        
        switch(op){
            
            case  1:  c3 = c1 + c2; break;
            case  2:  c3 = c1 - c2; break;
            case  3:  c3 = c1 * c2; break;
            case  4:  c3 = c1 / c2; break;
            case  5:  cout << (c1 == c2) << endl; break;
            default: exit(0);
        }
        
        c3.print();

    }
return 0;
}