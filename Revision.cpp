
#include "Revision.h"

Revision::Revision
(std::string arg_s) : Message { arg_s }
{
  this->revision_time = NULL;
}

Json::Value * Revision::dumpJ
(void)
{
  Json::Value *result_ptr = new Json::Value();
  (*result_ptr)["message"] = this->content;
  if (this->revision_time != NULL)
    {
      std::string * str_ptr =  (this->revision_time)->getTimeString();
      (*result_ptr)["revision_time"] = *str_ptr;
      delete str_ptr;
    }
  return result_ptr;
}
