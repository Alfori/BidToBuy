#include "Product.hpp"

class PetSupplies : public Product
{
private:
    std::string petType;
    std::string brand;
    double weight;

public:
    PetSupplies(const std::string& id, const std::string& name, const std::string& description, double basePrice, ProductQuality quality, const std::string& petType, const std::string& brand, double weight);

    // getters
    std::string getPetType() const { return petType; }
    std::string getBrand() const { return brand; }
    double getWeight() const { return weight; }

    // setters
    void setPetType(const std::string& newPetType) { petType = newPetType; }
    void setBrand(const std::string& newBrand) { brand = newBrand; }
    void setWeight(double newWeight) { weight = newWeight; }

    void printProduct() override        // testing override functionality
    {
        Product::printProduct();
        std::cout << "Pet Type: " << petType << std::endl;
        std::cout << "Brand: " << brand << std::endl;
        std::cout << "Weight: " << weight << std::endl;
    }
};