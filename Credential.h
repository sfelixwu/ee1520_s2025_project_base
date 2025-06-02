
#ifndef _CREDENTIAL_H_
#define _CREDENTIAL_H_

// Credential.h
#include "Core.h"
#include "Message.h"
#include "JvTime.h"

class Credential : public Message
{
 private:
 protected:
 public:
  JvTime *expiration;
  std::string keyword;
  Credential(std::string arg_s, std::string arg_c, Core * arg_f, Core * arg_t,
	 std::string arg_k, JvTime * arg_ex);
  virtual Json::Value * dumpJ(void);
};

#endif /* _CREDENTIAL_H_ */
