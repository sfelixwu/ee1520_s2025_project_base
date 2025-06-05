
#ifndef _REVISION_H_
#define _REVISION_H_

// Revision.h
#include "Message.h"
#include "JvTime.h"

class Revision : public Message
{
 private:
 protected:
 public:
  JvTime *revision_time;
  // Message(std::string arg_s) { this->content = arg_s; this->revision_time = NULL; }
  Revision(std::string arg_s);
  virtual Json::Value * dump2JSON(void);
};

#endif /* _REVISION_H_ */
