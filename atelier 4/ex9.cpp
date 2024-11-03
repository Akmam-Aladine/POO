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
    Element* premier;  // Pointeur vers le premier élément de la liste

public:
    Liste() : premier(nullptr) {}

    // Méthode pour ajouter un élément au début de la liste
    void ajouter(int val) {
        Element* nouvelElement = new Element(val);
        nouvelElement->suivant = premier;
        premier = nouvelElement;
    }

    // Méthode pour supprimer un élément du début de la liste
    void supprimer() {
        if (premier) {
            Element* temp = premier;
            premier = premier->suivant;
            delete temp;
        }
    }

    // Méthode pour afficher la liste en entier
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
    Liste maListe;

    maListe.ajouter(12);
    maListe.ajouter(8);
    maListe.ajouter(10);

    maListe.afficher();

    maListe.supprimer();
    maListe.afficher();

    return 0;
}
