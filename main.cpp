/*
 *	Author:			Jay Ramirez
 *	Title:			Bulls and Cows Guessing Game
 *	Class: 			CSCE 121-530
 *	Last Updated:	September 28, 2018
 */
 
#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;

vector<int> DecToVec(int decimalNum, int digits) {
	//Converts an integer decimal number to a vector
	//with each digit in ordered indeces and adds leading
	//zeros if decimalNum is smaller than digits.
	vector<int> vectorA;
	vector<int> remainder;
	int quotient = 0;
	int i = 0; 
	
	quotient = decimalNum / 10;
	
	remainder.push_back(decimalNum % 10);
	
	//This is decimal to base conversion procedure,
	//but here base is 10 only to separate digits.
	while (quotient != 0) {
		remainder.push_back(quotient % 10);
		quotient = quotient / 10;
	}
	
	//If number given is smaller or same size than specified number 
	//of digits, then make a zero vector up to the specified size
	if (remainder.size() <= digits) {
		for (i = 0; i < digits; i++) {
			vectorA.push_back(0);
		}
		//Then fill in given number starting from right
		//to keep leading zeros and correct order
		for (i = 0; i < remainder.size(); i++) {
			vectorA.at(vectorA.size() - 1 - i) = remainder.at(i);
		}
	}
	//If number given is larger than desired digits, 
	//make a zero vector the size of given number
	else {
		for (i = 0; i < remainder.size(); i++) {
			vectorA.push_back(0);
		}
		//Fill in starting from right in correct order
		for (i = 0; i < remainder.size(); i++) {
			vectorA.at(vectorA.size() - 1 - i) = remainder.at(i);
		}
	}
	
	return vectorA;
	
}

vector<int> RandomVector(int numElements) {
	//Create vector with available/possible digits to show up in code with 2-9 digits
		vector<int> availNumbers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
		vector<int> randomVector;
		int randomIndex = 0;
		
		//Generate a random index number from 0-10
		for (int i = 0; i < numElements; i++) {
			randomIndex = rand() % 10;
			
			//Check if possible digit vector at the random index is a zero,
			while (availNumbers.at(randomIndex) == 0) {
				randomIndex = rand() % 10;
			}
			//If not zero, then put that digit in the next available
			//spot on randomVector
			randomVector.push_back(availNumbers.at(randomIndex));
			//Set that spot to zero so that digit cannot be reused
			availNumbers.at(randomIndex) = 0;
		}
	//Return finished random vector with unrepeated digits
	return randomVector;
}

vector<int> DigitCount(vector<int> digitVector) {
	//Count the number of instances of digits 0-9 in any int vector
	//and return the result as a vector where indeces 0-9 represent that
	//digit, and the value contained is the number of instances
	vector<int> vectorDigitCount = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	
	//Check every value in digitVector
	for (int i = 0; i < digitVector.size(); i++) {
		//Check every digit 0-9
		for (int j = 0; j < 10; j++) {
			//Increase by one every instance of j
			if (digitVector.at(i) == j) {
				vectorDigitCount.at(j)++;
			}
		}
	}
	return vectorDigitCount;
}

int main() {
    srand(std::chrono::duration_cast<std::chrono::milliseconds>
     (std::chrono::system_clock::now().time_since_epoch()).count()%2000000000); 
    // needed to autograde some test cases in Mimir
	
	int numDigits = 0; 
	int i = 0;
	int bullsInt = 0;
	int cowsInt = 0;
	vector<int> code;
	vector<int> guessVector;
	vector<int> guessRemainder;
	vector<int> codeDigitCount = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	vector<int> guessDigitCount = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int guessVal = 0;
	bool bullBool = false; //Indicates a correct, all-bull guess if true
	bool duplicateBool = false;
	bool duplicateCheckBool = false;
	
	//Ask for first user input
	cout << "Enter number of digits in code (3, 4 or 5): ";
	cin >> numDigits;
	
	//Keep asking for input until it is valid
	while ((numDigits < 0) || (numDigits == 1) || (numDigits == 2) || (numDigits >= 6)) {
		
		cout << "Enter valid number of digits (3, 4, or 5): ";
		cin >> numDigits;
	}
	
	//If the entry is cheat code for inputting custom code for guessing
	if (numDigits == 0) { 
		int customCode = 0;
		int customDigits = 0;
		
		//Ask for custom code as single integer
		cout << "Enter code: ";
		cin >> customCode;
		
		//Ask for number of digits of code
		cout << "Enter number of digits in code: ";
		cin >> customDigits;
		
		code = DecToVec(customCode, customDigits);
		
	}
	
	//Requested random 3, 4, or 5 digit code to guess
	else if ((numDigits == 3) || (numDigits == 4) || (numDigits == 5)){
		
		code = RandomVector(numDigits);
		
	}
	
	//Output code separated by hyphens, eg.: 0-3-4
	cout << "Number to guess: ";
	
	for (i = 0; i < code.size()-1; i++) {
		cout << code.at(i) << "-";
	}
	cout << code.at(code.size()-1) << endl;
	
	
	
	while (bullBool == false) {
		//Ask for guess input
		cout << "Enter Guess: ";
		cin >> guessVal;
		
		guessVector = DecToVec(guessVal, code.size());
				
		//Check first for a matching guess
		if (code == guessVector) {
			cout << code.size() << " bulls... ";
			
			for (i = 0; i < code.size() - 1; i++) {
				cout << code.at(i) << "-";
			}
			cout << code.at(code.size() - 1) << " is correct!" << endl;
			bullBool = true;
		}
		else {
			//check each vector element by element and determine cows and bulls
			codeDigitCount = DigitCount(code);
			guessDigitCount = DigitCount(guessVector);
			i = 0;
			bullsInt = 0;
			cowsInt = 0; 
			duplicateBool = true;
			duplicateCheckBool = false;
			
			i = 0; //This caused me a couple hours of trouble
			
			//Loop through the guess vector and trip the duplicateCheckBool
			//if a number is repeated 
			while (duplicateBool){
				if (guessDigitCount.at(i) >= 2) {
					duplicateCheckBool = true;
					duplicateBool = false;
				}
				i++;
				if (i == 10) {
					duplicateBool = false;
				}
			}
			
			//If guess is larger than code size
			if (guessVector.size() > code.size()) {
				cout << "You can only enter " << code.size() << " digits." << endl;
			}
			
			//If duplicate number is detected in guess
			else if (duplicateCheckBool) {
				cout << "Each number must be different." << endl;
			}
			//If valid guess is made, check bulls and cows
			else {
				//Check if same digits in same spots to increase bull count
				for (i = 0; i < code.size(); i++) {
					if (code.at(i) == guessVector.at(i)) {
						bullsInt++;
					}
				}
				//Check if both digit counter vectors have a one to increase cows count
				for (i = 0; i < 10; i++) {
					if ((codeDigitCount.at(i) == 1) && (guessDigitCount.at(i) == 1)) {
						cowsInt++;
					}
				}
				
				//Since cows also counts bulls as cows, update cows to
				//show non-bull cows
				cowsInt = cowsInt - bullsInt;
				cout << bullsInt << " bulls" << endl;
				cout << cowsInt << " cows" << endl;
			}
		}
	}

	return 0;
}