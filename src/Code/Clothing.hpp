#include "Product.hpp"
#include <iostream>

class Clothing : public Product
{
    private:
        std::string size;
        std::string color;
        std::string material;
        std::string brand;
    
    public:
        Clothing(const std::string& id, const std::string& name, const std::string& description, double basePrice, ProductQuality quality, const std::string& size, const std::string& color, const std::string& material, const std::string& brand);
        
        // getters
        std::string getSize() const { return size; }
        std::string getColor() const { return color; }
        std::string getMaterial() const { return material; }
        std::string getBrand() const { return brand; }
    
        // setters
        void setSize(const std::string& newSize) { size = newSize; }
        void setColor(const std::string& newColor) { color = newColor; }
        void setMaterial(const std::string& newMaterial) { material = newMaterial; }
        void setBrand(const std::string& newBrand) { brand = newBrand; }
    
        void printProduct() override
        {
            Product::printProduct();                        // testing override function
            std::cout << "Size: " << size << std::endl;
            std::cout << "Color: " << color << std::endl;
            std::cout << "Material: " << material << std::endl;
            std::cout << "Brand: " << brand << std::endl;
        }
};