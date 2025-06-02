
// ysd_grocery.cpp
// #define _ECS36B_DEBUG_

#include "Coupon.h"
#include "Grocery.h"
#include "Item.h"
#include "Fridge.h"
#include "Post.h"
#include "JvTime.h"

int
main(int argc, char *argv[])
{
  if (argc != 1) return -1;

  // create several people, two families
  // Dad
  Person p1;
  p1.vsID = "234567890";
  p1.owner_vsID = "234567890";
  p1.avatar_name = "Oracle";

  // Mom
  Person p2;
  p2.vsID = "234567891";
  p2.owner_vsID = "234567891";
  p2.avatar_name = "Trinity";

  // child
  Person p3;
  p3.vsID = "234567892";
  p3.owner_vsID = "234567892";
  p3.avatar_name = "Agent Smith";

  GPS_DD gps_Davis {38.5, -121.7};
  GPS_DD gps_NYC {40.7, -73.95};
  GPS_DD gps_Sydney {-33.87, 151.213};

  IP_Address * ip_ptr = new IP_Address(inet_addr("169.237.6.102"));

  // create my_fridge at home
  Fridge my_fridge;
  my_fridge.location = &gps_Davis;
  my_fridge.history = new std::vector<Transaction *>();

  // create some history before shopping
  Transaction *tr_ptr;

  tr_ptr = new Transaction(0);
  tr_ptr->where = my_fridge.location;
  tr_ptr->when  = getNowJvTime();
  tr_ptr->srcIP = ip_ptr;
  tr_ptr->agent = &p1;
  (my_fridge.history)->push_back(tr_ptr);

  tr_ptr = new Transaction(0);
  tr_ptr->where = my_fridge.location;
  tr_ptr->when  = getNowJvTime();
  tr_ptr->srcIP = ip_ptr;
  tr_ptr->agent = &p2;
  (my_fridge.history)->push_back(tr_ptr);

  tr_ptr = new Transaction(0);
  tr_ptr->where = my_fridge.location;
  tr_ptr->when  = getNowJvTime();
  tr_ptr->srcIP = ip_ptr;
  tr_ptr->agent = &p3;
  (my_fridge.history)->push_back(tr_ptr);

  // who have accessed my_fridge
  std::vector<Person *> * person_vector_ptr = my_fridge.whoAccessed();
  int i;
  for (i = 0; i < person_vector_ptr->size(); i++)
    {
      Person * h_current = (*person_vector_ptr)[i];
      std::cout << (h_current->dumpJ())->toStyledString() << std::endl;
      // obtain necessary credentials (before shopping)
    }

  // create a Grocery store
  Grocery nugget;
  nugget.owner_vsID = "123456789";
  nugget.store = "Nugget Market";

  // create a fridge at Nugget Market
  Fridge nugget_fridge;
  nugget_fridge.place = &nugget;

  // specify products, create items, beer and diaper
  Product pr1 {"391", "00636412012067", "636412012067", "American Craft",
      "Appalachian Brewing Co. American Craft Root Beer - 6 Pk"};
  pr1.keyword = "alcohol";

  Product pr2 {"803", "00036000306149", "036000306149", "Huggies",
      "Huggies Overnite Diapers Step 4 Big Pack 60"};
  pr2.keyword = "baby";

  Item beer;
  beer.product = (&pr1);
  beer.ratio = 1.0;
  beer.current = &nugget_fridge;
  // show my intention (or walking) in purchasing this item
  beer.next = &my_fridge;

  // checking whether we need credential
  if ((beer.product)->keyword == "alcohol")
    {
      // check the credentials
      // authorize (person, fridge, keyword, product)
    }

  // sending the coupons
  JvTime *jt = getNowJvTime();
  jt->day += 7;
  Coupon c1 { "coupon", "beer 25\% off", (Core *) (&nugget), (Core *) (&p1),
      &pr1, jt, 0.75 };
  Coupon c2 { "coupon", "diaper 33\% off", (Core *) (&nugget), (Core *) (&p1),
      &pr2, jt, 0.67 };
  p1.message(*(c1.dumpJ()));
  p1.message(*(c2.dumpJ()));

  return 0;
}
