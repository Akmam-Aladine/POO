#include <iostream>
using namespace std ;
#include "Point1.h"
 int main ()
{
Point p (2.0, 3.0) ; 
p.affiche () ; 
p.deplace (1.0, 2.0) ; 
p.affiche () ; 
return 0;
}