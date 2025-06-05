
#include "IP.h"

IP_Address::IP_Address()
{
}

IP_Address::IP_Address
(unsigned int arg_ip)
{
  this->addr = arg_ip;
}

std::string SDefault {"Default"};

std::string&
IP_Address::getIPaddressString()
{  
  return SDefault;
}

unsigned int
IP_Address::getIPaddressValue()
{
  return addr;
}

Json::Value *
IP_Address::dump2JSON
()
{
  Json::Value * result_ptr = new Json::Value();

  struct in_addr my_in;
  my_in.s_addr = addr;
  char *ip_ch = inet_ntoa(my_in);
  std::string ip_str { ip_ch };

  (*result_ptr)["IPv4"] = ip_str;

#ifdef _ECS36B_DEBUG_
  std::cout << result_ptr->toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
  return result_ptr;
}
