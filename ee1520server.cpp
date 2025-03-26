
#include "Post.h"
#include "ee1520server.h"
#include "ee1520client.h"
#include "Personal_Timed_GPS_Record.h"

#include <jsonrpccpp/server/connectors/httpserver.h>

extern const char *ee1520_errors[];

using namespace jsonrpc;
using namespace std;

class Myee1520Server : public ee1520Server
{
public:
  Myee1520Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value update(const std::string& updating_json);
  virtual Json::Value search(const std::string& search_clause);
  virtual Json::Value upload(const Json::Value& updating_json);
  virtual Json::Value question(const Json::Value& question_json);
  virtual Json::Value dump2json(const std::string& identity);
};

Myee1520Server::Myee1520Server(AbstractServerConnector &connector, serverVersion_t type)
  : ee1520Server(connector, type)
{
  std::cout << "Myee1520Server Object created" << std::endl;
}

// member functions

#define BUFSIZE 1024

Json::Value
Myee1520Server::update(const std::string& updating_json)
{
  Json::Value result_json;
  char fname_buf[BUFSIZE];
  FILE * post_f_ptr;
  
  int rc = EE1520_ERROR_NORMAL;
  bool brc = false;
  
  Post * post_ptr = NULL;
  unsigned int exception_count = 0;
  
  std::cout << "update" << " " << updating_json << std::endl;

#ifdef _EE1520_DEBUG_
#endif /* _EE1520_DEBUG_ */

  Exception_Info * ei_ptr = NULL;
  ee1520_Exception lv_exception {};
  ee1520_Exception * lv_exception_ptr = &lv_exception;

  try
    {
      if ((updating_json.c_str())[0] != '{')
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "update first character";
	  ei_ptr->how_code = EE1520_ERROR_NORMAL;
	  ei_ptr->what_code = EE1520_ERROR_JSON_PARSING;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}
      
      myPrintLog(updating_json, "ee1520server_update.log");

      Json::Value myv_message;
      rc = checkBigID(updating_json);
      if (rc != EE1520_ERROR_NORMAL)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "update check Big ID";
	  ei_ptr->how_code = EE1520_ERROR_NORMAL;
	  ei_ptr->what_code = rc;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}

      // printf("server Here 1\n");
      rc = myParseJSON(updating_json, &myv_message);
      if (rc != EE1520_ERROR_NORMAL)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "update parse JSON";
	  ei_ptr->how_code = EE1520_ERROR_NORMAL;
	  ei_ptr->what_code = rc;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}

      // set the json_post file name
      if (((myv_message["id"]).isNull() == true) &&
	  ((myv_message["id"]).isString() == false) &&
	  (checkPostID((myv_message["id"]).asString()) != 0))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "update check Post ID";
	  ei_ptr->how_code = EE1520_ERROR_NORMAL;
	  ei_ptr->what_code = EE1520_ERROR_JSON_POST_NO_ID;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}

      bzero(fname_buf, BUFSIZE);
      snprintf(fname_buf,
	       strlen("./posts/post_.json") +
	       strlen(((myv_message["id"]).asString()).c_str()) + 1,
	       "./posts/post_%s.json", ((myv_message["id"]).asString()).c_str());
  
      // std::cout << "name: " << fname_buf << std::endl;
      
      // check vsID portion of id
      {
	char idstr[BUFSIZE];
	bzero(idstr, BUFSIZE);
	snprintf(idstr, strlen(((myv_message["id"]).asString()).c_str()) + 1,
		 "%s", ((myv_message["id"]).asString()).c_str());

	char c_prof_buf[BUFSIZE];
	char c_post_buf[BUFSIZE];
	bzero(c_prof_buf, BUFSIZE);
	bzero(c_post_buf, BUFSIZE);
	sscanf(idstr, "%[^_]_%s", c_prof_buf, c_post_buf);
	std::string s_vsID { c_prof_buf };
      }

      // printf("server Here 2\n");
      post_ptr = new Post((Person *) NULL, (Message *) NULL);

      Json::Value pjf_v;
      rc = myFile2JSON(fname_buf, &pjf_v);

      // printf("server Here 3\n");

      if ((rc != EE1520_ERROR_NORMAL) &&
	  (rc != EE1520_ERROR_FILE_NOT_EXIST))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "update File2JSON from file";
	  ei_ptr->how_code = EE1520_ERROR_NORMAL;
	  ei_ptr->what_code = rc;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}
      else
	{
	  try
	    {
	      // parsing the existing JSON Object copy, under ./posts/post...
	      // printf("server Here 4\n");
	      post_ptr->JSON2Object(&pjf_v);
	      // printf("server Here 5\n");
	    }
	  catch(ee1520_Exception& e)
	    {
	      // printf("server Here 6\n");
	      JSON2Object_appendEI(e, lv_exception_ptr, 0);
	    }
	}

      // std::cout << (&myv_message) << std::endl;      
      try
	{
	  // now the new object, perhaps merged
	  // printf("ee1520server before Post::JSON2Object 04\n");
	  // fflush(stdout);
	  post_ptr->JSON2Object(&myv_message);
	  // printf("ee1520server after  Post::JSON2Object 05\n");
	  // fflush(stdout);
	}
      catch(ee1520_Exception& e)
	{
	  // printf("after  Post::JSON2Object 06\n");
	  // fflush(stdout);
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
	}
      
      // try to get the keys (to the key files)
      if (post_ptr->keys == NULL)
	{
	  post_ptr->keys = new vector<OKey *> ();
	}
      
      // printf("Here 1\n");
      int ki;
      for (ki = 0; ki < (post_ptr->keys)->size(); ki++)
	{
	  // printf("Here 2\n");
	  FILE *okey_f   = NULL;
	  int found_flag = 0;
	  int null_flag  = 1; // usually new okey

	  OKey * okey_ptr = (*(post_ptr->keys))[ki];
	  
	  char fn_buf[256];
	  bzero(fn_buf, 256);
	  snprintf(fn_buf, strlen("./okeys/okey_.list") + strlen((okey_ptr->okey).c_str()) + 1,
		   "./okeys/okey_%s.list", (okey_ptr->okey).c_str());

	  // std::cout << fn_buf << std::endl;
	  std::string target_buf = (post_ptr->id).get();
	  // std::cout << target_buf << std::endl;

	  // printf("Here 2.1\n");
	  okey_f = fopen(fn_buf, "r");

	  if (okey_f != NULL)
	    {
	      // printf("Here 2.2\n");
	      null_flag = 0;
	      char post_id_buf[1024];
	      int okey_loop_flag = 1;
	      while (okey_loop_flag)
		{
		  // printf("Here 2.3\n");

		  bzero(post_id_buf, 1024);
		  int rc = fscanf(okey_f, "%[^\n]", post_id_buf);
		  if (rc == EOF)
		    {
		      okey_loop_flag = 0; // leaving the loop
		    }
		  else
		    {
		      // std::cout << post_id_buf << std::endl;
		      if (strcmp(target_buf.c_str(), post_id_buf) == 0)
			{
			  found_flag = 1;
			  okey_loop_flag = 0;
			}
		    }
		  fgetc(okey_f);
		}
	      fclose(okey_f);
	    }
	  // printf("Here 2.4\n");

	  if ((null_flag == 1) || (found_flag == 0))
	    {
	      // printf("Here 2.5\n");

	      FILE *okey_f = fopen(fn_buf, "a");
	      if (okey_f != NULL)
		{
		  fprintf(okey_f, "%s\n", ((post_ptr->id).get()).c_str());
		  fclose(okey_f);
		}
	      else
		{
		  // throw...
		  std::cout << "need to throw okey\n";
		}
	      // printf("Here 2.6\n");
	    }
	  // printf("Here 2.7\n");
	}

      // printf("Here 2.8\n");
      if ((lv_exception_ptr->info_vector).size() != 0)
	{
	  exception_count = (lv_exception_ptr->info_vector).size();
	  // std::cout << exception_count << std::endl;
	  // std::cout << *(lv_exception_ptr->dump2JSON()) << std::endl;
	  throw (*lv_exception_ptr);
	}
      // printf("Here 2.85\n");
    }
  catch (ee1520_Exception& e)
    {
      // printf("Here 2.9\n");
      int erc = produceErrorJSON(e, "ee1520server_update.log", &result_json, 0);
      if (erc != EE1520_ERROR_NORMAL)
	myPrintLog("{\"location\":\"produce Error catch\"}", "ee1520server_update.log");
    }

  // printf("Here 2.10\n");
  // write it back
  // std::cout << fname_buf <<  std::endl;
  if (post_ptr == NULL)
    {
      myPrintLog("{\"location\":\"before write back POST_PTR null\"}", "ee1520server_update.log");
      return result_json;
    }

  // printf("Here 2.110 [%p]\n", post_ptr);
  Json::Value *rj_ptr = post_ptr->dump2JSON();
  // printf("Here 2.115 [%p]\n", post_ptr);
  // std::cout << exception_count << std::endl;
  (*rj_ptr)["exception count"] = exception_count;
  if (exception_count > 0)
    {
      (*rj_ptr)["exceptions"] = *(lv_exception.dump2JSON());
    }
  // printf("Here 2.116 [%p]\n", post_ptr);

  // printf("Here 2.12\n");
  result_json = (*rj_ptr);
  std::cout << result_json << std::endl;
  (*rj_ptr)["JSON2Object"] = post_ptr->J2O_input;
  rc = myJSON2File(fname_buf, rj_ptr);
  myPrintLog((rj_ptr->toStyledString()).c_str(),
	     "ee1520server_update.log");
  delete rj_ptr;
  // strange *** resolved
  delete post_ptr;
  // printf("Here 2.13\n");

  return result_json;
}

