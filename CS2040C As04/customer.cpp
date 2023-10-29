#include "customer.h"
#include "heap.h"
#include <iostream>
using namespace std;
int comparisonWay = 0; // 0 for arrival time, 1 for processing time


bool Customer::operator>(const Customer& c) {
	return comparisonWay ? processing_time < c.processing_time : arrival_time < c.arrival_time; // a customer is "greater" if his time is shorter
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

	for (int round = 0; round<2; round++) {
		cout << endl << endl;
		cout << "Test Round " << round + 1 << endl;
		cout << (round == 0 ? "First come first serve" : "Customer with the least PT served first") << endl;
		comparisonWay = round; //round 0 is FIFO, round 1 compares the PT
		current_time = 0;
		totalWaitingTime = 0;
		index = 0; //index of the current customer being served
		PT_left = 0; //processing time left for current customer

		while (index < n_cust) { //exit loop when all the customers have been served already
			//Customer will only arrive in the first n_cust min according to customer behaviour
			if (current_time < n_cust) { 
				cout << "Customer arrives at time " << custList[current_time].AT() << " with PT=" << custList[current_time].PT() << endl;
				if (queue.empty() && PT_left < 1) {
					//no one is waiting when the queue is empty and the server is not busy
					cout << "Customer arrives when no one is waiting" << endl;
				}
				queue.insert(custList[current_time]);
			}
			if (PT_left < 1) { 
				//server is done serving the customer and ready to serve the next one
				current_cust = queue.extractMax();
				PT_left = current_cust.PT(); //processing time resets with new customer's PT
				index++; 
				WT = current_time - current_cust.AT();
				totalWaitingTime += WT;
				cout << "Customer is served at time " << current_time << " with AT=" << current_cust.AT() << " and PT=" << current_cust.PT() << " after waiting for "
					<< WT << " min." << endl;
			}
			if (current_time < n_cust) {
				//every iternation of the loop is 1 min if there are still customers arriving
				PT_left--;
				current_time++;
			}
			else {
				//once all the customers have arrived and inserted into the queue, jump to the next time when customer will be cleared
				current_time += PT_left;
				PT_left = 0;
			}
		}
		cout << "Total Waiting Time: " << totalWaitingTime << endl;
		cout << "Average Waiting Time: " << totalWaitingTime / (float)n_cust << endl;
	}

	delete[] custList;
}