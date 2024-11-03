#include<iostream>
using namespace std;

class Animal{
protected:
int age;
string nom;
public:
void set_value(int a,string name )
    {
    age=a;
     nom=name;
     }

};
 class Zebra:public Animal{
public:
void set_value( int age,string nom,string lieu_org){
    cout<<"le nom  :"<<nom<<  " et l'age :  "<<age<< " le lieu d'origine  :"  << lieu_org<<endl;
}

 };

 class Dolphin:public Animal{
   public:
void set_value( int age,string nom,string lieu_org){
    cout<<"le nom  :"<<nom<<" et l'age  :"<<age<< "  le lieu d'origine  :"  << lieu_org<<endl;
}
 };

 int main(){
Zebra Zeb1;
Dolphin Do1;
Zeb1.set_value(10,"zebra1","malawi");
Do1.set_value(13,"dophine","hawai");

    return 0;
 };