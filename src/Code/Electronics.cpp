#include "Electronics.hpp"

Electronics::Electronics(const std::string& Id, const std::string& name, const std::string& description, double basePrice, ProductQuality quality, int warrantyPeriod, const std::string& brand, const std::string& model, bool isRefurbished)
    : Product(Id, name, description, basePrice, quality, "defaultSellerID", "active"), warrantyPeriod(warrantyPeriod), brand(brand), model(model), isRefurbished(isRefurbished) {}
