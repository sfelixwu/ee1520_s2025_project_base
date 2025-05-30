
#include "Reaction.h"

Reaction::Reaction
(void)
{
  this->class_name = "Reaction";

  this->type = "default";
  this->author = (Person *) NULL;
  this->created = (JvTime *) NULL;
}

Reaction::~Reaction
(void)
{
  // return;
  
  if (this->author != NULL) delete this->author;
  if (this->created != NULL) delete this->created;
}

Reaction::Reaction
(std::string arg_type, Person * arg_author, JvTime * arg_created)
{
  this->type = arg_type;
  this->author = arg_author;
  this->created = arg_created;
}

bool
Reaction::operator==
(Reaction& aReaction)
{
  bool brc = true;

  // printf("Reaction OL 1\n");
  if (((this->author) != NULL) && ((aReaction.author) != NULL))
    {
      brc = ((*(this->author)) == (*(aReaction.author)));
    }

  // printf("Reaction OL 2\n");
  if (((this->created) != NULL) && ((aReaction.created) != NULL))
    {
      brc = (brc && ((*(this->created)) == (*(aReaction.created))));
    }
  // printf("Reaction OL 3\n");

  return (brc && (this->type   == aReaction.type));
}

Json::Value *
Reaction::dump2JSON
(void)
{
  Json::Value * result_ptr = new Json::Value();
  Json::Value * jv_ptr = NULL;
  
  if (this->author != NULL)
    {
      jv_ptr = (this->author)->dump2JSON();
      if (jv_ptr != NULL)
	{
	  (*result_ptr)["from"] = (*jv_ptr);
	  delete jv_ptr;
	}
    }

  (*result_ptr)["type"] = this->type;

  if (this->created != NULL)
    {
      jv_ptr = (this->created)->dump2JSON();
      if (jv_ptr != NULL)
	{
	  (*result_ptr)["created"] = (*jv_ptr);
	  delete jv_ptr;
	}
    }

  return result_ptr;
}

void
Reaction::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  
  ee1520_Exception lv_exception {};
  ee1520_Exception * lv_exception_ptr = &lv_exception;

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       EE1520_ERROR_JSON2OBJECT_REACTION);

  if (((*arg_json_ptr)["type"].isNull() == true) ||
      ((*arg_json_ptr)["type"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = EE1520_ERROR_JSON2OBJECT_REACTION;
      ei_ptr->which_string = "type";
      ei_ptr->how_code = EE1520_ERROR_NORMAL;

      if ((*arg_json_ptr)["type"].isNull() == true)
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}

      ei_ptr->array_index = 0;
      
      (lv_exception_ptr->info_vector).push_back(ei_ptr);
    }
  else
    {
      // [1] ((*arg_json_ptr)["type"])
      // [2] .asString();
      this->type = ((*arg_json_ptr)["type"]).asString();
    }

  if (((*arg_json_ptr)["created"].isNull() == true) ||
      ((*arg_json_ptr)["created"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = EE1520_ERROR_JSON2OBJECT_REACTION;
      ei_ptr->which_string = "created";
      ei_ptr->how_code = EE1520_ERROR_NORMAL;

      if ((*arg_json_ptr)["created"].isNull() == true)
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}

      ei_ptr->array_index = 0;
      
      (lv_exception_ptr->info_vector).push_back(ei_ptr);
    }
  else
    {
      try
	{
	  if (this->created == NULL)
	    {
	      this->created = new JvTime();
	    }
	  (this->created)->JSON2Object(&((*arg_json_ptr)["created"]));
	}
      catch(ee1520_Exception& e)
	{
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
	}
    }

  if (((*arg_json_ptr)["from"].isNull() == true) ||
      ((*arg_json_ptr)["from"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = EE1520_ERROR_JSON2OBJECT_REACTION;
      ei_ptr->which_string = "from";
      ei_ptr->how_code = EE1520_ERROR_NORMAL;

      if ((*arg_json_ptr)["from"].isNull() == true)
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = EE1520_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}

      ei_ptr->array_index = 0;
      
      (lv_exception_ptr->info_vector).push_back(ei_ptr);
    }
  else
    {
      try
	{
	  if (this->author == NULL)
	    {
	      this->author = new Person();
	    }
	  (this->author)->JSON2Object(&((*arg_json_ptr)["from"]));
	}
      catch(ee1520_Exception& e)
	{
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
	}
    }
  
  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}
