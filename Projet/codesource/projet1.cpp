#include <raylib.h>
#include <vector>
#include <stack>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Dimensions de la fenêtre de jeu
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 850;

// États possibles de l'application
enum class AppState {
    MENU,                 // Menu principal
    SELECTION_NIVEAU,     // Sélection du niveau de difficulté
    JEU,                  // État du jeu
    FIN,                  // Fin du jeu
    SCORES                // Écran des scores
};

// Niveaux de difficulté disponibles
enum class NiveauDifficulte {
    FACILE,
    MOYEN,
    DIFFICILE
};

// Structure pour stocker les scores
struct Score {
    int temps; // Temps pris pour terminer

    // Comparaison des scores pour les trier par ordre croissant
    bool operator<(const Score& other) const {
        return temps < other.temps;
    }
};

// Gestionnaire des scores pour différents niveaux de difficulté
class ScoreManager {
private:
    // Scores triés pour chaque niveau de difficulté
    vector<Score> scoresFacile;
    vector<Score> scoresMoyen;
    vector<Score> scoresDifficile;

public:
    // Ajoute un score à la liste correspondante au niveau choisi
    void ajouterScore(NiveauDifficulte niveau, int temps) {
        Score newScore{ temps }; // Crée un nouvel objet Score
        switch (niveau) {
        case NiveauDifficulte::FACILE:
            scoresFacile.push_back(newScore);
            sort(scoresFacile.begin(), scoresFacile.end()); // Trie la liste
            break;
        case NiveauDifficulte::MOYEN:
            scoresMoyen.push_back(newScore);
            sort(scoresMoyen.begin(), scoresMoyen.end());
            break;
        case NiveauDifficulte::DIFFICILE:
            scoresDifficile.push_back(newScore);
            sort(scoresDifficile.begin(), scoresDifficile.end());
            break;
        }
    }

    // Affiche les scores pour un niveau donné
    void afficherScores(NiveauDifficulte niveau) const {
        vector<Score> scores;
        string titre;

        // Sélectionne les scores et le titre en fonction du niveau
        switch (niveau) {
        case NiveauDifficulte::FACILE:
            scores = scoresFacile;
            titre = "Scores Facile";
            break;
        case NiveauDifficulte::MOYEN:
            scores = scoresMoyen;
            titre = "Scores Moyen";
            break;
        case NiveauDifficulte::DIFFICILE:
            scores = scoresDifficile;
            titre = "Scores Difficile";
            break;
        }

        // Affiche le titre
        DrawText(titre.c_str(), SCREEN_WIDTH / 2 - MeasureText(titre.c_str(), 30) / 2, 100, 30, BLACK);

        // Affiche les 10 meilleurs scores
        int y = 150;
        for (size_t i = 0; i < scores.size() && i < 10; ++i) {
            string scoreText = to_string(i + 1) + ". " + to_string(scores[i].temps) + "s";
            DrawText(scoreText.c_str(), SCREEN_WIDTH / 2 - MeasureText(scoreText.c_str(), 20) / 2, y, 20, BLACK);
            y += 30;
        }
    }
};

// Classe pour gérer les niveaux
class Niveau {
private:
    NiveauDifficulte difficulte; // Niveau de difficulté actuel

public:
    // Constructeur par défaut (FACILE)
    Niveau(NiveauDifficulte diff = NiveauDifficulte::FACILE) : difficulte(diff) {}

    // Définit la difficulté
    void setDifficulte(NiveauDifficulte diff) {
        difficulte = diff;
    }

    // Retourne la difficulté actuelle
    NiveauDifficulte getDifficulte() const {
        return difficulte;
    }

    // Retourne la taille des cellules en fonction de la difficulté
    int getCellSize() const {
        switch (difficulte) {
        case NiveauDifficulte::FACILE:
            return 100;
        case NiveauDifficulte::MOYEN:
            return 50;
        case NiveauDifficulte::DIFFICILE:
            return 25;
        }
        return 100; // Valeur par défaut
    }
};

// Classe pour gérer un bouton
class Button {
private:
    Rectangle rect;       // Rectangle définissant le bouton
    string label;         // Texte affiché sur le bouton
    bool isHovered;       // Indique si le bouton est survolé par la souris

public:
    // Constructeur
    Button(float x, float y, float width, float height, const string& text)
        : rect{ x, y, width, height }, label(text), isHovered(false) {
    }

    // Vérifie si le bouton est cliqué
    bool isClicked() {
        Vector2 mousePos = GetMousePosition();
        isHovered = CheckCollisionPointRec(mousePos, rect); // Vérifie si la souris survole le bouton
        return isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }

