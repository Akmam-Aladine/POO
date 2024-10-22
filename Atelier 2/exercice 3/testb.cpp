#include <iostream>
using namespace std ;
main()
{ const int N = 10 ; 
int i, min, max ;
int t[N] ;
cout << "donnez " << N << " valeurs"<<endl ;
for (i=0 ; i<N ; i++) cin >> *(t+i) ;
max = min = *t ;
for (i=1 ; i<N ; i++)
{ if ( *(t+i) > max) max = *(t+i) ;
if ( *(t+i) < min) min = *(t+i) ;
}
cout << "valeur max : " << max << endl ;
cout << "valeur min : " << min << endl ;
}