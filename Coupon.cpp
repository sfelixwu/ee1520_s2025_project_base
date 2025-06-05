
#include "Coupon.h"

Coupon::Coupon
(std::string arg_s, std::string arg_c, Core * arg_f, Core * arg_t,
 Product *arg_p, JvTime *arg_ex, double arg_discount)
{
  this->expiration = arg_ex;
  this->product = arg_p;
  if ((arg_discount < 1.0) && (arg_discount >= 0.0))
    this->discount = arg_discount;
  else
    this->discount = 1.0;
}

Json::Value * Coupon::dump2JSON
(void)
{
  // Json::Value *result_ptr = this->Message::dump2JSON();
  Json::Value *result_ptr = new Json::Value();

  if (this->expiration != NULL)
    {
      std::string * str_ptr =  (this->expiration)->getTimeString();
      (*result_ptr)["expiration"] = *str_ptr;
      delete str_ptr;
    }

  if (this->product != NULL)
    {
      Json::Value jv = *((this->product)->dump2JSON());
      if ((jv.isNull() != true) &&
	  (jv.isObject() == true))
	(*result_ptr)["product"] = jv;
    }

  (*result_ptr)["discount"] = this->discount;
  (*result_ptr)["subject"]  = "Coupon";
  (*result_ptr)["content"]  = "Coupon";

  return result_ptr;
}
