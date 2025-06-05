
#ifndef _ITEM_H_
#define _ITEM_H_

#include "Target.h"
#include "Product.h"
#include "Storage.h"

class Item;
class Storage;

class Item : public Target
{
 private:
 protected:
 public:
  std::string id;
  Product * product;
  Storage * current;
  Storage * next;
  double ratio;
  
  Item(void);
  virtual Json::Value * dump2JSON(void);
};

#endif /* _ITEM_H_ */
