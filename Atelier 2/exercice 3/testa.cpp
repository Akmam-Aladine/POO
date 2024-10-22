#include <iostream>
using namespace std ;
int main()
{ 
    const int N= 10 ; 
int i, min, max ;
int T[N] ;
cout << "donnez " << N << " valeurs" <<endl;
for (i=0 ; i<N ; i++) cin >> T[i] ;
max = min = T[0] ;
for (i=1 ; i<N ; i++)
{ max =( T[i]>max )? T[i] : max ; 
min = (T[i]<min) ? T[i] :min;
cout << "valeur max : " << max << endl ;
cout << "valeur min : " << min << endl ;
}
}