
#include <iostream>
#include "Labeled_GPS.h"

using namespace std;

int
main
(void)
{
  Labeled_GPS lg1 {1.0, -1.0, "LG1" };

  std::cout << "original" << std::endl;
  std::cout << *(lg1.dump2JSON()) << std::endl;

  std::cout << "cast as a copy" << std::endl;
  std::cout << *(((GPS_DD)  lg1).dump2JSON()) << std::endl;

  std::cout << "cast as a reference (refer to the original copy)" << std::endl;
  std::cout << *(((GPS_DD&) lg1).dump2JSON()) << std::endl;

  GPS_DD g_copy = lg1; // option 1
  std::cout << "original" << std::endl;
  std::cout << *(g_copy.dump2JSON()) << std::endl;

  std::cout << "cast as a copy" << std::endl;
  std::cout << *(((Labeled_GPS&) g_copy).dump2JSON()) << std::endl;

  GPS_DD& g_reference = lg1; // option 2
  std::cout << "original" << std::endl;
  std::cout << *(g_reference.dump2JSON()) << std::endl;

  std::cout << "cast as a reference" << std::endl;
  std::cout << *(((Labeled_GPS&) g_reference).dump2JSON()) << std::endl;

  return 0;
}
