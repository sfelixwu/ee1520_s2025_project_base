
#ifndef _STORAGE_H_
#define _STORAGE_H_

#include "Target.h"
#include "Item.h"
#include "Space.h"

class Item;
class Storage;

class Storage : public Target
{
 private:
 protected:
 public:
  Space *place;
  std::vector<Item         *> * content;

  Storage(void);
  virtual Json::Value * dumpJ(void);
  virtual std::vector<Person *> * whoAccessed(void);
};

#endif /* _STORAGE_H_ */
