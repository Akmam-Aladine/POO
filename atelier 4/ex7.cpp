#include <iostream>
#include <vector>
using namespace std;

class Pile {
private:
    vector<int> elements;

public:
    // Constructeur pour initialiser la pile
    Pile() {
        elements.clear();
    }

    // Empiler un élément sur la pile
    void push(int value) {
        elements.push_back(value);
    }

    // Dépiler un élément de la pile
    void pop() {
        if (!elements.empty()) {
            elements.pop_back();
        } else {
            cout << "La pile est vide. Impossible de dépiler." << endl;
        }
    }

    // Fonction pour afficher la pile (à des fins de débogage)
    void affiche() {
        cout << "Contenu de la pile : ";
        for (int i : elements) {
            cout << i << " ";
        }
        cout << endl;
    }
};

int main() {
    Pile p1, p2;

    // Empiler des valeurs sur p1
    p1.push(10);
    p1.push(20);
    p1.push(30);

    // Afficher p1
    cout << "Pile p1 (après empilement) : ";
    p1.affiche();

    // Dépiler un élément de p1
    p1.pop();

    // Afficher p1 après dépilement
    cout << "Pile p1 (après dépilement) : ";
    p1.affiche();

    // Empiler des valeurs sur p2
    p2.push(5);
    p2.push(15);

    // Afficher p2
    cout << "Pile p2 : ";
    p2.affiche();

    return 0;
}
