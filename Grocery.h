
#ifndef _GROCERY_H_
#define _GROCERY_H_

#include "Space.h"
#include "Storage.h"

class Grocery: public Space
{
 private:
 protected:
 public:
  std::string store;
  std::map<std::string, Storage *> * sections;

  Grocery(void);
  virtual Json::Value * dumpJ(void);
};

#endif /* _GROCERY_H_ */
