
#include "Grocery.h"

Grocery::Grocery
(void)
{
}

Json::Value * Grocery::dumpJ
(void)
{
  Json::Value *result_ptr = new Json::Value();

  Json::Value *core_ptr = this->Core::dumpJ();
  if (core_ptr != NULL)
    {
      if (((*core_ptr).isNull() != true) &&
	  ((*core_ptr).isObject() == true))
	{
	  (*result_ptr)["core"] = (*core_ptr);
	}
      delete core_ptr;
    }

  if ((this->store).size() > 0)
    (*result_ptr)["store"] = this->store;

  return result_ptr;
}
