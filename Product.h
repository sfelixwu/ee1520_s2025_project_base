
#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include "Core.h"

class Product
{
 private:
 protected:
 public:
  std::string keyword;
  std::string grp_id;
  std::string upc14;
  std::string upc12;
  std::string brand;
  std::string name;
  
  Product(void);
  Product(std::string arg_grp_id, std::string arg_upc14, std::string arg_upc12,
	  std::string arg_brand, std::string arg_name);
  virtual Json::Value * dump2JSON(void);
};

#endif /* _PRODUCT_H_ */
