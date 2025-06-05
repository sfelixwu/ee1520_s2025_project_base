
#ifndef _RECOMMENDATION_H_
#define _RECOMMENDATION_H_

// Recommendation.h
#include "Core.h"
#include "Message.h"
#include "JvTime.h"
#include "Relation.h"

class Recommendation : public Message
{
 private:
 protected:
 public:
  JvTime *expiration;
  std::string keyword;
  Recommendation(std::string arg_s, std::string arg_c, Relation * arg_f, Core * arg_t,
	 std::string arg_k, JvTime * arg_ex);
  virtual Json::Value * dump2JSON(void);
};

#endif /* _RECOMMENDATION_H_ */