int
simpleChecksum
(const char *data, int length)
{
  int *int_ptr = (int *) data;
  int int_array_size = length / sizeof(int);
  int i;
  int result = 95616; // very weak key
  for (i = 0; i < int_array_size; i++)
    {
      result ^= int_ptr[i];
    }
  return result;
}

Json::Value
Myee1520Server::search
(const std::string& search_clause)
{
  Json::Value result_json;
  int rc = EE1520_ERROR_NORMAL;
  bool brc = false;

  std::cout << "search" << " " << search_clause << std::endl;

#ifdef _EE1520_DEBUG_
#endif /* _EE1520_DEBUG_ */

  Exception_Info * ei_ptr = NULL;
  ee1520_Exception * lv_exception_ptr = new ee1520_Exception {};

  try
    {
      if ((search_clause.c_str())[0] != '{')
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "search first character";
	  ei_ptr->how_code = EE1520_ERROR_NORMAL;
	  ei_ptr->what_code = EE1520_ERROR_JSON_PARSING;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}
      myPrintLog(search_clause, "ee1520server_search.log");

      Json::Value myv_message;
      rc = myParseJSON(search_clause, &myv_message);
      if (rc != EE1520_ERROR_NORMAL)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "search clause parse";
	  ei_ptr->how_code = EE1520_ERROR_NORMAL;
	  ei_ptr->what_code = rc;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}

      if (myv_message.isObject() != true)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "search clause not object";
	  ei_ptr->how_code = EE1520_ERROR_NORMAL;
	  ei_ptr->what_code = EE1520_ERROR_BAD_KEYWORD_FORMAT;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}

      if (((myv_message["keyword"]).isNull() == true) &&
	  ((myv_message["id"]).isNull() == true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "search clause keyword null";
	  ei_ptr->how_code = EE1520_ERROR_NORMAL;
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_MISSING;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}
      
      int  post_count = 0;
      Json::Value json_data;

      if ((myv_message["keyword"]).isNull() == false)
	{
	  if ((myv_message["keyword"]).isString() == false)
	    {
	      ei_ptr = new Exception_Info {};
	      ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	      ei_ptr->which_string = "search clause keyword null";
	      ei_ptr->how_code = EE1520_ERROR_NORMAL;
	      ei_ptr->what_code = EE1520_ERROR_JSON_KEY_TYPE_MISMATCHED;
	      (lv_exception_ptr->info_vector).push_back(ei_ptr);
	      throw (*lv_exception_ptr);
	    }

	  // let us check if there is file around for this keyword
	  // adding the post_id to the Keyword object file

	  char fn_buf[256];
	  bzero(fn_buf, 256);

	  // bug: const char * test_str = ((myv_message["keyword"]).asString()).c_str();

	  char test_str[1024];
	  bzero(test_str, 1024);
	  snprintf(test_str, strlen((myv_message["keyword"]).asString().c_str()) + 1,
		   "%s", ((myv_message["keyword"]).asString()).c_str());

	  // coverting the keyword to lower case
	  char cbuf[1024];
	  bzero(cbuf, 1024);

	  int ii;
	  for (ii = 0; ii < strlen(test_str); ii++)
	    {
	      if ((test_str[ii] >= 'A') && (test_str[ii] <= 'Z'))
		cbuf[ii] = tolower(test_str[ii]);
	      else
		cbuf[ii] = test_str[ii];	    
	    }

	  snprintf(fn_buf, strlen("./okeys/okey_.list") + strlen(cbuf) + 1,
		   "./okeys/okey_%s.list", cbuf);

	  printf("Keyword file is [%s]\n", fn_buf);
	  
	  std::string s = fn_buf;
	  myPrintLog(s, "ee1520server_search.log");

	  FILE *okey_f = fopen(fn_buf, "r");
	  if (okey_f == NULL)
	    {
	      ei_ptr = new Exception_Info {};
	      ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	      ei_ptr->which_string = "search clause okey file null";
	      ei_ptr->how_code = EE1520_ERROR_NORMAL;
	      ei_ptr->what_code = EE1520_ERROR_NO_OKEY;
	      (lv_exception_ptr->info_vector).push_back(ei_ptr);
	      throw (*lv_exception_ptr);
	    }

	  char post_id_buf[1024];
	  int  okey_flag  = 1;

	  while(okey_flag)
	    {
	      bzero(post_id_buf, 1024);
	      int f_rc = fscanf(okey_f, "%[^\n]", post_id_buf);
	      std::cout << post_id_buf << std::endl;
	      std::string post_id_string = post_id_buf;
	      
	      if (f_rc == EOF)
		{
		  okey_flag = 0; // leaving the loop
		}
	      else
		{
		  if (checkPostID(post_id_string) == 0)
		    {
		      char pfn_buf[1024];
		      bzero(pfn_buf, 1024);
		      snprintf(pfn_buf, strlen("./posts/post_.json") + strlen(post_id_buf) + 1,
			       "./posts/post_%s.json", post_id_buf);
		      std::cout << pfn_buf << std::endl;

		      Json::Value pjf_v;
		      rc = myFile2JSON(pfn_buf, &pjf_v);
		      if (rc != EE1520_ERROR_NORMAL)
			{
			  ei_ptr = new Exception_Info {};
			  ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
			  ei_ptr->which_string = "search clause post myFile2JSON";
			  ei_ptr->how_code = EE1520_ERROR_NORMAL;
			  ei_ptr->what_code = rc;
			  (lv_exception_ptr->info_vector).push_back(ei_ptr);
			}
		      else
			{
			  Post *post_ptr = new Post((Person *) NULL, (Message *) NULL);
			  try
			    {
			      post_ptr->JSON2Object(&pjf_v);
			    }
			  catch(ee1520_Exception e)
			    {
			      JSON2Object_appendEI(e, lv_exception_ptr, 0);
			    }
			  // add to the result data
			  Json::Value *jv_post_ptr = post_ptr->dump2JSON();
			  if (jv_post_ptr != NULL)
			    {
			      json_data[post_count] = *(jv_post_ptr);
			      post_count++;
			      delete jv_post_ptr;
			      delete post_ptr;
			    }
			}
		    }
		}
	      fgetc(okey_f);
	    }
	  fclose(okey_f);
	  result_json["data"]  = json_data;
	  result_json["court"] = post_count;
	}
      else
	{
	  // "id" related search
	  if ((myv_message["id"]).isString() == false)
	    {
	      ei_ptr = new Exception_Info {};
	      ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
	      ei_ptr->which_string = "search clause id not a string";
	      ei_ptr->how_code = EE1520_ERROR_NORMAL;
	      ei_ptr->what_code = EE1520_ERROR_JSON_KEY_TYPE_MISMATCHED;
	      (lv_exception_ptr->info_vector).push_back(ei_ptr);
	      throw (*lv_exception_ptr);
	    }

	  printf("searching id [%s]\n", ((myv_message["id"]).asString()).c_str());
	  
	  // extracting the "id" object
	  vector<std::string> matched = matchDirent("posts/.", "post",
						    (myv_message["id"]).asString());

	  int j;
	  for (j = 0; j < matched.size(); j++)
	    {
	      char pfn_buf[1024];
	      bzero(pfn_buf, 1024);
	      printf("[%d] = %s\n", j, (matched[j]).c_str());
	      fflush(stdout);
	      
	      snprintf(pfn_buf, strlen("./posts/") + strlen((matched[j]).c_str()) + 1,
		       "./posts/%s", (matched[j]).c_str());
	      std::cout << pfn_buf << std::endl;

	      Json::Value pjf_v;
	      rc = myFile2JSON(pfn_buf, &pjf_v);
	      if (rc != EE1520_ERROR_NORMAL)
		{
		  ei_ptr = new Exception_Info {};
		  ei_ptr->where_code = EE1520_ERROR_JSONRPC_SERVER;
		  ei_ptr->which_string = "search clause post myFile2JSON";
		  ei_ptr->how_code = EE1520_ERROR_NORMAL;
		  ei_ptr->what_code = rc;
		  (lv_exception_ptr->info_vector).push_back(ei_ptr);
		}
	      else
		{
		  Post *post_ptr = new Post((Person *) NULL, (Message *) NULL);
		  try
		    {
		      post_ptr->JSON2Object(&pjf_v);
		    }
		  catch(ee1520_Exception e)
		    {
		      JSON2Object_appendEI(e, lv_exception_ptr, 0);
		    }
		  // add to the result data
		  Json::Value *jv_post_ptr = post_ptr->dump2JSON();
		  if (jv_post_ptr != NULL)
		    {
		      json_data[post_count] = *(jv_post_ptr);
		      post_count++;
		      delete jv_post_ptr;
		      delete post_ptr;
		    }
		}
	    }

	  result_json["data"]  = json_data;
	  result_json["court"] = post_count;
	}
      
      if ((lv_exception_ptr->info_vector).size() != 0)
	{
	  throw (*lv_exception_ptr);
	}
    }
  catch (ee1520_Exception e)
    {
      int erc = produceErrorJSON(e, "ee1520server_search.log", &result_json, 0);
      if (erc != EE1520_ERROR_NORMAL)
	myPrintLog("{\"location\":\"produce Error catch\"}", "ee1520server_search.log");
      e.myDestructor();
    }

  return result_json;
}

