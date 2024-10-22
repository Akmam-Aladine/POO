#include <iostream>
using namespace std ;
main()
{ int val ; 
int * p1, * p2 ; 
for (;;) { 
        cout << "combien de valeurs souhaitez vous : ";
        cin >> val;

        if (val > 0) {
            break; 
        }
    }

p1 = new int [val] ;
cout << "veuillez donnez " << val << " valeurs  "<<endl;
for (int i = 0 ; i<val ; i++) cin >> p1[i] ; 

p2 = new int [val] ;
for (int i = 0 ; i<val ; i++) p2[i] = p1[i] * p1[i] ;

delete p1 ;
cout << "voila leurs carrés : \n" ;
for (int i = 0 ; i<val ; i++) cout << p2[i] << " " ;

delete p2 ;
}