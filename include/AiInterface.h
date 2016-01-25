#ifndef AIINTERFACE_H
#define AIINTERFACE_H

class AiInterface {

public:
  virtual void train(double alpha) = 0;
  virtual void predict() = 0;
};

#endif