// std::map
// two columns: first, second
// first  --> a string
// second --> an PTGR object
std::map<std::string, Personal_Timed_GPS_Record> hw3_PTGR_map;

Json::Value
Myee1520Server::upload
(const Json::Value& location_jv)
{
  Json::Value result;

  // the following part is just for logging of information for the server
  std::cout << "upload" << " " << location_jv << std::endl;

  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);

  char buffer[128];
  bzero(buffer, 128);
  std::strftime(buffer, 32, "%Y-%m-%dT%H:%M:%S", my_tm_ptr);
  printf("at %s\n", buffer);

  // above is for logginhg
  
  int i;
  Json::Value *jv_ptr = (Json::Value *) NULL;
  std::string id_str;
  Personal_Timed_GPS_Record * ptgr_ptr = NULL;
  Personal_Timed_GPS_Record ptgr_data {};
  
  if ((location_jv["identity"].isNull() != true) &&
      (location_jv["identity"].isString() == true) &&
      (location_jv["traces"].isNull() != true) &&
      (location_jv["traces"].isArray() == true))
    {
      id_str = location_jv["identity"].asString();

      // check whether the ID (id_str) exists in hw3_PTGR_map
      if (hw3_PTGR_map.find(id_str) != hw3_PTGR_map.end())
	{
	  // not equal (from the above line) ==> it exists
	  // if the key doesn't exist, it will create a new entry for that key
	  // ptgr_ptr = &(hw3_PTGR_map[id_str]);
	  // if the key doesn't exist, it won't create a new entry for that key
	  ptgr_ptr = &((hw3_PTGR_map.find(id_str))->second);
	}
      else
	{
	  ptgr_ptr = &ptgr_data;
	}

      try {
	Json::Value my_jv = location_jv; // original
	ptgr_ptr->JSON2Object(&my_jv);   // original
      } catch(ee1520_Exception e) {
	result["status"] = "ee1520_Exception caught";
	Json::Value exception_jv = *(e.dump2JSON());
	e.myDestructor();
	result["exceptions"] = exception_jv;
	return result;
      }
      
      TL_Sort(ptgr_ptr->traces);
      std::vector<Timed_Location> * unique_ptr = NULL;
      unique_ptr = TL_Unique(ptgr_ptr->traces);
      (hw3_PTGR_map[id_str]).traces = (*unique_ptr);
      delete unique_ptr;
  
      // dump the MAP
      for (const auto& n : hw3_PTGR_map)
	{
	  std::cout << '[' << n.first << ']' << std::endl;
	  Personal_Timed_GPS_Record x = n.second;
	  Json::Value *jvp = x.dump2JSON();
	  std::cout << (*jvp) << std::endl;
	  delete jvp;
	}

      result["status"] = "successful";
    }
  else
    {
      result["status"] = "failed";
    }
  return result;
}

