#include "Shoes.hpp"

Shoes::Shoes(const std::string& id, const std::string& name, const std::string& description, double basePrice, ProductQuality quality, const std::string& shoeType, const std::string& brand, double size)
    : Product(id, name, description, basePrice, quality, "defaultSellerID", "active"),
      shoeType(shoeType), brand(brand), size(size){}