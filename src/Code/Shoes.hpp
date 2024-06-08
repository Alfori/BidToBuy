#include "Product.hpp"

class Shoes : public Product
{
private:
    std::string shoeType;
    std::string brand;
    double size;

public:
    Shoes(const std::string& id, const std::string& name, const std::string& description, double basePrice, ProductQuality quality, const std::string& shoeType, const std::string& brand, double size);

    // getters
    std::string getShoeType() const { return shoeType; }
    std::string getBrand() const { return brand; }
    double getSize() const { return size; }

    // setters
    void setShoeType(const std::string& newShoeType) { shoeType = newShoeType; }
    void setBrand(const std::string& newBrand) { brand = newBrand; }
    void setSize(double newSize) { size = newSize; }

    void printProduct() override
    {
        Product::printProduct();
        std::cout << "Shoe Type: " << shoeType << std::endl;
        std::cout << "Brand: " << brand << std::endl;
        std::cout << "Size: " << size << std::endl;
    }
};