
#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include "Core.h"

// Transaction.h
#include "JvTime.h"
#include "Person.h"
#include "Relation.h"
#include "OKey.h"

#define TR_TYPE_FLIGHT 1

class OKey;
class Post;
class Relation;
class Transaction;

class Transaction : public Core
{
 private:
 protected:
 public:

  static unsigned int transaction_count;

  unsigned int type;
  unsigned int status;
  JvTime * when;
  JvTime * ajourn;
  Person * agent;
  Relation * group;
  GPS_DD * where;
  IP_Address * srcIP;
  std::vector<OKey               *> * keys;
  std::vector<Transaction        *> * related;

  Transaction(std::string, std::string, std::string, std::string);
  Transaction(unsigned int);
  Transaction(std::string, std::string, std::string, std::string,
	      unsigned int, Person *,
	      GPS_DD *, IP_Address *, JvTime *);
  virtual Json::Value * dumpJ();
};

class Airline
{
 private:
 protected:
 public:
};

class Flight: public Transaction
{
 private:
  static unsigned int fl_count;
 protected:
  Person * passenger;
  Airline * airline;
  std::string ticket_number;

 public:
  Flight(std::string, std::string, std::string, std::string, unsigned int, Person *, GPS_DD *,
	 IP_Address *, JvTime *, Person *, Airline *, std::string _ticket, GPS_DD *, GPS_DD *);
  Flight(std::string, std::string, std::string, std::string);
  GPS_DD * departure;
  GPS_DD * arrival;
  virtual double getDistance();
  bool Conflict_of_Interest();
};

#endif  /* _TRANSACTION_H_ */