Json::Value
Myee1520Server::question
(const Json::Value& question_jv)
{
  Json::Value result;
  
  std::cout << "question" << " " << question_jv << std::endl;
  std::string strJson;

  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);

  char buffer[128];
  bzero(buffer, 128);
  std::strftime(buffer, 32, "%Y-%m-%dT%H:%M:%S", my_tm_ptr);
  printf("at %s\n", buffer);

  int i;
  Json::Value *jv_ptr = (Json::Value *) NULL;

  std::string jvt_s;
  std::string id_str;

  if (((question_jv["time"]).isNull() != true)    &&
      ((question_jv["time"]).isObject() == true)  &&
      ((question_jv["identity"]).isNull() != true)    &&
      ((question_jv["identity"]).isString() == true)  &&
      ((question_jv["time"]["time"]).isNull() != true)    &&
      ((question_jv["time"]["time"]).isString() == true))
    {
      jvt_s = (question_jv["time"]["time"]).asString();
    }
  else
    {
      std::cout << "question JSON content error" << std::endl;
      result["status"] = "failed";
      return result;
    }

  JvTime jvt_question { jvt_s.c_str() };
  Personal_Timed_GPS_Record * ptgr_ptr = NULL;
  GPS_DD answer {0.0, 0.0};
  
  id_str = question_jv["identity"].asString();

  if (hw3_PTGR_map.find(id_str) != hw3_PTGR_map.end())
    {
      ptgr_ptr = &((hw3_PTGR_map.find(id_str))->second);
      answer = ptgr_ptr->question(jvt_question);
      // std::cout << answer.latitude << std::endl;
      // std::cout << answer.longitude << std::endl;      
      result["status"] = "successful";
      result["latitude"]  = answer.latitude;
      result["longitude"] = answer.longitude;
    }
  else
    {
      result["status"] = "failed";
    }

  return result;
}

Json::Value
Myee1520Server::dump2json
(const std::string& arg_identity)
{
  Json::Value result;

  std::cout << "dump2json" << " " << arg_identity << std::endl;

  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);

  char buffer[128];
  bzero(buffer, 128);
  std::strftime(buffer, 32, "%Y-%m-%dT%H:%M:%S", my_tm_ptr);
  printf("at %s\n", buffer);

  int i;
  Json::Value *jv_ptr = (Json::Value *) NULL;
  Personal_Timed_GPS_Record * ptgr_ptr = NULL;

  if (hw3_PTGR_map.find(arg_identity) != hw3_PTGR_map.end())
    {
      ptgr_ptr = &((hw3_PTGR_map.find(arg_identity))->second);
      jv_ptr = ptgr_ptr->dump2JSON();
      result = (*jv_ptr);
      delete jv_ptr;
    }
  else
    {
      result["status"] = "failed";
    }

  return result;
}

int
main(int argc, char *argv[])
{
  if (argc != 1) exit(-1);
  // HttpServer httpserver(8384);
  HttpServer httpserver(8300);
  // HttpServer httpserver(55408);
  Myee1520Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
