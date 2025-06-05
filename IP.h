
#ifndef _IP_H_
#define _IP_H_

// IP.h

#include "Core.h"

class IP_Address
{
 private:
  unsigned int addr;
 public:
  IP_Address();
  IP_Address(unsigned int);
  std::string& getIPaddressString();
  unsigned int getIPaddressValue();
  virtual Json::Value * dump2JSON();
};

#endif  /* _IP_H_ */