    // Dessine le bouton à l'écran
    void draw() const {
        Color color = isHovered ? LIGHTGRAY : GRAY; // Change la couleur si survolé
        DrawRectangleRec(rect, color);             // Dessine le bouton
        DrawText(label.c_str(), rect.x + 10, rect.y + 10, 20, BLACK); // Affiche le texte
    }
};

// Classe représentant un labyrinthe
class Labyrinthe {
public:
    // Structure représentant une cellule du labyrinthe
    struct Cell {
        int x, y;               // Position de la cellule
        bool walls[4] = { true, true, true, true }; // Murs : [haut, droite, bas, gauche]
        bool visited = false;   // Indique si la cellule a été visitée
    };

private:
    vector<vector<Cell>> grid; // Grille des cellules
    int cols, rows;            // Nombre de colonnes et de rangées
    int cellSize;              // Taille d'une cellule

    // Retourne un voisin non visité de la cellule actuelle
    Cell* getUnvisitedNeighbor(Cell& cell) {
        vector<Cell*> neighbors;

        // Ajoute les voisins disponibles
        if (cell.y > 0 && !grid[cell.y - 1][cell.x].visited)
            neighbors.push_back(&grid[cell.y - 1][cell.x]);
        if (cell.x < cols - 1 && !grid[cell.y][cell.x + 1].visited)
            neighbors.push_back(&grid[cell.y][cell.x + 1]);
        if (cell.y < rows - 1 && !grid[cell.y + 1][cell.x].visited)
            neighbors.push_back(&grid[cell.y + 1][cell.x]);
        if (cell.x > 0 && !grid[cell.y][cell.x - 1].visited)
            neighbors.push_back(&grid[cell.y][cell.x - 1]);

        // Choisit un voisin aléatoire parmi ceux disponibles
        if (!neighbors.empty()) {
            return neighbors[rand() % neighbors.size()];
        }
        return nullptr;
    }

    // Supprime les murs entre deux cellules adjacentes
    void removeWalls(Cell& current, Cell& next) {
        if (current.x == next.x) { // Même colonne
            if (current.y > next.y) {
                current.walls[0] = false; // Mur en haut
                next.walls[2] = false;   // Mur en bas
            }
            else {
                current.walls[2] = false;
                next.walls[0] = false;
            }
        }
        else if (current.y == next.y) { // Même rangée
            if (current.x > next.x) {
                current.walls[3] = false; // Mur à gauche
                next.walls[1] = false;   // Mur à droite
            }
            else {
                current.walls[1] = false;
                next.walls[3] = false;
            }
        }
    }

public:
    // Constructeur
    Labyrinthe(int width, int height, int cellSize)
        : cols(width / cellSize), rows(height / cellSize), cellSize(cellSize) {
        grid.resize(rows, vector<Cell>(cols));
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                grid[y][x] = { x, y }; // Initialise chaque cellule
            }
        }
    }

    // Génère le labyrinthe en utilisant l'algorithme de backtracking
    void generate() {
        srand(static_cast<unsigned>(time(nullptr))); // Initialise le générateur de nombres aléatoires
        stack<Cell*> stack;
        Cell* current = &grid[0][0];
        current->visited = true;

        while (true) {
            Cell* next = getUnvisitedNeighbor(*current);
            if (next) {
                next->visited = true;
                stack.push(current);
                removeWalls(*current, *next); // Supprime les murs entre les cellules
                current = next;
            }
            else if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            }
            else {
                break; // Labyrinthe généré
            }
        }
    }

    // Dessine le labyrinthe à l'écran
    void draw() const {
        for (const auto& row : grid) {
            for (const auto& cell : row) {
                int x = cell.x * cellSize;
                int y = cell.y * cellSize;
                if (cell.walls[0]) DrawLine(x, y, x + cellSize, y, BLACK);          // Ligne du haut
                if (cell.walls[1]) DrawLine(x + cellSize, y, x + cellSize, y + cellSize, BLACK); // Ligne de droite
                if (cell.walls[2]) DrawLine(x, y + cellSize, x + cellSize, y + cellSize, BLACK); // Ligne du bas
                if (cell.walls[3]) DrawLine(x, y, x, y + cellSize, BLACK);          // Ligne de gauche
            }
        }
    }

    // Retourne la grille pour des interactions
    const vector<vector<Cell>>& getGrid() const {
        return grid;
    }

    int getCols() const { return cols; }
    int getRows() const { return rows; }
    int getCellSize() const { return cellSize; }
};

// Classe représentant le joueur
class Joueur {
private:
    Vector2 position; // Position du joueur

public:
    // Constructeur par défaut
    Joueur() : position{ 0, 0 } {}

