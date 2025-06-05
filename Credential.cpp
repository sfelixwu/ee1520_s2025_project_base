
#include "Credential.h"

Credential::Credential
(std::string arg_s, std::string arg_c, Core * arg_f, Core * arg_t,
 std::string arg_k, JvTime *arg_ex)
{
  this->expiration = arg_ex;
  this->keyword    = arg_k;
}

Json::Value * Credential::dump2JSON
(void)
{
  Json::Value *result_ptr = this->Message::dump2JSON();

  if (this->expiration != NULL)
    {
      std::string * str_ptr =  (this->expiration)->getTimeString();
      (*result_ptr)["expiration"] = *str_ptr;
      delete str_ptr;
    }

  if ((this->keyword).size() > 0)
    {
      (*result_ptr)["keyword"] = this->keyword;
    }

  return result_ptr;
}
