
#include "Relation.h"

Relation::Relation
(std::string core_arg_host_url, std::string core_arg_owner_vsID,
 std::string core_arg_class_id, std::string core_arg_object_id)
{
}

bool
Relation::is_a_member_of
(Person& arg_target)
{
  return false;
}

bool
Relation::has_been_invited
(Person& arg_target)
{
  return false;
}

int
Relation::feed
(Post * arg_post_ptr)
{
  return 0;
}

bool
Relation::operator==
(Relation& arg_relation)
{
  return false;
}

std::string 
Relation::role
(Person& arg_target)
{
  return "none";
}

