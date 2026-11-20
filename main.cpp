
#include <iostream>
using namespace std;

class BusReservation {
    // Module 1: Bus Routes
    int busID[100];
    char source[100][30];
    char destination[100][30];
    char time[100][20];
    int totalBuses;

    // Module 2: Seat Availability
    int totalSeats[100];
    int bookedSeats[100];

    // Module 3: Ticket Booking
    int bookingID[100];
    int ticketBusID[100];
    char passengerName[100][30];
    int seatNumber[100];
    int ticketCount;

    int nextBookingID;

    // Module 4: Fare Calculation
    int distance[100];
    int fare[100];

public:

    BusReservation() {
        totalBuses = 0;
        ticketCount = 0;
        nextBookingID = 1001;
    }

    // Find bus using its ID
    int findBus(int id) {
        for (int i = 0; i < totalBuses; i++) {
            if (busID[i] == id) {
                return i;
            }
        }
        return -1;
    }

    // MODULE 1: ADD BUS ROUTE
    void addBus() {
        if (totalBuses == 100) {
            cout << "Bus storage is full!\n";
            return;
        }

        int id;

        cout << "Enter Bus ID: ";
        cin >> id;

        if (findBus(id) != -1) {
            cout << "Bus ID already exists!\n";
            return;
        }

        busID[totalBuses] = id;

        cout << "Enter Source: ";
        cin >> source[totalBuses];

        cout << "Enter Destination: ";
        cin >> destination[totalBuses];

        cout << "Enter Departure Time: ";
        cin >> time[totalBuses];

        cout << "Enter Total Seats: ";
        cin >> totalSeats[totalBuses];

        if (totalSeats[totalBuses] <= 0) {
            cout << "Invalid seat count!\n";
            return;
        }

        bookedSeats[totalBuses] = 0;

        totalBuses++;

        cout << "Bus Route Added Successfully!\n";
    }

    // UPDATE BUS ROUTE
    void updateBus() {
        int id;
        cout << "Enter Bus ID to update: ";
        cin >> id;

        int index = findBus(id);

        if (index == -1) {
            cout << "Bus not found!\n";
            return;
        }

        cout << "Enter New Source: ";
        cin >> source[index];

        cout << "Enter New Destination: ";
        cin >> destination[index];

        cout << "Enter New Departure Time: ";
        cin >> time[index];

        cout << "Route Updated Successfully!\n";
    }

    // DISPLAY ALL BUSES
    void displayBuses() {
        if (totalBuses == 0) {
            cout << "No buses available!\n";
            return;
        }

        cout << "\n----- BUS DETAILS -----\n";

        for (int i = 0; i < totalBuses; i++) {
            cout << "\nBus ID: " << busID[i];
            cout << "\nSource: " << source[i];
            cout << "\nDestination: " << destination[i];
            cout << "\nDeparture Time: " << time[i];
            cout << "\nTotal Seats: " << totalSeats[i];
            cout << "\nAvailable Seats: "
                 << totalSeats[i] - bookedSeats[i] << endl;
        }
    }

    // MODULE 2: CHECK SEAT AVAILABILITY
    void checkSeats() {
        int id;

        cout << "Enter Bus ID: ";
        cin >> id;

        int index = findBus(id);

        if (index == -1) {
            cout << "Bus not found!\n";
            return;
        }

        cout << "\nTotal Seats: " << totalSeats[index];
        cout << "\nBooked Seats: " << bookedSeats[index];
        cout << "\nAvailable Seats: "
             << totalSeats[index] - bookedSeats[index] << endl;
    }

    // MODULE 3: BOOK TICKET
    void bookTicket() {
        if (ticketCount == 100) {
            cout << "Ticket storage is full!\n";
            return;
        }

        int id, seat, index;

        cout << "Enter Bus ID: ";
        cin >> id;

        index = findBus(id);

        if (index == -1) {
            cout << "Bus not found!\n";
            return;
        }

        if (bookedSeats[index] == totalSeats[index]) {
            cout << "No seats available!\n";
            return;
        }

        cout << "Enter Passenger Name: ";
        cin >> passengerName[ticketCount];

        cout << "Enter Seat Number (1 to "
             << totalSeats[index] << "): ";
        cin >> seat;

        if (seat < 1 || seat > totalSeats[index]) {
            cout << "Invalid seat number!\n";
            return;
        }

        // Check whether seat is already booked
        for (int i = 0; i < ticketCount; i++) {
            if (ticketBusID[i] == id &&
                seatNumber[i] == seat) {
                cout << "This seat is already booked!\n";
                return;
            }
        }

        cout << "Enter Journey Distance (in km): ";
        cin >> distance[ticketCount];

        if (distance[ticketCount] <= 0) {
            cout << "Invalid distance!\n";
            return;
        }

        bookingID[ticketCount] = nextBookingID;
        ticketBusID[ticketCount] = id;
        seatNumber[ticketCount] = seat;

        // Fare calculation: Rs. 2 per km
        fare[ticketCount] = distance[ticketCount] * 2;

        bookedSeats[index]++;

        cout << "\nTicket Booked Successfully!";
        cout << "\nYour Booking ID is: "
             << bookingID[ticketCount] << endl;

        ticketCount++;
        nextBookingID++;
    }

