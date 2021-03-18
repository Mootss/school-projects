#include <iostream>
#include <string>
#include <limits>

// Initialize public variables
int trainsUpTime[4] = {9, 11, 13, 15};
int trainsUpTickets[4] = {480, 480, 480, 480};
float trainsUpMoney[4] = {0.0, 0.0, 0.0, 0.0};

int trainsDownTime[4] = {10, 12, 14, 16};
int trainsDownTickets[4] = {480, 480, 480, 640};
float trainsDownMoney[4] = {0.0, 0.0, 0.0, 0.0};
std::string line = "========================================================";

void task1();
void task2();
void task3();

int main(){
	startMain:while (1) {
		task1();
		task2();

		prompt:std::cout << "\nThank you for using us! Would you like to make another booking? press Y for yes or N for no.\n 	> ";
		std::cin.clear();std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');			
		char yn;
		std::cin >> yn;
		if (yn == 'y') { goto startMain; }
		else if (yn == 'n') { 
			task3();
			break;
		}
		else { goto prompt; }
	}
}

void task1(){
	// Task 1

	// trains data table
	std::cout << "==============================\n Welcome To Mountain Railway!\n==============================\n";
	std::cout << line << std::endl << "UP Trains:-";
	std::cout << std::endl << "Train Time 	Available Train Tickets 	Money" << std::endl;
	for (int i = 0; i < 4; i++) { // loop and print table
		std::cout << trainsUpTime[i] <<"		";
		if (trainsUpTickets[i] == 0) { // print closed if trainsUpTime[count] equals 0
			std::cout << "CLOSED";
		} else {
			std::cout <<  trainsUpTickets[i]; }
		std::cout <<"				$"<< trainsUpMoney[i] << std::endl;
	}
	std::cout << line << std::endl << "DOWN Trains:-";
	std::cout << std::endl << "Train Time 	Available Train Tickets 	Money" << std::endl;
	for (int i = 0; i < 4; i++) {
		std::cout << trainsDownTime[i] <<"		";
		if (trainsDownTickets[i] == 0) {
		 	std::cout << "CLOSED";
		} else {
		 	std::cout << trainsDownTickets[i];
		}
		 std::cout << "				$"<< trainsDownMoney[i] << std::endl;
	}
}

void task2(){
	// Task 2

	// initialize
	const float ticketCost = 25.00;
	char sellingTickets = 'Y';
	float timeUp = 0.0;
	float timeDown = 0.0;
	int numTickets = 0;
	float totalCostOneTrip = 0.0;
	int indexUp = 0;
	int indexDown = 0;

	if (sellingTickets == 'Y') {
		std::cout << "\nWhat time would you like to go up the mountain ?\n 	> ";
		std::cin >> timeUp; // get input
		while (1) { // loop until a valid input is given;
			if (std::cin.fail()) { // validate data type
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // basically ignores uneeded stuff
				std::cout << "\nInvalid Input! Enter the time you would like to go up the mountain, as an integer, eg: 9" << "\n 	> ";
				std::cin >> timeUp;
			}
			checkTimeUp:if (timeUp != 9 && timeUp != 11 && timeUp != 13 && timeUp != 15) { // check given time
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');			
				std::cout << "\nInappropriate time! At what time would you like to go up the mountain ?\n 	> ";
				std::cin >> timeUp;
				goto checkTimeUp;
			}

			if (!std::cin.fail())
			break;
		}
		for (int i = 0; i <= 4; i++) {
			if (timeUp == trainsUpTime[i]) {
				indexUp = i;
			}
		}

		std::cout << "\nWhat time would you like to go down the mountain ?\n 	> ";
		std::cin.clear(); // clear previous values
		std::cin >> timeDown; // get input
		while (1) {
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // basically ignores uneeded stuff
				std::cout << "\nInvalid Input! Enter the time you would like to go down the mountain, as an integer, eg: 12" << "\n 	> ";
				std::cin >> timeDown;
			}
			checkTimeDown:if (timeDown != 10 && timeDown != 12 && timeDown != 14 && timeDown != 16) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');			
				std::cout << "\nInappropriate time! At what time would you like to go down the mountain ?\n 	> ";
				std::cin >> timeDown;
				goto checkTimeDown;
			}

			if (!std::cin.fail())
			break;
		}
		for (int i = 0; i <= 4; i++) {
			if (timeDown == trainsDownTime[i]) {
				indexDown = i;
			}
		}

		std::cout << "\nHow many tickets would you like to buy? Every 10th ticket is free!\n 	> ";
		std::cin.clear();
		std::cin >> numTickets;

		while (numTickets > trainsUpTickets[indexUp] || numTickets > trainsUpTickets[indexDown]) {
			std::cout << "\nSorry there are not enough tickets, ";
			checkNumTickets:std::cout << "enter any other number of tickets or choose 0 tickets to cancel..\n 	> ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> numTickets;
			if (std::cin.fail()) {
				goto checkNumTickets;
			}
		}

		// calculate the costs and stuff
		totalCostOneTrip = numTickets * ticketCost; // calc total cost
		for (int i = 9; numTickets > i; i+=10) { // decrement total cost by $25 for every tenth person
			totalCostOneTrip -= 25; 
		}
		std::cout << "\nYour total cost is " << totalCostOneTrip * 2;		

		trainsUpTickets[indexUp] -= numTickets;
		trainsDownTickets[indexDown] -= numTickets;
		trainsUpMoney[indexUp] += totalCostOneTrip;
		trainsDownMoney[indexDown] += totalCostOneTrip;
	}
}

void task3() {
	// task 3 

	int passengersUp[4] = {0, 0, 0, 0};
	int passengersDown[4] = {0, 0, 0, 0};
	int totalPassengers = 0;
	float totalMoneyTaken = 0.0;

	std::cout << line << "\nEnd of the day results:-\nTrip time 	Passengers served\n----------------------------------\n";
	for (int i = 0; i < 4; i++) {
		passengersUp[i] = 480 - trainsUpTickets[i];
		passengersDown[i] = 480 - trainsDownTickets[i];
		passengersDown[3] = 640 - trainsDownTickets[3];

		std::cout << trainsUpTime[i] <<":00 		"<< passengersUp[i] << std::endl;
		std::cout << trainsDownTime[i] <<":00 		"<< passengersDown[i] << std::endl;

		totalMoneyTaken += trainsUpMoney[i] + trainsDownMoney[i]; 
		totalPassengers += passengersUp[i];
	}

	std::cout << "\nTotal passengers for the day: " << totalPassengers << std::endl;
	std::cout << "\nTotal money collected for the day: " << totalMoneyTaken << std::endl;

	std::cout << "\nPress ENTER to exit console...";
	int x;
	std::cin >> x;
}

// end of code :)