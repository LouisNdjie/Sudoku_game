#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include"../header/sudoku.h"

void initialiserSudoku(Sudoku& sudoku)
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++) 
        {
            sudoku.grille[i][j] = 0;
        }

    }
}

void afficherSudoku(const Sudoku& sudoku)
{
    for ( int i = 0 ; i < 9 ; ++i ) 
    {
        for ( int j = 0 ; j < 9 ; ++j ) 
        {
            std::cout <<"|"<< sudoku.grille[i][j]<<"|" ;
        }
        std::cout<<std::endl ;
    }
}

void genererPuzzle (Sudoku& sudoku, int level)
{
    srand(time(NULL));
    //remplir la grille avec un solveur
    remplirgrille(sudoku);

    // Enlever un certain nombre de chiffres pour generer un puzzle
    remove(sudoku, level);

}

    bool remplirgrille(Sudoku& sudoku)
    {
        for (int i = 0; i < 9; i++) 
        {
            for (int j = 0; j < 9; j++) 
            {
                if (sudoku.grille[i][j] == 0) 
                {
                    for (int num = 1; num <= 9; num++) 
                    {
                        if (peutremplir(sudoku, i, j, num)) 
                        {
                            sudoku.grille[i][j] = num;
                            if (remplirgrille(sudoku)) 
                            {
                                return true;
                            }
                            sudoku.grille[i][j] = 0;
                        }
                    }
                    return false; 
                }
            }
        }
        return true; 
    }

    bool peutremplir(Sudoku& sudoku, int line, int column, int num)
    {
        for (int i = 0; i < 9; i++) 
            {
            if (sudoku.grille[line][i] == num || sudoku.grille[i][column] == num || sudoku.grille[line - line % 3 + i / 3][column - column % 3 + i % 3] == num) 
            {
                return false;
            }
        }
        return true;
    }

    void remove(Sudoku& sudoku, int level)
    {
        int removing = level;
        if(removing == 0)
        {
            removing = 1;
        }
        if(removing > 70)
        {
            removing = 70;
        }
        while(removing != 0)
        {
            int i = rand() % 9;
            int j = rand() % 9;
            if(sudoku.grille[i][j] != 0)
            {
                sudoku.grille[i][j] = 0;
            }
            removing--;
        }
    }


void entrerValeur (Sudoku& sudoku, int ligne, int colonne, int valeur)
{
    if ( valeur < 1 || valeur > 9 ) {
        std::cout<< " Valeur invalide. Entrez un nombre entre 1 et 9 . " << std::endl;
        return ;
    }
    if( sudoku.grille[ligne][colonne] != 0 ) 
    {
        std::cout<< " Cette case est deja remplie " << std::endl ;
        return ;
    }
    sudoku.grille[ligne][colonne] = valeur;
}

bool resoudreSudoku (Sudoku& sudoku)
{
      for (int i = 0; i < 9; i++) 
      {
        for (int j = 0; j < 9; j++) 
        {
            if (sudoku.grille[i][j] == 0) 
            {
                for (int num = 1; num <= 9; num++) 
                {
                    if (peutresoudre(sudoku, i, j, num)) 
                    {
                        sudoku.grille[i][j] = num; 

                        if (resoudreSudoku(sudoku)) 
                        {
                            return true;
                        }

                        sudoku.grille[i][j] = 0;
                    }
                }
                return false; 
            }
        }
    }
    return true; 
}

    bool peutresoudre(Sudoku& sudoku, int line, int column, int num) 
    {
        for (int i = 0; i < 9; i++) 
        {
            if (sudoku.grille[line][i] == num) 
            {
                return false;
            }
        }


        for (int i = 0; i < 9; i++) 
        {
            if (sudoku.grille[i][column] == num) 
            {
                return false;
            }
        }


        int block_line = line - line % 3;
        int block_column = column - column % 3;
        for (int i = 0; i < 3; i++) 
        {
            for (int j = 0; j < 3; j++) 
            {
                if (sudoku.grille[i + block_line][j + block_column] == num) 
                {
                    return false;
                }
            }
        }

        return true;
    }
    
