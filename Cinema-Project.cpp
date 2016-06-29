
/*
Project: Cinema
Team members:
	Sherif Mohamed Abdel-Naby 20150309
	Khaled Ahmed Hamed 20150101
	Mohamed Ezzat 20150216
	Mohamed Magdy 20150221
	Nada Gamal Mohamed 20150277
*/

#include <iostream>
#include <iomanip>
#include "cinema.h"
using namespace std;

int main() {
	clearSeats();
	while (true)
	{
		int choice;
		cout << "\nPlease select an Option:\n1: Ticket reservation\n2: Ticket Cancellation\n3: Reset all reservations\n4: Show cinema map\n5: Exit\n\n\n";
		cout << "8: About\n9 : Settings\n";
		cin >> choice;
		int classX, seatX, tkt_number, cancelled = 0;
		bool escape = false;
		system("cls");
		switch (choice)
		{
		case 1: // Ticket reservation
			cout << "Which class do you want ?" << endl;
			cin >> classX;
			system("cls");
			showClassSeats(classX);
			cout << "Seats Available: " << seatsAvailable[classX] << endl;
			cout << "Price per seat: $" << classes_price[classX] << endl;
			cout << "How many tickets you would like to reserve?" << endl;
			cin >> tkt_number;
			system("cls");
			if (tkt_number <= seatsAvailable[classX])
			{
				for (int i = 0; i < tkt_number; i++)
				{
					cout << "Which seat you would like to reserve ?" << "  (" << i + 1 << "/" << tkt_number << ")" << endl;
					cin >> seatX;
					while (!reserveSeat(seatX, classX))
					{
						cout << "Sorry the seat is already reserved Or is out of the selected class.\nPlease enter another valid seat ID..." << endl;
						cin >> seatX;
					}
					cout << "Successful! Seat: " << seatX << " is now reserved, Thank you." << endl;
				}
				cout << fixed << setprecision(2) << "Total money: $" << classes_price[classX] * tkt_number << endl;
			}
			else
				cout << "Sorry, that class doesn't have enough seats.\nReturning to main menu..." << endl;
			break;
		case 2: // Ticket Cancellation
			cancelled = 0;
			escape = false;
			cout << "In which class do you want to cancel the reservation?" << endl;
			cin >> classX;
			showClassSeats(classX);
			cout << "How many reservations you'd like to cancel?" << endl;
			cin >> tkt_number;
			system("cls");
			for (int i = 0; i < tkt_number; i++)
			{
				cout << "Which seat you would like to cancel its reservation?" << "  (" << i + 1 << "/" << tkt_number << ")" << endl;
				cin >> seatX;
				while (!cancelSeat(seatX, classX))
				{
					cout << "Sorry the seat is not reserved Or is out of the selected class.\nPlease enter another valid seat ID... (Enter -1 to go back to menu)" << endl;
					cin >> seatX;
					if (seatX == -1) { escape = true; break; }
				}
				if (escape) break;
				cout << "Successful! Seat: " << seatX << " reservation is now cancelled, Thank you." << endl;
				cancelled++;
			}
			cout << fixed << setprecision(2) << "Total money returned: $" << classes_price[classX] * cancelled << endl;
			break;
		case 3: // Reset all reservations (cancel them all)
			cout << "RESETING...\nTheater reservation has been reset\nReturning to main menu..." << endl;
			clearSeats();
			break;
		case 4: // Show cinema map
			showAllSeats();
			break;
		case 5: // Exit
			return 0;
		case 8: // About
			showAbout();
			break;
		case 9: // Settings
			while (true)
			{
				system("cls");
				cout << "(Current settings: Rows: " << rows << " Columns=" << columns << " Total seats:" << total_seats << ")" << endl;;
				int setting;
				cout << "1: Change the dimensions of the theater.\n2: Change classes division & prices\n3: go back to menu" << endl;
				cin >> setting;
				system("cls");
				if (setting == 1)
				{
					cout << "Please enter the number of seats rows in the theater." << endl;
					cin >> rows;
					cout << "Please enter the number of seats columns in the theater." << endl;
					cin >> columns;
					total_seats = rows * columns;
					delete[] cinemaSeats;
					cinemaSeats = new bool[total_seats];
					clearSeats();
					cout << "Successfully changed theater dimensions...\n(Note that all old reservations have been cleared in process)" << endl;
					cout << "Due to the change in dimensions, Please set new classes and new ticket price for each class" << endl;
					setting = 2;
				}
				if (setting == 2)
				{
					cout << "Please enter the number of different classes" << " (Max:" << rows << ")" << endl;
					cin >> class_no;
					while (class_no > rows)
					{
						cout << "The number of classes is more than the number of rows!\nPlease enter a valid number" << " (Max:" << rows << ")" << endl;
						cin >> class_no;
					}
					delete[] classes_rows;
					delete[] classes_price;
					delete[] seatsAvailable;
					classes_rows = new int[class_no + 1];
					classes_price = new double[class_no + 1];
					seatsAvailable = new int[class_no + 1];
					for (int i = 1; i <= class_no; i++)
					{
						cout << "Please enter number of rows of class number " << i << endl;
						cin >> classes_rows[i];
						seatsAvailable[i] = classes_rows[i] * columns;
						cout << "Please enter ticket price of class number " << i << endl;
						cin >> classes_price[i];
					}

				}
				else if (setting = 3)
				{
					cout << "Returning to main menu..." << endl;
					break;
				}
			}
			break;
		default: // Wrong number entered
			cout << "Wrong Choice!\nPlease try again";
			break;
		}
		cin.ignore();cin.get();
		system("cls");
	}
}
