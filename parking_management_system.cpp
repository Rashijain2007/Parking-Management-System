
//  PARKING MANAGEMENT SYSTEM


#include <iostream>
using namespace std;

const int TOTAL_SLOTS      = 100;     // number of parking slots
const int RATE_BIKE        = 20;    // Rs. per hour
const int RATE_CAR         = 40;    // Rs. per hour
const int RATE_BUS         = 50;    // Rs. per hour
const int RATE_RICKSHAW    = 30;    // Rs. per hour

// CLASS 1: Vehicle - stores the details of one vehicle

class Vehicle {
private:
    int vehicleNumber;      // digits only, example: 1234
    char ownerName[20];     // one word, example: Rahul
    int vehicleType;        // 1 = Two-wheeler, 2 = Car, 3 = Bus, 4 = Rickshaw
    int Hour;               // 0 - 23
    int Minute;             // 0 - 59
 
    // Takes all the vehicle details from the user
public:
    void input() {
        cout << "Enter vehicle number (digits only)  : ";
        cin >> vehicleNumber;
        cout << "Enter owner name (one word)         : ";
        cin >> ownerName;
        cout << "Vehicle type (1=Two-wheeler, 2=Car, 3=Bus, 4=Rickshaw  (1-4)) : ";
        cin >> vehicleType;
        cout << "Enter entry time (hour minute)      : ";
        cin >> Hour >> Minute;
    }

    // Returns 1 if the details are correct, otherwise 0
    int isCorrect() {
        if (vehicleType != 1 && vehicleType != 2 && vehicleType != 3 && vehicleType != 4) {
            cout << "Wrong vehicle type!\n";
            return 0;
        }
        if (Hour < 0 || Hour > 23 || Minute < 0 || Minute > 59) {
            cout << "Wrong time!\n";
            return 0;
        }
        return 1;
    }

    int VehicleNumber(){ 
        return vehicleNumber; 
    }
    const char* OwnerName(){ 
        return ownerName; 
    }
    int VehicleType(){ 
        return vehicleType; 
    }
    int EntryHour(){ 
        return Hour; 
    }
    int EntryMinute(){ 
        return Minute; 
    }
};

// CLASS 2: ParkingLot - manages all slots 

class ParkingLot {
private:
    Vehicle parkedVehicles[TOTAL_SLOTS];
    int slotUsed[TOTAL_SLOTS];        // 1 = used, 0 = free
    int ReceiptNumber;

public:
    ParkingLot() {
        ReceiptNumber = 1001;
        for (int i = 0; i < TOTAL_SLOTS; i++) {
            slotUsed[i] = 0;
        }
    }

    //  MODULE 1- Register vehicle entry  
    void registerEntry() {
        // Step 1: find a free slot
        int freeSlot = -1;
        for (int i = 0; i < TOTAL_SLOTS; i++) {
            if (slotUsed[i] == 0) {
                freeSlot = i;
                break;
            }
        }
        if (freeSlot == -1) {
            cout << "Parking is FULL!\n";
            return;
        }

        // Step 2: take vehicle details and check them
        Vehicle newVehicle;
        newVehicle.input();
        if (newVehicle.isCorrect() == 0) {
            return;
        }

        // Step 3: check that the vehicle is not already parked
        for (int i = 0; i < TOTAL_SLOTS; i++) {
            if (slotUsed[i] == 1 && parkedVehicles[i].VehicleNumber() == newVehicle.VehicleNumber()) {
                cout << "This vehicle is already parked!\n";
                return;
            }
        }

        // Step 4: park the vehicle
        parkedVehicles[freeSlot] = newVehicle;
        slotUsed[freeSlot] = 1;
        cout << "Vehicle registered in Slot " << freeSlot + 1 << endl;
    }

    // MODULE 2- Display available parking slots
    void displaySlots() {
        int availableCount = 0;

        cout << "\n--- Parking Slots ---\n";
        for (int i = 0; i < TOTAL_SLOTS; i++) {
            cout << "Slot " << i + 1 << " : ";
            if (slotUsed[i] == 1) {
                cout << "Occupied (Vehicle " << parkedVehicles[i].VehicleNumber() << ")\n";
            } 
            else {
                cout << "Available\n";
                availableCount++;
            }
        }
        cout << "Available slots : " << availableCount << " out of " << TOTAL_SLOTS << endl;
    }

