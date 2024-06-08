#include "Product.hpp"
#include "Clothing.hpp"
#include "Electronics.hpp"

#include "Home.hpp"
#include "petSupplies.hpp"
#include "Shoes.hpp"

Product* productFactory(productClass pc) 
{
    switch (pc) 
    {
        case productClass::Electronics:
            return new Electronics("E001", "Some Electronic", "Some electronics desc", 49.99, ProductQuality::New, 24, "TechBrand", "SmartModel X", false);

        case productClass::Clothing:
            return new Clothing("C001", "T-Shirt", "Comfortable cotton t-shirt", 39.99, ProductQuality::New, "L", "Black", "Cotton", "FashionBrand");

        case productClass::Home:
            return new Home("H001", "Modern House", "Spacious house with a beautiful garden", 300000.0, ProductQuality::New, 5, 2, true);

        case productClass::Shoes:
            return new Shoes("S001", "Running Shoes", "Lightweight and comfortable running shoes", 89.99, ProductQuality::New, "Running", "SportBrand", 9);

        case productClass::petSupplies:
            return new PetSupplies("P001", "Dog Food", "Nutritious food for your dog", 9.99, ProductQuality::New, "Dog", "PetBrand", 5.0);

        default:
            return new Product("D001", "Generic Product", "This is a generic product", 50.0, ProductQuality::New, "defaultSellerID", "Open", 0.0f);
    }
}