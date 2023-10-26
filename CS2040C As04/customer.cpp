#include "customer.h"
#include "heap.h"
#include <iostream>
using namespace std;
int comparisonWay = 0; // 0 for arrival time, 1 for processing time


bool Customer::operator>(const Customer& c) {
	return comparisonWay ? processing_time < c.processing_time : arrival_time < c.arrival_time; // a customer is "greater" if his time is shorter
};

bool Customer::operator<(const Customer& c) {
	return comparisonWay ? processing_time > c.processing_time : arrival_time > c.arrival_time; // a customer is "smaller" if his time is shorter
};


void customerQueueTest(int n_cust) { //n_cust is 10 for the test case
	int current_time = 0;
	int totalWaitingTime = 0;
	int i;
	int WT = 0; // waiting time for each customer

	Heap<Customer> queue; //creating a heap called queue for type Customer

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

	for (int round = 0; round<2; round++) {
		// you may need a big modification within this for-loop
		cout << endl << endl;
		cout << "Test Round " << round + 1 << endl;
		cout << (round == 0 ? "First come first serve" : "Customer with the least PT served first") << endl;
		comparisonWay = round; //round 0 is FIFO, round 1 compares the PT
		current_time = 0; //cannot be a variable
		totalWaitingTime = 0; //cannot be a variable
		int index = 0; //havent set to increase
		int sum_PT = 0;
		queue.insert(custList[index]); //how to print out to check if it is inserted correctly
		//queue.printHeapArray(); is it because of templete it doesnt work?
		//cout << queue._heap[0].AT() << endl; //why is it inaccessible

		Customer c = queue.extractMax();
		cout << c.AT() << endl;
	
		cout << "Customer arrives at time " << custList[index].AT() << " with PT=" << custList[index].PT() << endl;

		/*
		while (!queue.empty()) {

			// you should change all of the code here inside
			Customer c = queue.extractMax();
			if (sum_PT == current_time) {
				cout << "Customer arrives when no one is waiting" << endl;
			}
			cout << "Customer is served at time " << current_time << " with AT=" << c.AT() << " and PT=" << c.PT() << " after waiting for "
				<< WT << " min." << endl;
		}
		cout << "Total Waiting Time: " << totalWaitingTime << endl;
		cout << "Average Waiting Time: " << totalWaitingTime / (float)n_cust << endl;
		*/
	}


	delete[] custList;
}
