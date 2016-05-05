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
  int index;
  int c;

  string dataset;
  int nbMovies, nbUsers, nbGenres;
  double lambda, alpha;

  string datasets;
  int nbDataSets, nbLignesSurUnJeu;

  dataset = "data/u1";
  nbMovies = 1682;
  nbUsers = 943;
  nbGenres = 19;
  lambda = 5/100;
  alpha = 0.0001;

  datasets = "data/u";
  nbDataSets = 5;
  nbLignesSurUnJeu = 20000;

  opterr = 0;
  while ((c = getopt (argc, argv, "TSVZ:")) != -1)
    switch (c)
      {
      case 'T':
        {
        if(argc < 3){
          cout << "Dataset par défaut: " << dataset <<endl;
        }
        else{
          dataset = argv[2];
          nbMovies = stoi(argv[3]);
          nbUsers = stoi(argv[4]);
          nbGenres = stoi(argv[5]);
          cout << "Dataset: " << dataset <<endl;
        }
        if(argc > 5){
          lambda = stod(argv[6]);
          alpha = stod(argv[7]);
        }
        MovieRecommender *mr = new MovieRecommender(dataset, nbMovies, nbUsers, nbGenres);
        mr->train(alpha,lambda);
        break;
        }
      case 'S':
        {
        if(argc < 3){
          cout << "Dataset par défaut: " << dataset <<endl;
        }
        else{
          dataset = argv[2];
          cout << "Dataset: " << dataset <<endl;
        }
        Saver s = Saver(dataset);
        MovieRecommender *mr2 = new MovieRecommender(dataset, s);
        vector<string> reco = mr2->recommend(12, 5);
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

  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  return 0;
}
