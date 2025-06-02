
#include "Credential.h"

Credential::Credential
(std::string arg_s, std::string arg_c, Core * arg_f, Core * arg_t,
 std::string arg_k, JvTime *arg_ex)
  : Message { arg_s, arg_c, arg_f, arg_t }
{
  this->expiration = arg_ex;
  this->keyword    = arg_k;
}

Json::Value * Credential::dumpJ
(void)
{
  Json::Value *result_ptr = this->Message::dumpJ();

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
