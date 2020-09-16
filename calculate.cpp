//Emily Wilber
//CPSC 1071: 003
//Bug Smashers
//September 15, 2020


#include <iostream>
#include <cmath>
#include <cstdio>
#include <limits>

#define TRUE 1
#define FALSE 0 
using namespace std;


//function for calculating the amount of interest on a monthly payment
double calculateMonthlyInterest(double air, double p) {
        return (air / 1200 * p);
}


//calculates the total interest for a loan
//Note: A simpler way to calculate total interest would be to calculate the total amount paid (number of months * monthly payment) minus the principal.
double calculateTotalInterest(double air, double p, int months, double monthlyPayment) {
        double sum = 0;
        int i = 0;
        double monthlyInterest = 0;

        for (i = 0; i < months; i++) {
                monthlyInterest = calculateMonthlyInterest(air, p);
                sum += monthlyInterest;
                p -= monthlyPayment - monthlyInterest;
        }
        return sum;
}


// function for calculating number of months remaining
//assuming compounded monthly
int paymentMonths(double p, double air, double mp) {			
	
	int  months = 0.5 + (log (mp) - log(mp - (air/ 1200.0 * p)))/ log (air / 1200.0 + 1.0);
	int plusTen = 0.5 + (log (mp + 10) - log(mp + 10 - (air/ 1200.0 * p)))/ log (air / 1200.0 + 1.0);


	printf("%d months (%.1f years) are needed to pay your loan off.\r\n\r\n", months, static_cast<double>(months)/12);
	printf("Did you know that if you paid an additional $10 per month, you would pay off your loan %d month(s) earlier?\r\n\r\n", months - plusTen);
	
	double totalInterest = calculateTotalInterest(air, p, months, mp);
	printf("The total interest paid is $%.2f and the total amount you'll pay is $%0.2f.\r\n\r\n", totalInterest, totalInterest + p);	

	return months;
}

// finds input to calculate loan with
void paymentDriver() {		
	int inputValid = FALSE;
	char anotherLoan = 'y';
	while (anotherLoan == 'y' || anotherLoan == 'Y') {				
		double monthlyPayment = 0;
		double principal = 0;
		double annIntRate = 0;
		cout << "Loan Payment Calculator\r\n";
		cout << "Please input your principal amount: ";
		cin >> principal;	
		while(!inputValid) {
			if(cin.fail()) {	
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout << "This input is invalid. Try again: ";
				cin >> principal; 
			}	
			else {
				if (principal >= 0) {
					inputValid = TRUE;
				}
				else {
					cout << "Principal cannot be negative\r\nRe-enter principal: ";
					cin >> principal; 
				}
			}

		}

		cout << "Please input your annual interest rate (in %): ";
		cin >> annIntRate;
		inputValid = FALSE;
		while(!inputValid) {
			if(cin.fail()) {	
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout << "This input is invalid. Try again: ";
				cin >> annIntRate; 
			}	
			else {
				if (annIntRate >= 0) {
					inputValid = TRUE;
				}
				else {
					cout << "Annual Interest Rate cannot be negative\r\nRe-enter annual interest rate: ";
					cin >> annIntRate; 
				}
			}

		}

		cout << "Please input your monthly payment: ";	
		cin >> monthlyPayment;
		inputValid = FALSE;
		while(!inputValid) {
			if(cin.fail()) {	
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
				cout << "This input is invalid. Try again: ";
				cin >> monthlyPayment; 
			}	
			else {
				if (monthlyPayment > 0) {
					inputValid = TRUE;
				}
				else {
					cout << "Monthly payment must be positive\r\nRe-enter monthly payment: ";
					cin >> monthlyPayment; 
				}
			}

		}
		cout << "\r\nCalculating...\r\n";

		paymentMonths(principal, annIntRate, monthlyPayment); 
		// ask use if another estimate is desired and validate response
    		inputValid = FALSE;
		while (!inputValid)  {
			cout << "Calculate another loan? (y/n): ";
			cin >> anotherLoan;
			if ((anotherLoan == 'y') || (anotherLoan =='Y') || (anotherLoan == 'n') || (anotherLoan == 'N'))  {
				inputValid = TRUE;
			}
		}
	}
}
//calculates earnings
double estimateEarnings(int ageCurrent, int ageRetired, double moneySaved, double monthlyContribution, double annualReturn) {
	for (int months = 0; months < (ageRetired - ageCurrent) * 12; months++)  {
		moneySaved += moneySaved * static_cast<double>(annualReturn) / 1200;
		moneySaved += static_cast<double>(monthlyContribution);
	}
	return moneySaved;
}

