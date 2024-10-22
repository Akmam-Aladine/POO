#include <iostream>
using namespace std ;
void fonct ()
{
int i; 
i++ ;
cout << "appel numéro " << i << "\n" ;
}
main()
{ void fonct() ;
int i ;
while(i<3){
fonct() ;
i++;
}
}