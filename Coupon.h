
#ifndef _COUPON_H_
#define _COUPON_H_

// Coupon.h
#include "Core.h"
#include "Message.h"
#include "JvTime.h"
#include "Product.h"

class Coupon : public Message
{
 private:
 protected:
 public:
  JvTime *expiration;
  Product *product;
  double discount;
  Coupon(std::string arg_s, std::string arg_c, Core * arg_f, Core * arg_t,
	 Product * arg_p, JvTime * arg_ex, double arg_discount);
  virtual Json::Value * dump2JSON(void);
};

#endif /* _COUPON_H_ */
