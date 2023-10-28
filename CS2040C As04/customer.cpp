#include "customer.h"
#include "heap.h"
#include <iostream>
using namespace std;
int comparisonWay = 0; // 0 for arrival time, 1 for processing time


bool Customer::operator>(const Customer& c) {
	return comparisonWay ? processing_time < c.processing_time : arrival_time < c.arrival_time; // a customer is "greater" if his time is shorter
};

bool isSame(Customer a, Customer b) {
	//assuming all customers arrive at different timings
	if (a.AT() > b.AT()) {
		return false;
	}
	if (b.AT() > a.AT()) {
		return false;
	}
	return true;
};

void customerQueueTest(int n_cust) { //n_cust is 10 for the test case
	int current_time = 0;
	int totalWaitingTime = 0;
	int i; 
	int WT; // waiting time for each customer
	int index;
	int PT_left;
	Customer current_cust;


	Heap<Customer> queue;

	Customer* custList = new Customer[n_cust]; //creating array to store list of customer
	cout << endl << endl << "Setup" << endl;
	cout << "List of customers and their arrival and processing times" << endl;
	for (i = 0; i<n_cust; i++) //storing customer with their arrival time and processing time
	{
		custList[i].setAT(i);
		custList[i].setPT((n_cust - i) % (n_cust / 2) + 1 + (i % 2)*(n_cust / 2));
		cout << "Customer " << i << " will arrive at time " << custList[i].AT() << " with PT=" << custList[i].PT() << endl;
	}
	cout << endl;

	for (int round = 0; round<1; round++) { //chnange back to round 2 when done
		cout << endl << endl;
		cout << "Test Round " << round + 1 << endl;
		cout << (round == 0 ? "First come first serve" : "Customer with the least PT served first") << endl;
		comparisonWay = round; //round 0 is FIFO, round 1 compares the PT
		current_time = 0;
		totalWaitingTime = 0;
		index = 0;
		PT_left = 0;

		while (index < n_cust) {
			//customer will only arrive in the first 10 iteration of the loop for example
			if (current_time < n_cust) {
				cout << "Customer arrives at time " << custList[current_time].AT() << " with PT=" << custList[current_time].PT() << endl;
			}
			if (queue.empty() && PT_left < 1) {
				cout << "Customer arrives when no one is waiting" << endl;
			}
			if (current_time < n_cust) {
				queue.insert(custList[current_time]);
			}
			if (PT_left < 1) {
				current_cust = queue.extractMax();
				PT_left = current_cust.PT();
				index++;
				WT = current_time - current_cust.AT();
				totalWaitingTime += WT;
				cout << "Customer is served at time " << current_time << " with AT=" << current_cust.AT() << " and PT=" << current_cust.PT() << " after waiting for "
					<< WT << " min." << endl;
			}
			PT_left--;
			current_time++;
		}
		cout << "Total Waiting Time: " << totalWaitingTime << endl;
		cout << "Average Waiting Time: " << totalWaitingTime / (float)n_cust << endl;
	}


	delete[] custList;
}

/*		//check if <= is correct exit condition
		while (index <= n_cust) {
			// you should change all of the code here inside
			//customer will only arrive in the first 10 iteration of the loop for example
			if (current_time < n_cust) {
				cout << "Customer arrives at time " << custList[current_time].AT() << " with PT=" << custList[current_time].PT() << endl;
			} 
			if (queue.empty()) {
				cout << "Customer arrives when no one is waiting" << endl;
			}
			if (current_time < n_cust) {
				queue.insert(custList[index]);
			}
			if (isSame(queue.peekMax(), custList[index])) {
				if (printedserve == 0) {
					WT = current_time - current_cust.AT();
					totalWaitingTime += WT;
					cout << "Customer is served at time " << current_time << " with AT=" << current_cust.AT() << " and PT=" << current_cust.PT() << " after waiting for "
						<< WT << " min." << endl;
					PT_left = current_cust.PT();
					printedserve = 1;
				}
				PT_left--;
			}
			if (PT_left == 0) {
				queue.deleteItem(current_cust);
				printedserve = 0;
				index++;
				current_cust = queue.peekMax();
			}
			current_time++;
		}
		cout << "Total Waiting Time: " << totalWaitingTime << endl;
		cout << "Average Waiting Time: " << totalWaitingTime / (float)n_cust << endl;
		//round++;*/
