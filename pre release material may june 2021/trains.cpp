// may june 2021 pre-release material solution in C++

// dependencies
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
	startMain:while (1) { // infinitely loop until prompted to break out
		task1(); // run task1
		task2(); // and then task2

		// ask user to run task3 or not
		prompt:std::cout << "\nThank you for using us! Would you like to make another booking? press Y for yes or N for no.\n 	> ";
		// below line prevents line breaks (pressing return key) from entering into input
		std::cin.clear();std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		char yn;
		std::cin >> yn;
		if (yn == 'y') { goto startMain; } // restarts program from task1 if the user gives a yes
		else if (yn == 'n') { // otherwise proceed to task3 and finish program
			task3();
			break;
		}
		else { goto prompt; } // loop until user gives an answer
	}
}

void task1(){
	// Task 1

	// prints trains data table
	std::cout << "==============================\n Welcome To Mountain Railway!\n==============================\n";
	std::cout << line << std::endl << "UP Trains:-";
	std::cout << std::endl << "Train Time 	Available Train Tickets 	Money" << std::endl;
	for (int i = 0; i < 4; i++) { // loop and print each item in the arrays
		std::cout << trainsUpTime[i] <<"		";
		if (trainsUpTickets[i] == 0) { // print "CLOSED" instead of 0 if the current trainsUpTime[count] is 0
			std::cout << "CLOSED";
		} else { 
			std::cout <<  trainsUpTickets[i]; 
		}
		std::cout <<"				$"<< trainsUpMoney[i] << std::endl;
	}

	// same as above forloop except its for down trains
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

	// initialize variables
	const float ticketCost = 25.00;
	char sellingTickets = 'Y';
	float timeUp = 0.0;
	float timeDown = 0.0;
	int numTickets = 0;
	float totalCostOneTrip = 0.0;
	int indexUp = 0;
	int indexDown = 0;

	if (sellingTickets == 'Y') {
		std::cout << "\nWhat time would you like to go up the mountain ?\n 	> "; // prompt user
		std::cin >> timeUp; // get input
		while (1) { // loop until a valid input is given;
			if (std::cin.fail()) { // handle error
				std::cin.clear(); // resets input
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); // basically ignores when the user presses ENTER
				std::cout << "\nInvalid Input! Enter the time you would like to go up the mountain, as an integer, eg: 9" << "\n 	> ";
				std::cin >> timeUp; // retry getting input
			}
			checkTimeUp:if (timeUp != 9 && timeUp != 11 && timeUp != 13 && timeUp != 15) { // check if given time is served
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');			
				std::cout << "\nInappropriate time! At what time would you like to go up the mountain ?\n 	> ";
				std::cin >> timeUp;
				goto checkTimeUp;
			}

			if (!std::cin.fail()) // if the user gives a valid time, then break out of loop and proceed
			break;
		}

		// the following is basically the same as the above one, except it prompts for when to go down
		std::cout << "\nWhat time would you like to go down the mountain ?\n 	> "; // prompt user
		std::cin.clear(); // clear values
		std::cin >> timeDown; // get input
		while (1) { // does the same thing as the prevous input timeUp
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //
				std::cout << "\nInvalid Input! Enter the time you would like to go down the mountain, as an integer, eg: 12" << "\n 	> ";
				std::cin >> timeDown;
			}
			checkTimeDown:if (timeDown != 10 && timeDown != 12 && timeDown != 14 && timeDown != 16) { 
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');			
				std::cout << "\nInappropriate time! At what time would you like to go down the mountain ?\n 	> ";
				std::cin >> timeDown;
				goto checkTimeDown; // retry prompt if an invalid time is given.
			}
			reTimeDown:if (timeUp > timeDown) { // raises error if the selected train to go up is greater than selected train to go down
				std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				std::cout << "\nError: You cant go up at " << timeUp << ":00 and go down at " << timeDown << ":00 !";
				std::cout << "\nInappropriate time! At what time would you like to go down the mountain ?\n 	> ";
				std::cin >> timeDown;
				goto reTimeDown; // retry 
			}

			if (!std::cin.fail())
			break; // break out of loop if no errors were raised while getting input from user
		}

		for (int i = 0; i <= 4; i++) {
			if (timeUp == trainsUpTime[i]) {
				indexUp = i;
			}
			if (timeDown == trainsDownTime[i]) {
				indexDown = i; 
			}
		}
		

		std::cout << "\nHow many tickets would you like to buy? Every 10th ticket is free!\n 	> ";
		std::cin >> numTickets;
		reNumTickets:if (std::cin.fail()) { // if user gives a improper input, retry getting the input
			std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			std::cout << "Please enter a valid number of tickets !\n 	> ";
			std::cin >> numTickets;
			goto reNumTickets; // retry until user gives a proper input
		}

		// inputs the amount of tickets and checks if the amount specified is available in the train
		// keep prompting user for input or let them cancel the operation
		while (numTickets > trainsUpTickets[indexUp] || numTickets > trainsUpTickets[indexDown]) {
			std::cout << "\nSorry there are not enough tickets, ";
			checkNumTickets:std::cout << "\nEnter any other number of tickets or choose 0 tickets to cancel..\n 	> ";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> numTickets;
			if (std::cin.fail()) {
				goto checkNumTickets;
			}
		}

		// calculate the costs and stuff
		totalCostOneTrip = numTickets * ticketCost; // calculate total cost
		for (int i = 9; numTickets > i; i+=10) { // decrement total cost by $25 for every tenth person
			totalCostOneTrip -= 25; 
		}
		std::cout << "\nYour total cost is $" << totalCostOneTrip * 2; // print the users final cost

		// update the train tickets array by subtracting it by the number of tickets the user bought
		trainsUpTickets[indexUp] -= numTickets;
		trainsDownTickets[indexDown] -= numTickets;

		// update moneys array by adding it aswell
		trainsUpMoney[indexUp] += totalCostOneTrip;
		trainsDownMoney[indexDown] += totalCostOneTrip;
	}
}

