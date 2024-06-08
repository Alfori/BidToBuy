#include "petSupplies.hpp"

PetSupplies::PetSupplies(const std::string& id, const std::string& name, const std::string& description, double basePrice, ProductQuality quality, const std::string& petType, const std::string& brand, double weight)
    : Product(id, name, description, basePrice, quality, "defaultSellerID", "active"), petType(petType), brand(brand), weight(weight){}
