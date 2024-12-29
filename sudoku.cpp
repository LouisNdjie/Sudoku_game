#include<iostream>
#include<ctime>
#include<fstream>
#include<cstdlib>
#include"header/sudoku.h"

Sudoku sudoku;
Sudoku loadpart;
int valeur = 0;
int line = 0;
int column = 0; 
int level = 0;

int choix;

int main(int argc, char *argv[])
{
    bool running = true;

    while(running)
    {
        system("cls");
        afficherMenu_debut();
        std::cout<<"choississez une option : ";
        std::cin >> choix;
        switch(choix)
        {
            case 1:
                system("cls");
                initialiserSudoku(sudoku);
                level = 0;
                std::cout<<"Entrez le niveau de difficulte [1-100] : ";
                std::cin>>level;
                genererPuzzle(sudoku,level);
                play(sudoku, running, choix);
            break;

            case 2:
            {
                system("cls");
                chargerSudoku(loadpart, "save_file/sudoku_console.txt");
                play(loadpart, running, choix);
            }
            break;

            case 3:
            {
                running = false;
            }
            break;
        }
    }
    if(choix == 1)
    {
        afficherSudoku(sudoku);
    }else if(choix == 2)
    {
        afficherSudoku(loadpart);
    }

    return 0;

}