    // Déplace le joueur si le mouvement est valide
    void move(const Labyrinthe& lab, int key) {
        if (key == KEY_UP && position.y > 0) position.y -= 1;                  // Déplacement vers le haut
        if (key == KEY_DOWN && position.y < lab.getRows() - 1) position.y += 1; // Bas
        if (key == KEY_LEFT && position.x > 0) position.x -= 1;               // Gauche
        if (key == KEY_RIGHT && position.x < lab.getCols() - 1) position.x += 1; // Droite
    }

    // Retourne la position actuelle
    Vector2 getPosition() const { return position; }
};

// Classe principale gérant tout le jeu
class Jeu {
private:
    AppState appState;         // État actuel de l'application
    Niveau niveau;             // Niveau actuel
    Labyrinthe* labyrinthe;    // Instance du labyrinthe
    Joueur joueur;             // Instance du joueur
    Vector2 exitPos;           // Position de la sortie
    double startTime, endTime; // Temps de début et de fin
    ScoreManager scoreManager; // Gestionnaire des scores

    // Textures pour les éléments graphiques
    Texture2D ratTexture, cheeseTexture;

    // Boutons pour différentes actions
    Button buttonStart{ SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 25, 200, 50, "Commencer" };
    Button buttonEasy{ SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 125, 200, 50, "Facile" };
    Button buttonMedium{ SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 25, 200, 50, "Moyen" };
    Button buttonHard{ SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 75, 200, 50, "Difficile" };
    Button buttonReplay{ SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 25, 200, 50, "Rejouer" };
    Button buttonScores{ SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 50, 200, 50, "Scores" };
    Button buttonQuit{ SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 + 125, 200, 50, "Quitter" };

    // Dessine le menu principal
    void drawMenu() {
        DrawText("Bienvenue dans le Jeu !", SCREEN_WIDTH / 2 - MeasureText("Bienvenue dans le Jeu !", 30) / 2, 200, 30, BLACK);
        if (buttonStart.isClicked()) appState = AppState::SELECTION_NIVEAU; // Passe à l'état de sélection de niveau
        buttonStart.draw();
    }

    // Affiche l'écran de sélection de niveau
    void drawSelectionNiveau() {
        DrawText("Choisissez un Niveau", SCREEN_WIDTH / 2 - MeasureText("Choisissez un Niveau", 30) / 2, 200, 30, BLACK);
        if (buttonEasy.isClicked()) setNiveau(NiveauDifficulte::FACILE);     // Facile
        if (buttonMedium.isClicked()) setNiveau(NiveauDifficulte::MOYEN);   // Moyen
        if (buttonHard.isClicked()) setNiveau(NiveauDifficulte::DIFFICILE); // Difficile
        buttonEasy.draw();
        buttonMedium.draw();
        buttonHard.draw();
    }

    // Définit la difficulté et démarre le jeu
    void setNiveau(NiveauDifficulte difficulte) {
        niveau.setDifficulte(difficulte);
        startGame();
    }

    // Initialise le jeu
    void startGame() {
        int cellSize = niveau.getCellSize();                          // Taille des cellules
        labyrinthe = new Labyrinthe(SCREEN_WIDTH, SCREEN_HEIGHT, cellSize);
        labyrinthe->generate();                                       // Génère le labyrinthe
        joueur = Joueur();                                            // Réinitialise le joueur
        exitPos = { (float)(labyrinthe->getCols() - 1), (float)(labyrinthe->getRows() - 1) }; // Position de la sortie
        appState = AppState::JEU;                                     // Passe à l'état du jeu
        startTime = GetTime();                                        // Débute le chronomètre
    }

    // Dessine l'état du jeu (labyrinthe et joueur)
    void drawGame() {
        labyrinthe->draw();                                           // Dessine le labyrinthe
        Vector2 playerPos = joueur.getPosition();                    // Position du joueur
        int cellSize = labyrinthe->getCellSize();

        const auto& grid = labyrinthe->getGrid();                    // Grille du labyrinthe
        if (IsKeyPressed(KEY_UP) && !grid[playerPos.y][playerPos.x].walls[0]) joueur.move(*labyrinthe, KEY_UP);   // Déplacement haut
        if (IsKeyPressed(KEY_DOWN) && !grid[playerPos.y][playerPos.x].walls[2]) joueur.move(*labyrinthe, KEY_DOWN); // Bas
        if (IsKeyPressed(KEY_LEFT) && !grid[playerPos.y][playerPos.x].walls[3]) joueur.move(*labyrinthe, KEY_LEFT); // Gauche
        if (IsKeyPressed(KEY_RIGHT) && !grid[playerPos.y][playerPos.x].walls[1]) joueur.move(*labyrinthe, KEY_RIGHT); // Droite

        // Dessine le joueur
        Rectangle source = { 0, 0, (float)ratTexture.width, (float)ratTexture.height };
        Rectangle dest = { playerPos.x * cellSize, playerPos.y * cellSize, (float)cellSize, (float)cellSize };
        Vector2 origin = { 0, 0 };
        DrawTexturePro(ratTexture, source, dest, origin, 0.0f, WHITE);

        // Dessine la sortie
        Rectangle exitDest = { exitPos.x * cellSize, exitPos.y * cellSize, (float)cellSize, (float)cellSize };
        DrawTexturePro(cheeseTexture, source, exitDest, origin, 0.0f, WHITE);

        // Si le joueur atteint la sortie
        if (playerPos.x == exitPos.x && playerPos.y == exitPos.y) {
            appState = AppState::FIN;                                // Passe à l'état de fin
            endTime = GetTime();                                     // Arrête le chronomètre
            scoreManager.ajouterScore(niveau.getDifficulte(), static_cast<int>(endTime - startTime)); // Enregistre le score
        }
    }

