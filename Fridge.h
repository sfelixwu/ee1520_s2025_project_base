
#ifndef _FRIDGE_H_
#define _FRIDGE_H_

#include "Storage.h"

class Fridge : public Storage
{
 private:
 protected:
 public:
  Fridge(void);
  virtual Json::Value * dump2JSON(void);
};

#endif /* _FRIDGE_H_ */
