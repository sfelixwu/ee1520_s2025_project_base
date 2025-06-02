
#include "Product.h"

Product::Product
(void)
{
}

Product::Product
(std::string arg_grp_id, std::string arg_upc14, std::string arg_upc12,
 std::string arg_brand, std::string arg_name)
  : grp_id { arg_grp_id }, upc14 { arg_upc14 }, upc12 { arg_upc12 },
  brand { arg_brand }, name { arg_name }
{
}

Json::Value * Product::dumpJ
(void)
{
  Json::Value *result_ptr = new Json::Value();
  if ((this->grp_id).size() > 0)
    (*result_ptr)["grp_id"] = this->grp_id;
  if ((this->upc14).size() > 0)
    (*result_ptr)["upc14"] = this->upc14;
  if ((this->upc12).size() > 0)
    (*result_ptr)["upc12"] = this->upc12;
  if ((this->brand).size() > 0)
    (*result_ptr)["brand"] = this->brand;
  if ((this->name).size() > 0)
    (*result_ptr)["name"] = this->name;
#ifdef _ECS36B_DEBUG_
  std::cout << result->toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
  return result_ptr;
}
