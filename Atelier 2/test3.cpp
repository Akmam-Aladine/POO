
#include <iostream>
using namespace std;

int main() {

    int a ;
    cout<<"entrez la valeur de a:";
    cin>>a;
    int& ref_a = a;
    int* p_a = &a;

    cout << "Valeur de a : " << a << endl;
    cout << "Adresse de a : " << &a << endl;
    cout << "Valeur de ref_a : " << ref_a << endl;
    cout << "Adresse de ref_a : " << &ref_a << endl; // Adresse de ref_a est la même que celle de a
    cout << "Valeur de p_a : " << p_a << endl;
    cout << "Valeur pointée par p_a : " << *p_a << endl;
    cout << "Adresse de p_a : " << &p_a << endl;

    return 0;
}