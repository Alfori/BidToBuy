#include "Clothing.hpp"

Clothing::Clothing(const std::string& id, const std::string& name, const std::string& description, double basePrice, ProductQuality quality, const std::string& size, const std::string& color, const std::string& material, const std::string& brand)
    : Product(id, name, description, basePrice, quality, "defaultSellerID", "active"), size(size), color(color), material(material), brand(brand) {}