    // CANCEL TICKET
    void cancelTicket() {
        int id, found = -1;

        cout << "Enter Booking ID to cancel: ";
        cin >> id;

        for (int i = 0; i < ticketCount; i++) {
            if (bookingID[i] == id) {
                found = i;
                break;
            }
        }

        if (found == -1) {
            cout << "Booking not found!\n";
            return;
        }

        int busIndex = findBus(ticketBusID[found]);

        if (busIndex != -1) {
            bookedSeats[busIndex]--;
        }

        // Shift ticket records to remove cancelled ticket
        for (int i = found; i < ticketCount - 1; i++) {
            bookingID[i] = bookingID[i + 1];
            ticketBusID[i] = ticketBusID[i + 1];
            seatNumber[i] = seatNumber[i + 1];
            distance[i] = distance[i + 1];
            fare[i] = fare[i + 1];

            for (int j = 0; j < 30; j++) {
                passengerName[i][j] =
                    passengerName[i + 1][j];
            }
        }

        ticketCount--;

        cout << "Ticket Cancelled Successfully!\n";
    }

    // DISPLAY ALL BOOKINGS
    void displayBookings() {
        if (ticketCount == 0) {
            cout << "No bookings available!\n";
            return;
        }

        cout << "\n----- BOOKING DETAILS -----\n";

        for (int i = 0; i < ticketCount; i++) {
            cout << "\nBooking ID: " << bookingID[i];
            cout << "\nPassenger: " << passengerName[i];
            cout << "\nBus ID: " << ticketBusID[i];
            cout << "\nSeat Number: " << seatNumber[i];
            cout << "\nDistance: " << distance[i] << " km";
            cout << "\nFare: Rs. " << fare[i] << endl;
        }
    }

    // MODULE 4: PRINT TICKET
    void printTicket() {
        int id, found = 0;

        cout << "Enter Booking ID: ";
        cin >> id;

        for (int i = 0; i < ticketCount; i++) {
            if (bookingID[i] == id) {
                int index = findBus(ticketBusID[i]);

                cout << "\n========== BUS TICKET ==========\n";

                cout << "Booking ID: " << bookingID[i] << endl;
                cout << "Passenger Name: "
                     << passengerName[i] << endl;

                cout << "Bus ID: " << ticketBusID[i] << endl;

                if (index != -1) {
                    cout << "Source: " << source[index] << endl;
                    cout << "Destination: "
                         << destination[index] << endl;
                    cout << "Departure Time: "
                         << time[index] << endl;
                }

                cout << "Seat Number: " << seatNumber[i] << endl;
                cout << "Distance: " << distance[i] << " km" << endl;
                cout << "Total Fare: Rs. " << fare[i] << endl;

                cout << "================================\n";

                found = 1;
                break;
            }
        }

        if (found == 0) {
            cout << "Ticket not found!\n";
        }
    }
};

// MAIN FUNCTION
int main() {
    BusReservation b;
    int choice;

    do {
        cout << "\n\n================================";
        cout << "\n       BUS RESERVATION SYSTEM";
        cout << "\n================================";

        cout << "\n1. Add Bus Route";
        cout << "\n2. Update Bus Route";
        cout << "\n3. Display Bus Routes";
        cout << "\n4. Check Seat Availability";
        cout << "\n5. Book Ticket";
        cout << "\n6. Cancel Ticket";
        cout << "\n7. Display All Bookings";
        cout << "\n8. Calculate Fare and Print Ticket";
        cout << "\n9. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                b.addBus();
                break;

            case 2:
                b.updateBus();
                break;

            case 3:
                b.displayBuses();
                break;

            case 4:
                b.checkSeats();
                break;

            case 5:
                b.bookTicket();
                break;

            case 6:
                b.cancelTicket();
                break;

            case 7:
                b.displayBookings();
                break;

            case 8:
                b.printTicket();
                break;

            case 9:
                cout << "\nThank You for Using Our System!";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.";
        }

    } while (choice != 9);

    return 0;
}
