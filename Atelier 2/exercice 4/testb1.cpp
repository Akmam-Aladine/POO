#include<iostream>
using namespace std;
void permuter (int * m, int * n)
{ int l ; // pour la permutation
l= *m ;
*m = *n ;
*n = l ;
}

int main()
{ void permuter (int *, int *) ; // prototype de la fonction echange
int a, b;
cout<<"entrez les valeurs "<<endl;
cin>>a>>b;
cout << "avant : " << a << " et " << b << endl ;
permuter (&a, &b) ;
cout << "après : " << a << " et " << b << endl ;
return 0;
}
