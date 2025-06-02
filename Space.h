
#ifndef _SPACE_H_
#define _SPACE_H_

#include "Target.h"

class Space : public Target
{
 private:
 protected:
 public:
  std::map<Person *, std::string> * people;

  Space(void);
  virtual Json::Value * dumpJ(void);
};

#endif /* _SPACE_H_ */
