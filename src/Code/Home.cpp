#include "Home.hpp"

Home::Home(const std::string& id, const std::string& name, const std::string& description, double basePrice, ProductQuality quality, int rooms, int floors, bool garage)
    : Product(id, name, description, basePrice, quality, "defaultSellerID", "active"),
      rooms(rooms), floors(floors), garage(garage){}
