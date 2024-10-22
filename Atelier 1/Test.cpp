#include <ctime>       // Pour utiliser la fonction time()
#include <cstdlib>     // Pour les fonctions rand() et srand()
#include <iostream>    // Pour les entrées/sorties standard
#include <limits>      // Pour std::numeric_limits

using namespace std;
// Fonction pour lancer un dé
int throwDice(){
    int diceValue = 0; // valeur de la lancée
    diceValue = rand() % 6 + 1; // génère un nombre aléatoire entre 1 et 6
    return diceValue;
}

// Fonction pour gérer le tour d'un joueur
void playerTurn(int& scorep1, int& scorep2, bool& isFirstPlayerTurn) {
    int choice;
    bool validInput = false;
    // Affiche quel joueur joue
    (isFirstPlayerTurn) ? cout << "Autour de Player 1" << endl : cout << "Autour de Player 2" << endl;
    
    do {
        std::cout << "Voulez-vous lancer 1 ou 2 des ? >> ";

        // Vérifier si l'entrée est un nombre
        if (std::cin >> choice) {
            // Vérifier si le nombre est 1 ou 2
            if (choice == 1 || choice == 2) {
                validInput = true;
            } else {
                cout << "Erreur : Veuillez entrer 1 ou 2." << endl;
            }
        } else {
            // L'entrée n'est pas un nombre
            cout << "Erreur : Veuillez entrer un nombre valide." << endl;
            cin.clear(); // Réinitialiser l'état de cin
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Vider le buffer
        }

    } while (!validInput);

    if(choice == 1){
        // Lancer un seul dé
        int value = throwDice();
        cout << "________" << endl;
        cout << "resultat de la lancee : \n" <<
                  "De 1 --> " << value << endl;
        // Ajouter le score au joueur actuel
        if(isFirstPlayerTurn)
            scorep1 += value;
        else
            scorep2 += value;
    }else{
        // Lancer deux dés
        int value1 = throwDice();
        int value2 = throwDice();
        cout << "________" << endl;
        cout << "resultat de la lancee : \n" <<
                  "De 1 --> " << value1 << "\n" <<
                  "De 2 --> " << value2 << endl;
        // Gérer le score en fonction des résultats
        if(isFirstPlayerTurn)
            if(value1 == value2){
                // Si double, soustraire les points
                scorep1 += -(value1 + value2);
                if(scorep1 < 0)
                    scorep1 = 0;  // Empêcher un score négatif
            }
            else
                scorep1 += (value1 + value2);
        else
            if(value1 == value2){
                scorep2 += -(value1 + value2);
                if(scorep2 < 0)
                    scorep2 = 0;
            }
            else
                scorep2 += (value1 + value2);
    }

    // Changer de joueur pour le prochain tour
    isFirstPlayerTurn = !isFirstPlayerTurn;
}

int main() {
    srand(time(0));    // Initialise le générateur de nombres aléatoires avec le temps actuel


    int score1 = 0;
    int score2 = 0;
    bool isFirstPlayerTurn = true;

    // Boucle principale du jeu
    while (score1 < 30 && score2 < 30){
        playerTurn(score1, score2, isFirstPlayerTurn);
        // Afficher les scores actuels
        cout << "________" << endl;
        cout << "    Score actuel    " << endl;
        cout << "Player 1 = " << score1 << endl;
        cout << "Player 2 = " << score2 << endl;
        cout << "________" << endl;
    }

    // Déterminer et annoncer le gagnant
    if(score1 > score2 && score2 < 30){
        cout << "le gagnant est player 1" << endl;
    }else if(score1 > 30 && score2 > 30){
        cout << "Match null" << endl;
    }else{
        cout << "le gagnant est player 2" << endl;
    }

    return 0;
}