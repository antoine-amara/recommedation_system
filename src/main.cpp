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

  nbMovies = 1682;
  nbUsers = 943;
  nbGenres = 19;
  lambda = 5/100;
  alpha = 0.0001;

  opterr = 0;
  while ((c = getopt (argc, argv, "TSVZ:")) != -1)
    switch (c)
      {
      case 'T':
        {
        if(argc < 3){
          dataset = "data/u1";
          cout << "Dataset par défaut: " << dataset <<endl;
        }
        else{
          dataset = argv[2];
          cout << "Dataset: " << dataset <<endl;
        }
        MovieRecommender *mr = new MovieRecommender(dataset, nbMovies, nbUsers, nbGenres);
        mr->train(alpha,lambda);
        break;
        }
      case 'S':
        {
        Saver s = Saver("data/u1");
        MovieRecommender *mr2 = new MovieRecommender("data/u1", s);
        vector<string> reco = mr2->recommend(12, 5);
        break;
        }
      case 'V':
        {
        Validator v = Validator("data/u", 5, 20000);
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
