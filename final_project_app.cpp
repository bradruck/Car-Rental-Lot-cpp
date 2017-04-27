//
// Created by Bradley Ruck on 12/1/16.
//
// ********************************************************************************************
//  This program models a car rental lot to demonstrate polymorphism
//  It holds a vector of pointers to a generic vehicle, specific vehicles are added or removed
//  STL vector container is used, and also a vector's iterator
//  Template method is used to release specific types of vehicles
//  Generic algorithm "sort" is used.
// ********************************************************************************************

#include <iostream>
#include "final_project.h"

using namespace csci2312;

void displayMainMenu();
void loadVehicleInventory(Inventory_T& inventory, VehiclePtr newVehicle);

int main() {
    // Instantiate the container with given capacity
    Inventory_T inventory(50);

    // Generic pointer used to add vehicles that have been returned
    VehiclePtr returnedVehicle = nullptr;

    // Generic pointer used to remove vehicles that have been rented
    VehiclePtr rentedVehicle = nullptr;

    // Load initial rental inventory from file
    loadVehicleInventory(inventory, returnedVehicle);

    int choice = -1;

    do {
        displayMainMenu();
            // Check for non-integer selection.
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore();
            cout << "\nThat was not a valid choice!\n";
        }
            // Check for integer choice out-of-range.
        else if (choice < 0 || choice > 7) {
            cin.clear();
            cin.ignore();
            cout << "\nThat was not a valid choice!\n";
        }
        switch (choice) {
            case 1:
                // Return a Car
                returnedVehicle = new Car_T;
                cout << "Enter Car's Make, Model, # of Doors and VIN to be returned: ";
                cin >> *returnedVehicle;
                try {
                    inventory.addVehicle(returnedVehicle);
                }
                catch (Inventory_E e) {
                    e.handleError();
                }
                break;
            case 2:
                // Return a Truck
                returnedVehicle = new Truck_T;
                cout << "Enter Truck's Make, Model, # of WheelDrive and VIN to be returned: ";
                cin >> *returnedVehicle;
                try {
                    inventory.addVehicle(returnedVehicle);
                }
                catch (Inventory_E e) {
                    e.handleError();
                }
                break;
            case 3:
                // Prints all the vehicles in inventory available to rent
                cout << inventory;
                break;
            case 4:
                //  Rent a Car
                rentedVehicle = new Car_T;
                cout << inventory;
                cout << endl << "Please enter the Car's Make, Model, # of Doors and VIN that you would like to rent: ";
                cin >> *rentedVehicle;

                //  Template method
                inventory.rentVehicle<Car_T>(rentedVehicle);
                break;
            case 5:
                //  Rent a Truck
                rentedVehicle = new Truck_T;
                cout << inventory;
                cout << endl << "Please enter the Truck's Make, Model, # of WheelDrive and VIN that you would like to rent: ";
                cin >> *rentedVehicle;

                // Template method
                inventory.rentVehicle<Truck_T>(rentedVehicle);
                break;
            case 6:
                // Sort the inventory
                inventory.sortVehicles();
                break;
            case 7:
                //  Searches for a specific vehicle, if available, rents the vehicle
                inventory.findAndRentVehicle();
                break;
            default:
                break;
        }
    } while (choice != 0);

    return 0;
}

// Display the main menu
void displayMainMenu() {
    cout << endl;
    cout << "        MAIN MENU\n";
    cout << "0) Quit\n";
    cout << "1) Return a Car\n";
    cout << "2) Return a Truck\n";
    cout << "3) Print Vehicles Available to Rent\n";
    cout << "4) Rent a Car\n";
    cout << "5) Rent a Truck\n";
    cout << "6) Sort Vehicles by VIN\n";
    cout << "7) Find and Rent a specific Vehicle\n";
    cout << "\nPlease Enter your choice: ";
}

// Read in the initial rental inventory from a text file
void loadVehicleInventory(Inventory_T& inventory, VehiclePtr newVehicle) {
    fstream infile;
    char type;
    infile.open("rental_inventory.txt");

    // Check for validity of file
    if (!infile)
    {
        cout << "\nError opening file. \n";
        cout << "It may not exist where indicated. \n";
    }

    infile.get(type); // Get type indicator, 1 for car and 2 for truck
    infile.ignore();
    while (infile) {
        if (type == '1') {
            newVehicle = new Car_T;
            infile >> *newVehicle;
            infile.ignore();
            try {
                inventory.addVehicle(newVehicle);
            }
            catch (Inventory_E e) {
                e.handleError();
            }
        } else {
            newVehicle = new Truck_T;
            infile >> *newVehicle;
            try {
                inventory.addVehicle(newVehicle);
            }
            catch (Inventory_E e) {
                e.handleError();
            }
            infile.ignore();
        }
        infile.get(type);
        infile.ignore();
    }
    infile.close();
}
