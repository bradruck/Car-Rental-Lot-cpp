//
// Created by Bradley Ruck on 12/1/16.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"

#ifndef CSCI2312_FINAL_PROJECT_FINAL_PROJECT_H
#define CSCI2312_FINAL_PROJECT_FINAL_PROJECT_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

namespace csci2312 {
    using std::string;
    using std::ostream;
    using std::istream;
    using std::fstream;
    using std::cout;
    using std::endl;
    using std::cin;
    using std::get;
    using std::setw;
    using std::vector;
    using std::sort;

    // Base Class
    class Vehicle_T {
    public:
        // Default Constructor
        Vehicle_T();

        // Constructor sets Vehicle's make, model and VIN
        Vehicle_T(string, string, int, long);

        // Destructor
        ~Vehicle_T();

        // Accessors and Mutators
        void setMake(string);
        string getMake() const;

        void setModel(string);
        string getModel() const;

        void setVIN(long);
        long getVIN() const;

        void setVehicleFeature(int);
        int getVehicleFeature() const;

        // Vehicle identifier
        void virtual vehicleDescription() const;

        // Overloads the >> operator for input values of type Vehicle_T
        friend istream& operator >>(istream& ins, Vehicle_T& the_vehicle);

        // Overloads the << operator for output values of type Vehicle_T.
        friend ostream& operator <<(ostream& outs, const Vehicle_T& the_vehicle);

        friend bool operator ==(Vehicle_T p1, Vehicle_T p2) {
            return(p1.getVIN() == p2.getVIN());
        }

    protected:
        // Unique identifiers for the vehicles in the inventory
        long VIN;
        int vehicleFeature;
        string make, model;
    };

    // Use 'typedef' to define a new type for the pointer to the base element
    typedef Vehicle_T* VehiclePtr;

    // Function to support generic "sort"
    bool sortVehicleVin(VehiclePtr, VehiclePtr);

    // First sub-class
    class Car_T : public Vehicle_T {
    public:
        // Default
        Car_T();

        // Constructor sets Car's make, model, # of doors, and VIN
        Car_T(const string&, const string&, int, const long&);

        // Body type
        void setVehicleFeature(int);
        int getVehicleFeature() const;

        // Vehicle identifier
        void virtual vehicleDescription() const;

    protected:
        int doors;
    };

    // Second sub-class
    class Truck_T : public Vehicle_T {
    public:
        // Default
        Truck_T();

        // Constructor sets Truck's make, model, # wheel drive, and VIN
        Truck_T(const string&, const string&, int, const long&);

        // Wheel Drive type
        void virtual setVehicleFeature(int);
        int virtual getVehicleFeature() const;

        // Vehicle identifier
        void virtual vehicleDescription() const;

    protected:
        int wdrive;
    };

    // Inventory exceptions
    class Inventory_E {
    private:
        string errorMessage;
    public:
        //  Constructor set a message
        Inventory_E(string);
        void handleError();
    };

    // Inventory STL container
    class Inventory_T {
    public:

        // Default Constructor to sets Inventory's capacity
        Inventory_T(int = MAX_CAPACITY);

        // Copy Constructor
        Inventory_T(const Inventory_T&);

        // Destructor
        ~Inventory_T();

        size_t getCapacity() const;
        size_t getSize() const;

        // Adds a Vehicle to Inventory, passses the base pointer.  Polymorphism.
        void addVehicle(VehiclePtr) throw (Inventory_E);

        // Sort Vehicles
        void sortVehicles();

        // Find and Rent a Vehicle
        void findAndRentVehicle();

        // Template function to rent Vehicle, parametized on type of vehicle
        template<typename VehicleType_T>
        void rentVehicle(VehiclePtr whatVehicle) {
            VehicleType_T *vehiclePointer = NULL;

            for (where = vehicles.begin(); where != vehicles.end(); where++) {
                // Runtime Type Identification (RTTI)
                vehiclePointer = dynamic_cast<VehicleType_T *>(*where);
                // Check if equal using == operator on Vehicle_T
                if ((**where) == (*whatVehicle))
                    break;
            }
            // If found and is the right type of vehicle, rent it out
            if (where != vehicles.end() & vehiclePointer != NULL)
                vehicles.erase(where);
            else {
            cout << endl << "There was a problem with your request." << endl;
            cout << "Please check the type of vehicle you are attempting to rent, Car versus Truck" << endl;
            cout << "Try your selection again." << endl;
            }
        };

        // Overloads the << operator for output content of type Inventory_T.
        friend ostream& operator <<(ostream& outs, const Inventory_T& the_vehicle);

    private:
        int static MAX_CAPACITY;

        // A vector container is used to hold pointers to vehicles
        vector<VehiclePtr> vehicles;

        // A vector iterator in order to use STL functions
        vector<VehiclePtr>::iterator where;
    };

}
#endif //CSCI2312_FINAL_PROJECT_FINAL_PROJECT_H

#pragma clang diagnostic pop