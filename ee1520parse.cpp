
#include <iostream>

// JSON RPC part
#include <stdlib.h>
#include "ee1520client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

#include "Post.h"

using namespace jsonrpc;
using namespace std;

int
main
(int argc, char *argv[])
{
  if (argc != 2)
    {
      char arg_string[] = " <parsing_json>";
      std::cout << "usage: " << argv[0] << arg_string << std::endl; 
      return -1;
    }

  // getting the JSON to be parsed
  Json::Value jv;
  int rc = myFile2JSON(argv[1], &jv);
  fprintf(stdout, "rc = %d\n", rc);

  Exception_Info * ei_ptr = NULL;
  ee1520_Exception lv_exception;
  ee1520_Exception * lv_exception_ptr = &lv_exception;
  
  Post * post_ptr = new Post((Person *) NULL, (Message *) NULL);
  try
    {
      post_ptr->JSON2Object(&jv);
    }
  catch(ee1520_Exception& e)
    {
      JSON2Object_appendEI(e, lv_exception_ptr, 0);
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      std::cout << (lv_exception_ptr->info_vector).size() << std::endl;
      std::cout << *(lv_exception_ptr->dump2JSON()) << std::endl;
      lv_exception_ptr->myDestructor();
    }

  return 0;
}