//function to estimate savings at retirement
void estimateDriver() {
	int ageCurrent = 0;
	int ageRetired = 0;
	double moneySaved = 0;
	double monthlyContribution = 0;
	double annualReturn = 0;	
	int inputValid = FALSE;
	char anotherEstimate = 'y';

    while (anotherEstimate == 'y' || anotherEstimate == 'Y') {
	cout << "Estimate savings at retirement\r\nDisclaimer: This is only a rough estimate!\r\n\r\n";
	cout << "Enter your current age in years: ";
	cin >> ageCurrent;	
	inputValid = FALSE;
	while(!inputValid) {
		if(cin.fail()) {	
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "This input is invalid. Try again: ";
			cin >> ageCurrent; 
		}	
		else {
			if ( ageCurrent > 0) {
				inputValid = TRUE;
			}
			else {
				cout << "Age cannot be 0 or less\r\nRe-enter age in years: ";
				cin >> ageCurrent; 
			}
		}
	}

	cout << "Enter your target retirement age: ";
	cin >> ageRetired;
	inputValid = FALSE;
	while(!inputValid) {
		if(cin.fail()) {	
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "This input is invalid. Try again: ";
			cin >> ageRetired; 
		}	
		else {
			if ( ageRetired > ageCurrent) {
				inputValid = TRUE;
			}
			else {
				cout << "Age cannot be less than or equal to current age\r\nRe-enter retirement age in years: ";
				cin >> ageRetired; 
			}
		}
	}

	cout << "How much have you saved towards retirement?: ";
	cin >> moneySaved;
	inputValid = FALSE;
	while(!inputValid) {
		if(cin.fail()) {	
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "This input is invalid. Try again: ";
			cin >> moneySaved; 
		}	
		else {
			if (moneySaved >= 0) {
				inputValid = TRUE;
			}
			else {
				cout << "You cannot have negative savings\r\nRe-enter savings: ";
				cin >> moneySaved; 
			}
		}
	}

	cout << "Enter your monthly contribution to retirement: ";
	cin >> monthlyContribution;
	inputValid = FALSE;
	while(!inputValid) {
		if(cin.fail()) {	
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "This input is invalid. Try again: ";
			cin >> monthlyContribution; 
		}	
		else {
			if (monthlyContribution  > 0) {
				inputValid = TRUE;
			}
			else {
				cout << "You must contribute more than $0 per month\r\nRe-enter monthly contribution: ";
				cin >> monthlyContribution; 
			}
		}
	}

	cout << "Enter the estimate annual return on investment (in percent): ";
	cin >> annualReturn;
	inputValid = FALSE;
	while(!inputValid) {
		if(cin.fail()) {	
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			cout << "This input is invalid. Try again: ";
			cin >> annualReturn; 
		}	
		else {
			if (annualReturn >=  0) {
				inputValid = TRUE;
			}
			else {
				cout << "Annual Return cannot be negative\r\nRe-enter annual return: ";
				cin >> annualReturn; 
			}
		}
	}

	double earnings = estimateEarnings(ageCurrent, ageRetired, moneySaved, monthlyContribution, annualReturn);
	
	printf("Estimated retirement savings: $%0.2f\r\n", earnings);
	cout << "Estimated retirement growth: $" << earnings - moneySaved - (monthlyContribution * 12) * (ageRetired - ageCurrent)  << "\r\n";
    
	// ask use if another estimate is desired and validate response
    	inputValid = FALSE;
	while (!inputValid)  {
		cout << "Calculate another estimate? (y/n): ";
		cin >> anotherEstimate;
		if ((anotherEstimate == 'y') || (anotherEstimate =='Y') || (anotherEstimate == 'n') || (anotherEstimate == 'N'))  {
			inputValid = TRUE;
		}
	}	
	
    }//main while loop

}
//runs the menu in a loop
void runMenuSystem() {
	int isRunning = TRUE;
	
	while(isRunning) {		
			cout << "\r\n\r\n******* Welcome to Bug Smashers Financial *******\r\n\r\n";
			cout << "Menu:\r\n";
			cout << "[E] Estimate how much money you  will have at retirement\r\n[L] Loan Payoff Calculator\r\n[Q] Quit program\r\n\r\n";
			char selection = 'a';
			cout << "Enter your choice and press enter: ";
			cin >> selection;
			cout << "\r\n\r\n";

			if (selection == 'E' || selection == 'e') {
				estimateDriver();
				
			}
			else if (selection == 'L' || selection == 'l') {
				paymentDriver();			
			}
			else if (selection == 'Q' || selection == 'q') {
				cout << "Thank you for using this program.\r\n";
				isRunning = FALSE;
			}
			else {
				cout << "This is not a valid input. Please try again.\r\n";
			}
	
	}
}

int main() {	
	runMenuSystem();
	return 0;
}
