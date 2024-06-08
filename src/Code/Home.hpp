#include "Product.hpp"

class Home : public Product 
{
    private:
        int rooms;
        int floors;
        bool garage;

    public:
        Home(const std::string& id, const std::string& name, const std::string& description, double basePrice, ProductQuality quality, int rooms, int floors, bool garage);

        // getters
        int getRooms() const { return rooms; }
        int getFloors() const { return floors; }
        int getGarage() const { return garage; }
        
        // setters
        void setRooms(int newRooms) { rooms = newRooms; }
        void setFloors(int newFloors) { floors = newFloors; }
        void setGarage(int newGarage) { garage = newGarage; }

        void printProduct() override
        {
            Product::printProduct();
            std::cout << "Rooms: " << rooms << std::endl;
            std::cout << "Floors: " << floors << std::endl;
            std::cout << "Garage: " << (garage ? "Yes" : "No") << std::endl;
        }
};