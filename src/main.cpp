#include "DataParser.h"
#include "Saver.h"
#include "MovieRecommender.h"
#include "Vector3.h"
#include "Validator.h"
#include <gsl/gsl_matrix.h>
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int
main (int argc, char **argv)
{
  int c;

  string dataset;
  int nbMovies, nbUsers, nbGenres;
  double alpha, lambda;

  string datasets;
  int nbDataSets, nbLignesSurUnJeu;

  int idUser, nbRecommend;

  dataset = "data/u1";
  nbMovies = 1682;
  nbUsers = 943;
  nbGenres = 19;
  alpha = 0.0001;
  lambda = 5.0/100.0;

  datasets = "data/u";
  nbDataSets = 5;
  nbLignesSurUnJeu = 20000;

  idUser = 13;
  nbRecommend = 5;

  cout << "Nombres d'argument :" << argc <<endl;
  opterr = 0;
  while ((c = getopt (argc, argv, "TSVRZ:")) != -1)
    switch (c)
      {
      case 'T':
        {
        if(argc < 3){
          cout << "Dataset par défaut: " << dataset <<endl;
        }
        else if (argc == 6){
          dataset = argv[2];
          nbMovies = stoi(argv[3]);
          nbUsers = stoi(argv[4]);
          nbGenres = stoi(argv[5]);
          cout << "Dataset: " << dataset <<endl;
        }
        else{
          dataset = argv[2];
          nbMovies = stoi(argv[3]);
          nbUsers = stoi(argv[4]);
          nbGenres = stoi(argv[5]);
          cout << "Dataset: " << dataset <<endl;
          alpha = stod(argv[6]);
          lambda = stod(argv[7]);
        }
        cout << "nbMovies: "<< nbMovies << " | nbUsers: " << nbUsers << " | nbGenres: " << nbGenres << endl;
        cout << "lambda: " << lambda << " | alpha: "<< alpha << endl;
        MovieRecommender *mr = new MovieRecommender(dataset, nbMovies, nbUsers, nbGenres);
        mr->train(alpha,lambda);
        break;
        }
      case 'S':
        {
        if(argc < 3){
          cout << "Dataset par défaut: " << dataset <<endl;
        }
        else if(argc == 3){
          dataset = argv[2];
          cout << "Dataset: " << dataset <<endl;
        }
        else{
          dataset = argv[2];
          alpha = stod(argv[3]);
          lambda = stod(argv[4]);
        }
        cout << "lambda: " << lambda << " | alpha: "<< alpha << endl;
        Saver s = Saver(dataset);
        MovieRecommender *mr2 = new MovieRecommender(dataset, s);
        mr2->train(alpha, lambda);
        break;
        }
      case 'V':
        {
        if(argc < 3){
          cout << "Datasets par défaut: " << datasets <<endl;
        }
        else{
          datasets = argv[2];
          nbDataSets = stoi(argv[3]);
          nbLignesSurUnJeu = stoi(argv[4]);
        }
        Validator v = Validator(datasets, nbDataSets, nbLignesSurUnJeu);
        v.startRMSE();
        break;
        }
      case 'R' :
        {
        if(argc < 3){
          cout << "Dataset par défaut: " << dataset <<endl;
        }
        else{
          dataset = argv[2];
          idUser = stoi(argv[3]);
          nbRecommend = stoi(argv[4]);
          cout << "Dataset: " << dataset <<endl;
        }
        Saver s = Saver(dataset);
        MovieRecommender *mr2 = new MovieRecommender(dataset, s);
        vector<string> reco = mr2->recommend(idUser, nbRecommend);
        for(unsigned int i = 0; i < reco.size(); ++i) {
          cout << reco[i] << endl;
        }
        break;
        }
      case '?':
        if (optopt == 'Z')
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }
  return 0;
}
