#include "Point1.h"
#include <iostream>
using namespace std ;
Point::Point (float abs, float ord)
{ x = abs ; y = ord ;
}
void Point::deplace (float dx, float dy)
{ x = x + dx ; y = + dy ;
}
void Point::affiche ()
{ cout << "Mes coordonnées cartésiennes sont " << x << " " << y << "\n" ;
}