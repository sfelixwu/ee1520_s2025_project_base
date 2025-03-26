
#include <iostream>

#include "ee1520_Common.h"
#include "ee1520_Exception.h"

using namespace std;

int
main
(int argc, char *argv[])
{
  if (argc != 2)
    {
      char arg_string[] = " <team log>";
      std::cout << "usage: " << argv[0] << arg_string << std::endl; 
      return -1;
    }

  FILE *f_ptr = fopen(argv[1], "r");
  if (f_ptr == NULL) exit(-1);

  Json::Value teams;
  
  char read_buf_1[4096];
  char read_buf_2[4096];
  char read_buf_3[8192];

  int array_index = 0;
  int rc;
  
  while (1)
    {
      bzero(read_buf_1, 4096);
      rc = fscanf(f_ptr, "%[^]]", read_buf_1);
      if (rc == EOF) break;

      rc = fgetc(f_ptr);
      if (rc == EOF) break;

      bzero(read_buf_1, 4096);
      rc = fscanf(f_ptr, "%[^[]", read_buf_1);
      if (rc == EOF) break;

      rc = fgetc(f_ptr);
      if (rc == EOF) break;

      bzero(read_buf_2, 4096);
      rc = fscanf(f_ptr, "%[^[]", read_buf_2);
      if (rc == EOF) break;

      bzero(read_buf_3, 8192);
      snprintf(read_buf_3, strlen(read_buf_1) + 1 + strlen(read_buf_2),
	       "%s[%s", read_buf_1, read_buf_2);

      Json::Value jv;
      rc = myParseJSON(read_buf_3, &jv);
      if (rc != 0)
	{
	  printf("error %s\n", read_buf_3);
	}
      else
	{
	  teams[array_index] = jv["registration"];
	  array_index++;
	}
    }

  std::cout << teams << std::endl;
  return 0;
}
