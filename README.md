# Parking-Management-System

A console-based parking management system written in C++ using object-oriented
programming. It manages a parking lot with 100 slots and handles the full cycle of a
vehicle's visit: entry, slot display, exit and billing.

## Features

- Register vehicle entry and automatically assign the first free slot
- Display all parking slots, showing which are occupied and how many are available
- Record vehicle exit time and calculate how long the vehicle was parked
- Calculate the parking fee and print a receipt with a unique receipt number
- Input validation for vehicle type, time and duplicate vehicles

## Project Structure

The program is divided into four modules, and each module depends on the others:

| Module | Class | Responsibility | Depends on |
|--------|-------|----------------|------------|
| 1 | `EntryModule` | Registers vehicle entry and stores slot data | None (base module) |
| 2 | `DisplayModule` | Displays available and occupied slots | Module 1 |
| 3 | `ExitModule` | Records exit time and calculates duration | Module 1, Module 4 |
| 4 | `BillingModule` | Calculates the fee and generates receipts | Vehicle data from Module 1 |

A separate `Vehicle` class stores the details of a single vehicle (number, owner name,
type and entry time).

## Parking Rates

| Vehicle Type | Rate per Hour |
|--------------|---------------|
| Two-wheeler  | Rs. 20 |
| Car          | Rs. 40 |
| Bus          | Rs. 50 |
| Rickshaw     | Rs. 30 |

Any part of an hour is charged as a full hour. For example, 1 hour 10 minutes is charged
as 2 hours.

## How It Works

1. **Entry:** The user enters the vehicle number, owner name, vehicle type and entry time.
   The system checks the details, makes sure the vehicle is not already parked, and
   assigns a free slot.
2. **Display:** Shows every slot as Available or Occupied, with a count of free slots.
3. **Exit:** The user enters the vehicle number and exit time. The system finds the
   vehicle, calculates the parking duration, and sends the details to the billing module.
4. **Billing:** The fee is calculated from the vehicle type and charged hours, a receipt
   is printed, and the slot is freed.

## Sample Receipt

```
===== PARKING RECEIPT =====
Receipt No    : 1001
Vehicle No    : 1234
Owner Name    : Rahul
Vehicle Type  : Car
Slot Number   : 1
Entry Time    : 10 hr 0 min
Exit Time     : 12 hr 30 min
Duration      : 2 hr 30 min
Charged Hours : 3
Rate per Hour : Rs. 40
---------------------------
TOTAL FEE     : Rs. 120
===========================
```

## How to Run

1. Make sure a C++ compiler (such as g++) is installed.
2. Clone the repository:
   git clone https://github.com/<your-username>/<repo-name>.git
cd <repo-name>
3. Compile and run:
   g++ parking.cpp -o parking
./parking


On Windows, run `parking.exe` instead of `./parking`.

## Concepts Used

- Classes and objects
- Encapsulation (private data with public getters)
- Object dependencies using references between classes
- Arrays and loops
- Input validation
- Menu-driven programming

## Limitations

- Data is stored in memory only, so it is lost when the program closes
- Entry and exit must happen on the same day (exit time must be later than entry time)
- Owner name must be a single word

## Possible Improvements

- Save records to a file or database
- Support parking that continues past midnight
- Add vehicle-type-specific slot zones
- Add a daily revenue report



## Conclusion

The Parking Management System shows how object-oriented programming in C++ can be used
to solve a real-world problem. By dividing the program into four dependent modules
(entry, display, exit and billing), the code stays organized, easy to understand and easy
to extend.

The project automates the main tasks of a parking lot: assigning slots, tracking
available space, recording parking duration and calculating fees with a printed receipt.
It also applies important programming concepts such as encapsulation, reference-based
class dependency, input validation and modular design.

Although the current version stores data only while the program is running, it provides
a strong foundation. Future versions could add file or database storage, daily revenue
reports and support for parking that continues past midnight.
