#include <iostream>
#include <iomanip>
using namespace std;

int columns = 5, rows = 22, total_seats = columns * rows;
int class_no = 3;
int *classes_rows = new int[class_no + 1]{ 0,4,8,10 };
double *classes_price = new double[class_no + 1]{ 0,50,15,10 };
bool *cinemaSeats = new bool[total_seats];
int *seatsAvailable = new int[class_no + 1]{ 0,4 * columns,8 * columns,10 * columns };

// Clears all seats in the cinema
void clearSeats()
{
	for (int i = 0; i <= total_seats; i++)
		cinemaSeats[i] = false;
}

// Shows all seats of the cinema indicating whether each seat is reserved or not
void showAllSeats()
{
	cout << "   -------------THEATER-------------\n----------------------------------------" << endl << endl;
	for (int i = 1; i <= total_seats; i++)
	{
		if (cinemaSeats[i])
			cout << setw(5) << i << ",X" << "\t";
		else
			cout << setw(5) << i << ",O" << "\t";
		if (!(i % columns)) cout << endl;
	}
	cout << "----------------------------------------\n    -------------BACK-------------" << endl;
}

// Returns the number of the last seat in a class, used in showClassSeats in
// order to know where a class starts and where it ends
int classSeats(int classX)
{
	int sum = 0;
	for (int i = classX; i >= 0; i--)
		sum += classes_rows[i];
	return sum * columns;
}

// Shows the seats of a given class and whether each seats is reserved or not
void showClassSeats(int classX)
{
	int from = classSeats(classX - 1) + 1;
	int to = classSeats(classX);
	cout << "   -------------THEATER-------------\n----------------------------------------" << endl << endl;
	for (int i = from; i <= to; i++)
	{
		if (cinemaSeats[i])
			cout << setw(5) << i << ",X" << "\t";
		else
			cout << setw(5) << i << ",O" << "\t";
		if (!(i % columns)) cout << endl;
	}
	cout << "----------------------------------------\n    -------------BACK-------------" << endl;

}

// Reserves a seat, returns true if it is successful
// returns false if the seat is already reserved or not in this class
bool reserveSeat(int seat_no, int classX)
{
	if (!cinemaSeats[seat_no] && seat_no > classSeats(classX - 1) && seat_no <= classSeats(classX))
	{
		cinemaSeats[seat_no] = true;
		seatsAvailable[classX]--;
		return true;
	}
	return false;
}

// Cancels reservation of a seat, returns true if it is successful
// returns false if the seat is not reserved or not in this class
bool cancelSeat(int seat_no, int classX)
{
	if (cinemaSeats[seat_no] && seat_no > classSeats(classX - 1) && seat_no <= classSeats(classX))
	{
		cinemaSeats[seat_no] = false;
		seatsAvailable[classX]++;
		return true;
	}
	return false;
}

// Shows the credits
void showAbout() {
	cout << endl;
	cout << "||------------------------------------||" << endl;
	cout << "||-----------CINEMA PROJECT-----------||" << endl;
	cout << "||------------------------------------||" << endl;
	cout << "||--------    KHALED HAMED    --------||" << endl;
	cout << "||--------  SHERIF ABDEL NABY --------||" << endl;
	cout << "||--------   MUHAMMED MAGDY   --------||" << endl;
	cout << "||--------    NADA MOHAMED    --------||" << endl;
	cout << "||--------   MOHAMED EZZAT    --------||" << endl;
	cout << "||------------------------------------||" << endl << endl;
	cout << "Press any key to return to main menu" << endl;
}
