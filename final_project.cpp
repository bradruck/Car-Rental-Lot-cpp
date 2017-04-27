//
// Created by Bradley Ruck on 12/1/16.
//
//Implementation File for final_project.cpp
//Header file is in final_project.h

#include <iostream>
#include "final_project.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "HidingNonVirtualFunction"

namespace csci2312 {
    // Vehicle_T Implementation

    // Default constructor
    Vehicle_T::Vehicle_T() { };

    // Constructor to sets make, model and VIN
    Vehicle_T::Vehicle_T(string veh_make, string veh_model, int veh_vehicleFeature, long veh_VIN) {
        //  VIN is a unique Vehicle identifier
        VIN = veh_VIN;
        vehicleFeature = veh_vehicleFeature;
        make = veh_make;
        model = veh_model;
    };

    // Destructor
    Vehicle_T::~Vehicle_T() {};

    void Vehicle_T::setMake(string veh_make) {
        make = veh_make;
    }

    string Vehicle_T::getMake() const {
        return make;
    }

    void Vehicle_T::setModel(string veh_model) {
        model = veh_model;
    }

    string Vehicle_T::getModel() const {
        return model;
    }

    void Vehicle_T::setVIN(long veh_VIN) {
        VIN = veh_VIN;
    }

    long Vehicle_T::getVIN() const {
        return VIN;
    }

    void Vehicle_T::setVehicleFeature(int veh_feature) {
        vehicleFeature = veh_feature;
    }

    int Vehicle_T::getVehicleFeature() const {
        return vehicleFeature;
    }

    void Vehicle_T::vehicleDescription() const {};

    // Overloads the >> operator for input values of type Vehicle_T.
    istream& operator >>(istream& ins, Vehicle_T& the_vehicle) {
        {
            ins >> the_vehicle.make >> the_vehicle.model >> the_vehicle.vehicleFeature >> the_vehicle.VIN;
            return ins;
        }
    };

    // Overloads the << operator for output values of type Vehicle_T.
    ostream& operator <<(ostream& outs, const Vehicle_T& the_vehicle) {
        the_vehicle.vehicleDescription();
        outs << endl;
        return outs;
    }

    // Needed for STL "sort" algorithm
    bool sortVehicleVin(VehiclePtr p1, VehiclePtr p2) {
        return(p1->getVIN() < p2->getVIN());
    }

    // Car_T Implementation

    // Default Constructor
    Car_T::Car_T() {};

    // Car_T constructor
    Car_T::Car_T(const string& veh_make, const string& veh_model, int veh_doors, const long& veh_VIN) : Vehicle_T(veh_make, veh_model, veh_doors, veh_VIN) {};

    // Redefine the base class function here
    void Car_T::setVehicleFeature(int veh_doors) {
        doors = veh_doors;
    }

    // Redefine the base class function here
    int Car_T::getVehicleFeature() const {
        return doors;
    }

    // Car_T output definition
    void Car_T::vehicleDescription() const {
        cout << setw(10) << "Car" << setw(20) << make << setw(20) << model << setw(15) << vehicleFeature << setw(38) << VIN;
    }

    // Truck_T implementation

    // Default Constructor
    Truck_T::Truck_T() {};

    // Truck_T Constructor
    Truck_T::Truck_T(const string& veh_make, const string& veh_model, int veh_wdrive, const long& veh_VIN) : Vehicle_T(veh_make, veh_model, veh_wdrive, veh_VIN) {};

    // Redefine the base class function here
    void Truck_T::setVehicleFeature(int veh_wdrive) {
        wdrive = veh_wdrive;
    }

    // Redefine the base class function here
    int Truck_T::getVehicleFeature() const {
        return wdrive;
    }

    // Truck_T output definition
    void Truck_T::vehicleDescription() const {
        cout << setw(10) << "Truck" << setw(20) << make << setw(20) << model << setw(30) << vehicleFeature << setw(23) << VIN;
    }

    // Inventory Implementation

    // Inventory exceptions
    Inventory_E::Inventory_E(string p_error_message) {
        errorMessage = p_error_message;
    };
    void Inventory_E::handleError() {
        cout << errorMessage << endl;
    };

    // Constructor to sets size of Inventory
    Inventory_T::Inventory_T(int veh_capacity) {
        vehicles.reserve(veh_capacity);
    };

    // Copy Constructor: creates new object as a copy
    Inventory_T::Inventory_T(const Inventory_T& p_inventory) {

        vehicles.reserve(p_inventory.getCapacity());

        for (unsigned i = 0; i < p_inventory.getSize(); i++) {

            Car_T* carPointer = NULL;
            Truck_T* truckPointer = NULL;

            // To find whether basePointer is pointing to Derived type of object
            // Runtime Type Identification (RTTI)
            carPointer = dynamic_cast<Car_T*>(p_inventory.vehicles[i]);
            truckPointer = dynamic_cast<Truck_T*>(p_inventory.vehicles[i]);

            if (carPointer != NULL)
            {
                vehicles.push_back(new Car_T(*carPointer));
            }
            else
            if (truckPointer != NULL)
            {
                vehicles.push_back(new Truck_T(*truckPointer));
            }
        }
    }

    // Destructor
    Inventory_T::~Inventory_T() {
        for(unsigned int i = 0; i < vehicles.size(); i++) {
            delete vehicles[i];
        }
    };

    size_t Inventory_T::getCapacity() const {
        return vehicles.capacity();
    }

    size_t Inventory_T::getSize() const {
        return vehicles.size();
    }

    // Adds Vehicle to Inventory
    void Inventory_T::addVehicle(VehiclePtr p_veh) throw (Inventory_E)  {

        if (vehicles.size() < vehicles.capacity())
            vehicles.push_back(p_veh);
        else
            throw(Inventory_E("The lot is full, no spaces available."));
    }

    // Sort Inventory.
    // Uses STL "sort", container's iterator, and a predicate function to compare elements
    void Inventory_T::sortVehicles() {
        sort(vehicles.begin(), vehicles.end(), sortVehicleVin);
    }

    // Searches inventory for specific vehicle, if found, rents it out
    void Inventory_T::findAndRentVehicle() {
        VehiclePtr whatVehicle = new Vehicle_T;
        cout << endl << "If you know the vehicle you wish to rent please - " << endl;
        cout << "Enter Vehicle's Make, Model and VIN: ";
        cin >> *whatVehicle;

        for (where = vehicles.begin(); where != vehicles.end(); where++) {
            // Check if equal using == operator on Vehicle_T
            if ((**where) == (*whatVehicle))
                break;
        }

        // If found, rent it out
        if (where != vehicles.end())
            vehicles.erase(where);
        else
            cout << endl << "There was a problem with your selection." << endl;
            cout << "Please refer to the Inventory List to see the vehicles that are currently available." << endl;
    }

    //Overloads the << operator for output values of type Inventory_T.
    ostream& operator <<(ostream& outs, const Inventory_T& the_vehicle) {
        if (the_vehicle.vehicles.size() == 0)
            outs << "The lot is empty" << endl;
        else {
            cout << "\n\nThis is a list of the available inventory to rent: \n\n";
            cout << setw(15) << "Vehicle Type" << setw(15) << "Make" << setw(20) << "Model" << setw(18) << "# of Doors";
            cout << setw(20) << "# of Wheel Drive"<< setw(11) << "VIN" << endl << endl;

            for (unsigned i = 0; i < the_vehicle.vehicles.size(); i++) {
                outs << *(the_vehicle.vehicles[i]);
            }
        }
        return outs;
    }
}

#pragma clang diagnostic pop