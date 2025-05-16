
#include <iostream>

// JSON RPC part
#include <stdlib.h>
#include "ee1520BUSclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

#include "Locatable_Thing.h"
#include "Traceable_Person.h"

using namespace jsonrpc;
using namespace std;

int
main
(int argc, char *argv[])
{
  if (argc != 2)
    {
      char arg_string[] = "<json_list_directory>";
      std::cout << "usage: " << argv[0] << arg_string << std::endl; 
      return -1;
    }

  // start
  Json::Value jv;
  int rc = myFile2JSON(argv[1], &jv);

  fprintf(stdout, "rc = %d\n", rc);
  // std::cout << jv << std::endl;
  
  // vector<basic_string<char, char_traits<char>, std::allocator<char>>> members;
  vector<std::string> members;
  members = jv.getMemberNames();
  int k;
  for (k = 0; k < members.size(); k++)
    {
      // fprintf(stdout, "%d\n", k);
      // std::cout << members[k] << std::endl;
      // fflush(stdout);
    }

  Exception_Info * ei_ptr = NULL;
  ee1520_Exception * lv_exception_ptr = new ee1520_Exception {};
  
  Post * post_ptr = new Post((Person *) NULL, (Message *) NULL);
  try
    {
      printf("update Here 1\n");
      post_ptr->JSON2Object(&jv);
      printf("update Here 2\n");
    }
  catch(ee1520_Exception& e)
    {
      std::cout << "post JSON2Object exception\n";
      JSON2Object_appendEI(e, lv_exception_ptr, 0);
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      std::cout << (lv_exception_ptr->info_vector).size() << std::endl;
      std::cout << *(lv_exception_ptr->dump2JSON()) << std::endl;
      lv_exception_ptr->myDestructor();
    }

  // Json::Value *jv2 = post_ptr->dump2JSON();
  // if (jv2 != NULL)
  // {
      // std::cout << *jv2 << std::endl;
  // }
  // else
  // {
      // printf("jv2 NULL\n");
  // }
  //  delete post_ptr;
  //  std::cout << jv << std::endl;
  //  return 0;
  
  HttpClient httpclient("https://ethikos.ngrok.io");
  // HttpClient httpclient("http://localhost:8384");
  // HttpClient httpclient("http://169.237.6.102:55407");
  // HttpClient httpclient("http://169.237.6.102:55408");
  ee1520Client myClient(httpclient, JSONRPC_CLIENT_V2);

  Json::Value result_json;

  try {
    // std::cout << (post_ptr->dump2JSON())->toStyledString() << std::endl;
    // result_json = myClient.update((post_ptr->dump2JSON())->toStyledString());
    result_json = myClient.update(jv.toStyledString());
    std::cout << result_json.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  return 0;
}
