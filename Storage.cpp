
#include "Storage.h"

Storage::Storage
(void)
{
}

Json::Value * Storage::dump2JSON
(void)
{
  return NULL;
}

std::vector<Person *> *
Storage::whoAccessed
(void)
{
  std::vector<Person *> * result_ptr = NULL;

  if ((this->history != NULL) &&
      ((this->history)->size() > 0))
    {
      result_ptr = new std::vector<Person *>();
      int result_size = 0;

      int i;
      for (i = 0; i < (this->history)->size(); i++)
	{
	  Person * h_current = ((*(this->history))[i])->agent;
	  bool flag_pr = false;
	  vector<Person *>::iterator my_it_pr;
	  for (my_it_pr = (*(result_ptr)).begin();
	       my_it_pr < (*(result_ptr)).end();
	       my_it_pr++)
	    {
	      if ((*(*my_it_pr)) == (*h_current))
		{
		  flag_pr = true;
		}
	    }

	  if (flag_pr == false)
	    {
	      result_ptr->push_back(h_current);
	    }
	}
    }
  return result_ptr;
}