    // MODULE 3- Record vehicle exit and duration
    void Exit() {
        int number, exitHour, exitMinute;

        cout << "Enter vehicle number : ";
        cin >> number;

        // Step 1: find the vehicle
        int slot = -1;
        for (int i = 0; i < TOTAL_SLOTS; i++) {
            if (slotUsed[i] == 1 && parkedVehicles[i].VehicleNumber() == number) {
                slot = i;
                break;
            }
        }
        if (slot == -1) {
            cout << "Vehicle not found!\n";
            return;
        }

        // Step 2: take exit time
        cout << "Enter exit time (hour minute) : ";
        cin >> exitHour >> exitMinute;
        if (exitHour < 0 || exitHour > 23 || exitMinute < 0 || exitMinute > 59) {
            cout << "Wrong time!\n";
            return;
        }

        // Step 3: find duration (convert both times to minutes)
        int entryInMinutes = parkedVehicles[slot].EntryHour() * 60 + parkedVehicles[slot].EntryMinute();
        int exitTimeInMinutes = (exitHour * 60) + exitMinute;
        int totalMinutes = exitTimeInMinutes - entryInMinutes;

        if (totalMinutes <= 0) {
            cout << "Exit time must be after entry time!\n";
            return;
        }
        cout << "Parking duration : " << totalMinutes / 60 << " hr " << totalMinutes % 60 << " min\n";

        // Step 4: calculate fee and print receipt (Module 4), then free the slot
        generateReceipt(slot, exitHour, exitMinute, totalMinutes);
        slotUsed[slot] = 0;
    }

    // MODULE 4- Calculate parking fees and generate receipts
    void generateReceipt(int slot, int exitHour, int exitMinute, int totalMinutes) {
        // Any part of an hour is charged as one full hour
        int chargedHours = totalMinutes / 60;
        if (totalMinutes % 60 != 0) {
            chargedHours++;
        }

        int rate;
        if (parkedVehicles[slot].VehicleType() == 1) {
            rate = RATE_BIKE;
        } 
        else if (parkedVehicles[slot].VehicleType() == 2) {
            rate = RATE_CAR;
        } 
        else if (parkedVehicles[slot].VehicleType() == 3) {
            rate = RATE_BUS;
        } 
        else {
            rate = RATE_RICKSHAW;
        }

        int totalFee = chargedHours * rate;

        cout << "\n===== PARKING RECEIPT =====\n";
        cout << "Receipt No: " << ReceiptNumber << endl;
        cout << "Vehicle No: " << parkedVehicles[slot].VehicleNumber() << endl;
        cout << "Owner Name: " << parkedVehicles[slot].OwnerName() << endl;
        if (parkedVehicles[slot].VehicleType() == 1){
            cout << "Vehicle Type: Two-wheeler\n";
        }
        else if (parkedVehicles[slot].VehicleType() == 2) {
            cout << "Vehicle Type: Car\n";
        }
        else if (parkedVehicles[slot].VehicleType() == 3) {
            cout << "Vehicle Type: Bus\n";
        }
        else {                                       
        cout << "Vehicle Type: Rickshaw\n";
        }
        cout << "Slot Number: " << slot + 1 << endl;
        cout << "Entry Time: " << parkedVehicles[slot].EntryHour() << " hr "<< parkedVehicles[slot].EntryMinute() << " min\n";
        cout << "Exit Time: " << exitHour << " hr " << exitMinute << " min\n";
        cout << "Duration: " << totalMinutes / 60 << " hr " << totalMinutes % 60 << " min\n";
        cout << "Charged Hours: " << chargedHours << endl;
        cout << "Rate per Hour: Rs. " << rate << endl;
        cout << "---------------------------\n";
        cout << "TOTAL FEE: Rs. " << totalFee << endl;
        cout << "===========================\n";

        ReceiptNumber++;
    }
};


int main() {
    ParkingLot myParking;
    int choice;

    cout << "===== PARKING MANAGEMENT SYSTEM =====\n";
    cout << "Rates: Two-wheeler Rs.20/hr, Car Rs.40/hr, Bus Rs.50/hr, Rickshaw Rs.30/hr\n";

    do {
        cout << "\n1. Register vehicle entry";
        cout << "\n2. Display available parking slots";
        cout << "\n3. Record vehicle exit and get receipt";
        cout << "\n4. Exit program";
        cout << "\nEnter choice : ";
        cin >> choice;
        if (cin.fail()) {
            cout << "\nWrong input! Program stopped.\n";
            break;
        }

        if (choice == 1){      
        myParking.registerEntry();
        } 
        else if (choice == 2) {
            myParking.displaySlots();
        } 
        else if (choice == 3) {
            myParking.Exit();
        }
        
    } 
    while (choice != 4);

    return 0;
}