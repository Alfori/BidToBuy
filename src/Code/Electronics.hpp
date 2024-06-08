#include "Product.hpp"

class Electronics : public Product
{
    private:
        int warrantyPeriod;
        std::string brand;
        std::string model;
        bool isRefurbished;

    public:
        Electronics(const std::string& id, const std::string& name, const std::string& description, double basePrice, ProductQuality quality, int warrantyPeriod, const std::string& brand, const std::string& model, bool isRefurbished);


        // getters
        int getWarrantyPeriod() const { return warrantyPeriod; }
        std::string getBrand() const { return brand; }
        std::string getModel() const { return model; }
        bool getIsRefurbished() const { return isRefurbished; }

        // setters
        void setWarrantyPeriod(int newWarrantyPeriod) { warrantyPeriod = newWarrantyPeriod; }
        void setBrand(const std::string& newBrand) { brand = newBrand; }
        void setModel(const std::string& newModel) { model = newModel; }
        void setIsRefurbished(bool newIsRefurbished) { isRefurbished = newIsRefurbished; }

        void printProduct() override
        {
            Product::printProduct();
            std::cout << "Warranty Period: " << warrantyPeriod << " months" << std::endl;
            std::cout << "Brand: " << brand << std::endl;
            std::cout << "Model: " << model << std::endl;
            std::cout << "Refurbished: " << (isRefurbished ? "Yes" : "No") << std::endl;
        }
};