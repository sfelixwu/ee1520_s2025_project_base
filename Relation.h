
#ifndef _RELATION_H_
#define _RELATION_H_

#include "Core.h"
#include "Person.h"
#include "Post.h"
#include "Transaction.h"

class OKey;
class Post;
class Relation;
class Transaction;

class Relation : public Core
{
 private:
 protected:
 public:
  std::string id;
  std::string description;
  std::map<std::string, Person *> * members;
  std::vector<Transaction      *> * history;

  Relation(std::string, std::string, std::string, std::string);
  bool is_a_member_of(Person&);
  bool has_been_invited(Person&);
  int feed(Post *);
  virtual bool operator==(Relation&);
  std::string role(Person&);
};

#endif  /* _HYPER_FRIENDS_H_ */
