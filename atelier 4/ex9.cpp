#include <iostream>
using namespace std;

// Structure pour les éléments de la liste
struct Element {
    int valeur;
    Element* suivant;

    Element(int val) : valeur(val), suivant(nullptr) {}
};

class Liste {
private:
    Element* premier; 

public:
    Liste() : premier(nullptr) {}

    void ajouter(int val) {
        Element* nouvelElement = new Element(val);
        nouvelElement->suivant = premier;
        premier = nouvelElement;
    }

    void supprimer() {
        if (premier) {
            Element* temp = premier;
            premier = premier->suivant;
            delete temp;
        }
    }

    void afficher() {
        Element* courant = premier;
        cout << "Liste : ";
        while (courant != nullptr) {
            cout << courant->valeur << " ";
            courant = courant->suivant;
        }
        cout << endl;
    }

    // Destructeur pour libérer la mémoire
    ~Liste() {
        while (premier != nullptr) {
            Element* temp = premier;
            premier = premier->suivant;
            delete temp;
        }
    }
};

int main() {
    Liste _Liste;

    _Liste.ajouter(12);
    _Liste.ajouter(8);
    _Liste.ajouter(10);

    _Liste.display();

    _Liste.supprimer();
    _Liste.display();

    return 0;
}