bool estValide (Sudoku& sudoku, int ligne, int colonne, int valeur)
{
    if ( valeur < 1 || valeur > 9 )
    {
        std::cout<<"Entree incorrecte. Elle doit etre comprise entre 1-9\n";
        return false;
    }

    for (int i = 0; i < 9; i++) 
    {   
        if (sudoku.grille[ligne][i] == valeur) 
        {
            std::cout<<"Cette valeur se trouve deja sur cette ligne\n";
            return false;
        }
    }

    for (int i = 0; i < 9; i++) 
    {
        if (sudoku.grille[i][colonne] == valeur) 
        {
            std::cout<<"Cette valeur se trouve deja sur cette colonne\n";
            return false;
        }
    }


    int block_line = ligne - ligne % 3;
    int block_column = colonne - colonne % 3;
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (sudoku.grille[i + block_line][j + block_column] == valeur) 
            {
                std::cout<<"Cette valeur se trouve deja dans ce block";
                return false;
            }
        }
    }

    return true;
}

void sauvegarderSudoku (Sudoku& sudoku, const char* nomFichier)
{
    std::ofstream file(nomFichier);
    if(file.is_open())
    {
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                file  << sudoku.grille[i][j] << " ";
            }
            file << std::endl;
        }
        file.close();
        std::cout<<"le jeu a ete sauvegarde dans :"<<nomFichier<<std::endl;
    }else
    {
        std::cerr<<"erreur de sauvegarde."<<std::endl;
    }

}

bool chargerSudoku(Sudoku& loadpart, const char* nomFichier )
{
    int place  = 0;
   std::ifstream file(nomFichier);
   if(file.is_open())
   {
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                file >> loadpart.grille[i][j];
            }
        }
        file.close();
        return true;
   }else
   {
        return false;
   }

}

void afficherMenu() 
{
    std::cout << "Bienvenue dans le Jeu de Sudoku ! " << std::endl;
    std::cout << " 1 . Nouveau jeu " << std::endl;
    std::cout << " 2 . Continuer jeu " << std::endl;
    std::cout << " 3 . Resoudre automatiquement " << std::endl;
    std::cout << " 4 . Sauvegarder le jeu " << std::endl ;
    std::cout << " 5 . Charger le jeu sauvegarde " << std::endl;
    std::cout << " 6 . Quitter " << std::endl;
}

void afficherMenu_debut()
{
    std::cout << "Bienvenue dans le Jeu de Sudoku ! " << std::endl;
    std::cout << " 1 . Nouveau jeu " << std::endl;
    std::cout << " 2 . Charger le jeu sauvegarde " << std::endl;
    std::cout << " 3 . Quitter " << std::endl;
}

bool play(Sudoku& sudoku, bool run, int choix)
{
    char main ;
    Sudoku loadpart;
    int column = 0;
    int line = 0;
    int level = 0;
    int valeur = 0;
    afficherSudoku(sudoku);
    bool valid = false;
    std::cout<<"Entrez la colonne ou vous voulez jouer :";
    std::cin>>column;
    std::cout<<"Entrez la ligne ou vous voulez jouer :";
    std::cin>>line;
    std::cout<<"Entrez la valeur que vous allez jouer : ";
    std::cin>>valeur;

    valid = estValide (sudoku, line, column, valeur);

    if(valid)
    {
        entrerValeur(sudoku, line, column, valeur);
    }
    std::cout<<" voulez vous acceder au menu ? (y/n):";
    std::cin>>main; 

    if(main == 'y')
    {
        sauvegarderSudoku (sudoku, "save_file/sudoku_console.txt");
        system("cls");
        afficherMenu(); 
        int choice = 0;
        std::cout<<"choississez une option : ";
        std::cin>>choice;
        switch(choice)
        {
            case 1:
                system("cls");
                initialiserSudoku(sudoku);
                level = 0;
                std::cout<<"Entrez le niveau de difficulte [1-100] : ";
                std::cin>>level;
                genererPuzzle(sudoku,level);
                valeur = 0;
                line = 0;
                column = 0; 
                choix = 1;
                play(sudoku, run, choix);

            break;
            
            case 2:
                system("cls");
                chargerSudoku(loadpart, "save_file/sudoku_console.txt");
                choix = 2;
                play(loadpart, run, choix);
                afficherSudoku(loadpart);
            break;

            case 3:
                system("cls");
                resoudreSudoku(sudoku);
                afficherSudoku(sudoku);
                run = false;
                choix = 3;
            break;

            case 4:
                system("cls");
                sauvegarderSudoku (sudoku, "save_file/sudoku_console.txt");
                return false;
                choix = 3;
            break;

            case 5:
                system("cls");
                chargerSudoku(loadpart, "save_file/sudoku_console.txt");
            break;
            
            case 6:
                quitter(run);
                return false ;
            break;
            
        }
    }
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(sudoku.grille[i][j] == 0)
            {
                if(play(sudoku, run, choix))
                {
                    return true;
                }
                run = false;
                return false;
            }
        }
    }
    return true;
}

void quitter(bool run)
{
    run = false;
}
