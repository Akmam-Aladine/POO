#include <iostream>
using namespace std ;
void echange (int & m, int & n)
{ int l ; 
l = m ;
m = n ;
n = l ;
}
int main()
{ void echange (int &, int &) ; 
int a, b;
cout<<"entrez les valeurs "<<endl;
cin>>a>>b;
cout << "avant : " << a<< " et " << b << endl;
echange (a, b) ; 
cout << "après : " << a << " et " << b << endl;
return 0;
}