    // Dessine l'écran de fin
    void drawEndScreen() {
        DrawText("Bravo! Vous avez termine le Labyrinthe!", SCREEN_WIDTH / 2 - MeasureText("Bravo! Vous avez termine le Labyrinthe!", 30) / 2, 200, 30, BLACK);
        string timeText = "Temps: " + to_string(static_cast<int>(endTime - startTime)) + " secondes";
        DrawText(timeText.c_str(), SCREEN_WIDTH / 2 - MeasureText(timeText.c_str(), 20) / 2, 250, 20, BLACK);

        // Actions possibles après la fin du jeu
        if (buttonReplay.isClicked()) {
            delete labyrinthe; // Nettoie le labyrinthe
            labyrinthe = nullptr;
            appState = AppState::SELECTION_NIVEAU; // Retour à la sélection du niveau
        }
        if (buttonScores.isClicked()) {
            appState = AppState::SCORES; // Passe à l'écran des scores
        }
        if (buttonQuit.isClicked()) {
            CloseWindow(); // Ferme la fenêtre
            exit(0);       // Termine le programme
        }
        buttonReplay.draw();
        buttonScores.draw();
        buttonQuit.draw();
    }

    // Dessine l'écran des scores
    void drawScores() {
        ClearBackground(LIGHTGRAY);                  // Fond de l'écran
        scoreManager.afficherScores(niveau.getDifficulte()); // Affiche les scores

        // Actions possibles depuis l'écran des scores
        if (buttonReplay.isClicked()) {
            delete labyrinthe;
            labyrinthe = nullptr;
            appState = AppState::SELECTION_NIVEAU; // Retour à la sélection du niveau
        }
        if (buttonQuit.isClicked()) {
            CloseWindow(); // Ferme la fenêtre
            exit(0);       // Termine le programme
        }
        buttonReplay.draw();
        buttonQuit.draw();
    }

public:
    // Constructeur initialisant l'état de l'application
    Jeu() : appState(AppState::MENU), labyrinthe(nullptr), startTime(0), endTime(0) {}

    // Destructeur pour nettoyer le labyrinthe
    ~Jeu() {
        if (labyrinthe) delete labyrinthe;
    }

    // Boucle principale du jeu
    void run() {
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Labyrinthe avec Scores"); // Initialise la fenêtre
        ratTexture = LoadTexture("rat.png");       // Charge la texture du rat
        cheeseTexture = LoadTexture("cheese.png"); // Charge la texture du fromage
        SetTargetFPS(60);                          // Définit le taux de rafraîchissement à 60 FPS

        while (!WindowShouldClose()) {            // Boucle principale jusqu'à ce que la fenêtre soit fermée
            BeginDrawing();
            ClearBackground(DARKPURPLE);          // Fond de l'écran principal

            // Dessine en fonction de l'état actuel de l'application
            switch (appState) {
            case AppState::MENU:
                drawMenu();                        // Menu principal
                break;
            case AppState::SELECTION_NIVEAU:
                drawSelectionNiveau();            // Sélection du niveau
                break;
            case AppState::JEU:
                drawGame();                        // Jeu
                break;
            case AppState::FIN:
                drawEndScreen();                  // Fin du jeu
                break;
            case AppState::SCORES:
                drawScores();                     // Scores
                break;
            }

            EndDrawing();
        }

        UnloadTexture(ratTexture);               // Décharge la texture du rat
        UnloadTexture(cheeseTexture);            // Décharge la texture du fromage
        CloseWindow();                           // Ferme la fenêtre
    }
};

// Point d'entrée principal
int main() {
    Jeu jeu;                                     // Crée une instance du jeu
    jeu.run();                                   // Lance le jeu
    return 0;                                    // Retourne 0 pour indiquer un succès
}
