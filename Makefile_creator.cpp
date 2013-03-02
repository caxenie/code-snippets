/***************************************************************\
 *                                                             *
 * Ce programme sert à generer un Makefile par default pour un *
 * programme standard.                                         *
 *                                                             *
\***************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

bool FicExiste(const char *Nom)
{
  bool Etat;
  ifstream Fic(Nom);
  Etat = !(Fic.fail());
  Fic.close();
  return Etat;
}


vector<string> GetHeaders(string NomFic)
{
  ifstream Fic(NomFic.c_str());
  string Tampon;
  vector<string> Headers;
  int i, j;

  getline(Fic, Tampon);
  while(!(Fic.eof()))
    {
      if (Tampon.substr(0,10) == string("#include \""))
        {
          for (i = 0; Tampon[i] != '\"'; i++);
          for (j = i+1; Tampon[j] != '\"'; j++);
          Headers.push_back(Tampon.substr(i+1,j-i-1));
        }

      getline(Fic, Tampon);
    }

  Fic.close();
  return Headers;
}


void main(int argc, char** argv)
{
  if (FicExiste("Makefile") || FicExiste("makefile"))
    {
      cout << "Il existe deja un Makefile dans ce repertoire." << endl;
      exit(1);
    }

  if (argc == 1)
    {
      cout << "Aucun fichier n'a ete entre." << endl;
      exit(1);
    }

  ofstream FicSortie("Makefile");


  // Ecriture des standards dans un Makefile
  FicSortie << "CC=" << endl
            << "CFLAGS=" << endl
            << "LIBS=" << endl
            << "TARGET=" << endl << endl
            << "all: $(TARGET)" << endl << endl
            << "rebuilt:" << endl
            << '\t' << "make clean" << endl
            << '\t' << "make all" << endl << endl;

  int i, j;
  vector<string> LesFics;
  vector<string> LesNoms;

  // Identification des fichiers valides
  for (i = 1; i < argc; i++)
    {
      if (FicExiste(argv[i]))
        {
          LesFics.push_back(string(argv[i]));
          for (j = LesFics[LesFics.size()-1].size();
               LesFics[LesFics.size()-1][j] != '.'; j--);
          LesNoms.push_back(LesFics[LesFics.size()-1].substr(0,j));
        }
      else
        cout << "Le fichier " << argv[i] << " n'existe pas." << endl;
    }


  // Pour la compilation du programme final
  FicSortie << "$(TARGET): ";
  for (i = 0; i < LesFics.size(); i++)
    {
      FicSortie << LesNoms[i] << ".o";
      if (i != LesFics.size() - 1)
        FicSortie << ' ';
    }
  FicSortie << endl << '\t' << "$(CC) ";

  for (i = 0; i < LesNoms.size(); i++)
    FicSortie << LesNoms[i] << ".o ";

  FicSortie << "$(LIBS) -o $(TARGET)" << endl << endl;



  // Pour la compilation de chacun des .cpp
  for (i = 0; i < LesNoms.size(); i++)
    {
      vector<string> Headers = GetHeaders(LesFics[i]);
      FicSortie << LesNoms[i] << ".o: " << LesFics[i];
      for (j = 0; j < Headers.size(); j++)
        FicSortie << ' ' << Headers[j];

      FicSortie << endl << '\t' << "$(CC) $(CFLAGS) "
                << LesFics[i] << " -c -o "
                << LesNoms[i] << ".o" << endl << endl;
    }


  // Ecriture des standards dans un makefile
  FicSortie << endl << endl << ".PHONY: clean rebuilt" << endl << endl
            << "clean:" << endl
            << '\t' << "rm -f ./*.o" << endl
            << '\t' << "rm -f ./*~" << endl
            << '\t' << "rm -f ./$(TARGET)" << endl;

  FicSortie.close();
}
