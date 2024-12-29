#ifndef  SUDOKU_H_INCLUDED
#define  SUDOKU_H_INCLUDED

typedef struct Sudoku{
    int grille[9][9];
}Sudoku;

void initialiserSudoku(Sudoku& sudoku);
void afficherSudoku(const Sudoku& sudoku);
void genererPuzzle (Sudoku& sudoku, int level);
    bool remplirgrille(Sudoku& sudoku);
    bool peutremplir(Sudoku& sudoku, int line, int column, int num);
    void remove(Sudoku& sudoku, int level);
void entrerValeur (Sudoku& sudoku, int ligne, int colonne, int valeur);
bool resoudreSudoku (Sudoku& sudoku);
    bool peutresoudre(Sudoku& sudoku, int line, int column, int num);
bool estValide (Sudoku& sudoku, int ligne, int colonne, int valeur);
void sauvegarderSudoku (Sudoku& sudoku, const char* nomFichier);
bool chargerSudoku (Sudoku& sudoku, const char* nomFichier );
void afficherMenu();
void afficherMenu_debut();
bool play(Sudoku& sudoku, bool run, int choix);
void quitter(bool run);
#endif