void task3() {
	// task 3 

	// initialize variables for task3
	int passengersUp[4] = {0, 0, 0, 0};
	int passengersDown[4] = {0, 0, 0, 0};
	int totalPassengers = 0;
	float totalMoneyTaken = 0.0;

	// prints out train data for the day
	std::cout <<"\n\n"<< line << "\nEnd of the day results:-\nTrip time 	Direction	Passengers served\n------------------------------------------------------\n";
	for (int i = 0; i < 4; i++) {
		// calc the stuffs
		passengersUp[i] = 480 - trainsUpTickets[i];
		passengersDown[i] = 480 - trainsDownTickets[i];
		passengersDown[3] = 640 - trainsDownTickets[3];

		// print out the trains up time values, add ":00" and a tabspace for more readabilty
		std::cout << trainsUpTime[i] <<":00 		Up 		";
		if (passengersUp[i] == 0) { // replace 0 with NONE
			std::cout << "NONE\n";
		} else { std::cout << passengersUp[i] << std::endl; }

	} std::cout << "\n"; // a line break cause why not
	for (int i = 0; i < 4; i++){
		// same as above, except for trains down times
		std::cout << trainsDownTime[i] <<":00 		Down 		";
		if (passengersDown[i] == 0) { // replace 0 with NONE, for readabilty and it looks nicer anyways
			std::cout << "NONE\n";
		} else { std::cout << passengersDown[i] << std::endl; }
 		
 		// add all the trains up and trains down money to totalMoneyTaken
		totalMoneyTaken += trainsUpMoney[i] + trainsDownMoney[i];
		totalPassengers += passengersUp[i]; // same thing here
	}

	// print out totals
	std::cout << "\nTotal passengers for the day: " << totalPassengers << std::endl;
	std::cout << "\nTotal money collected for the day: $" << totalMoneyTaken << std::endl;

	std::cout << "\nPress ENTER to exit console..."; // prompt user to exit
  	std::cin.get(); // this method reads any char from stdin
  	std::cin.get(); // this is done twice cause there would be characters buffered in stdin prevously
}

// end of code :)
