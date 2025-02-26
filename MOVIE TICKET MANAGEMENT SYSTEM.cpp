#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

const int ROW = 5;
const int COL = 10;
const int DAYS = 7;
const int MOVIES = 3;

string days[DAYS] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
string movies[DAYS][MOVIES] = {
    {"Movie A1", "Movie A2", "Movie A3"},
    {"Movie B1", "Movie B2", "Movie B3"},
    {"Movie C1", "Movie C2", "Movie C3"},
    {"Movie D1", "Movie D2", "Movie D3"},
    {"Movie E1", "Movie E2", "Movie E3"},
    {"Movie F1", "Movie F2", "Movie F3"},
    {"Movie G1", "Movie G2", "Movie G3"}};

// Function to display the seating arrangement
void display(bool seats[ROW][COL])
{
    // Print column headers
    cout << "   "; // Initial space for row labels
    for (int i = 1; i <= COL; i++)
    {
           cout << setw(3)<<"  "<< i;  // Align column numbers
    }
    cout << endl;

    // Print each row of seats
    for (int i = 0; i < ROW; i++)
    {
    	        cout<< static_cast<char>('A' + i)<<"  "; // Row label

        for (int j = 0; j < COL; j++)
       // cout << setw(6) << i << " ";
        {
            if (seats[i][j])
            {
            	                cout << setw(3)<<"  " << "R"; // Show "R" for reserved seats

            }
            else
            {
                cout << setw(3)<<"  " << "-"; // Show "-" for available seats
            }
        }
        cout << endl;
    }
}

// Function to reserve a seat
void reservation(bool seats[ROW][COL], int col, char row)
{
    if (seats[row - 'A'][col - 1])
    {
        cout << "Seat is already reserved." << endl;
    }
    else
    {
        seats[row - 'A'][col - 1] = true; // Mark the seat as reserved
        cout << "Your seat is successfully booked." << endl;
    }
}

// Function to cancel a reservation
void cancelReservation(bool seats[ROW][COL], int col, char row)
{
    if (!seats[row - 'A'][col - 1])
    {
        cout << "Seat is not reserved." << endl;
    }
    else
    {
        seats[row - 'A'][col - 1] = false; // Mark the seat as available
        cout << "Your reservation has been canceled." << endl;
    }
}

// Check if any seat is available
bool hasFalseValueIn2D(bool seats[ROW][COL])
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (!seats[i][j])
            {
                return true;
            }
        }
    }
    return false;
}

// Count available seats
int countAvailableSeats(bool seats[ROW][COL])
{
    int count = 0;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (!seats[i][j])
            {
                count++;
            }
        }
    }
    return count;
}

int main(){

    cout<<"----WELCOME TO MOVIE SEAT RESERVATION SYSTEM----"<<endl;

    bool seats[DAYS][MOVIES][ROW][COL] = {}; // Seating chart for each movie on all 7 days

    int dayInput, movieInput;
    char rowInput;
    int colInput;

    while (true)
    {
        cout << "Select a day to book a seat:" << endl;
        for (int i = 0; i < DAYS; i++)
        {
            cout << i + 1 << ". " << days[i] << endl;
        }

        cout << "Enter your day in which you want to reserve seat (1-7): ";
        cin >> dayInput;

        if (dayInput < 1 || dayInput > 7)
        {
            cout << "Invalid day selection! Please choose a valid day (1-7)." << endl;
            continue;
        }

        int selectedDay = dayInput - 1;

        cout << "Movies available on " << days[selectedDay] << ":\n";
        for (int i = 0; i < MOVIES; i++)
        {
            cout << i + 1 << ". " << movies[selectedDay][i] << endl;
        }

        cout << "Enter your choice (1-3): ";
        cin >> movieInput;

        if (movieInput < 1 || movieInput > MOVIES)
        {
            cout << "Invalid movie selection! Please choose a valid movie (1-3)." << endl;
            continue;
        }

        int selectedMovie = movieInput - 1;
        int availableSeats = countAvailableSeats(seats[selectedDay][selectedMovie]);

        cout << availableSeats << " seats are available for " << movies[selectedDay][selectedMovie] << endl;

        if (!hasFalseValueIn2D(seats[selectedDay][selectedMovie]))
        {
            cout << "All seats are reserved for this movie." << endl;
            continue;
        }

        display(seats[selectedDay][selectedMovie]);

        cout << "Do you want to (1) Reserve a seat or (2) Cancel a reservation? ";
        int action;
        cin >> action;

        if (action == 1) // Reserve a seat
        {
            cout << "Enter Row (A-E): ";
            cin >> rowInput;

            cout << "Enter Column (1-10): ";
            cin >> colInput;

            if ((rowInput < 'A' || rowInput > 'E') || (colInput < 1 || colInput > 10))
            {
                cout << "You entered an invalid row or column!" << endl;
                continue;
            }

            reservation(seats[selectedDay][selectedMovie], colInput, rowInput);
        }
        else if (action == 2) // Cancel a reservation
        {
            cout << "Enter Row (A-E): ";
            cin >> rowInput;

            cout << "Enter Column (1-10): ";
            cin >> colInput;

            if ((rowInput < 'A' || rowInput > 'E') || (colInput < 1 || colInput > 10))
            {
                cout << "You entered an invalid row or column!" << endl;
                continue;
            }

            cancelReservation(seats[selectedDay][selectedMovie], colInput, rowInput);
        }
        else
        {
            cout << "Invalid action! Please choose 1 or 2." << endl;
            continue;
        }

        display(seats[selectedDay][selectedMovie]);

        char choice;
        cout << "Do you want to perform another action (Y/N)? ";
        cin >> choice;

        if (choice != 'Y' && choice != 'y')
        {
            break;
        }
    }

    cout << "Thank you for using the movie reservation system!" << endl;
    return 0;
}
