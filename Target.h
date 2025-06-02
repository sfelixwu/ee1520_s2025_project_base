
#ifndef _TARGET_H_
#define _TARGET_H_

#include "Core.h"
#include "JvTime.h"
#include "Person.h"
#include "Relation.h"
#include "Transaction.h"
#include "OKey.h"

class Target : public Core
{
 private:
 protected:
 public:
  GPS_DD * location;
  std::vector<Transaction *> * history;
  
  Target(void);
  virtual Json::Value * dumpJ(void);
};

#endif /* _TARGET_H_ */
