// COMPILATION: gcc gorjianm_exam1.cpp -o gorjianm_exam1.exe -lstdc++
//         RUN: ./gorjianm_exam1.exe
#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#define INT_MAX 1000
using namespace std;

const int mrow = 9, mcol = 25;
int matrix[mrow][mcol];
int fill_mat = 0;
deque<int> temp_q;


int fifopageFaults(int pages[], int page_num, int frame_size)
{
	for (size_t i = 0; i < mrow; i++)
	{
		for (size_t j = 0; j < mcol; j++)
		{
			matrix[i][j] = fill_mat;
		}
	}
	// set data structure to find the existence of a page
	unordered_set<int> page_set;
	// keeping track of the pages
	deque<int> indices;
	int page_faults = 0;

	for (int i=0; i<page_num; i++)
	{
		// check for the set empty place
		if (page_set.size() < frame_size)
		{
			// if not in the set then add it to it
			if (page_set.find(pages[i]) == page_set.end())
			{
				page_set.insert(pages[i]);
				matrix[mrow-1][i+1] = -1;

				// page fault tracker
				page_faults++;

				// adding the page to the trackers
				indices.push_back(pages[i]);
				temp_q.push_front(pages[i]);
			}
		} //end if

		else
		{
			// if not in the set then add it to it
			if (page_set.find(pages[i]) == page_set.end())
			{
				// getting the front
				int val = indices.front();
				// poping from the deque to empty space for the new page
				indices.pop_front();
				// erasing the poped page from the set too
				page_set.erase(val);
				// adding the new page to the set
				page_set.insert(pages[i]);
				// adding the page to the trackers
				indices.push_back(pages[i]);
				temp_q.push_front(pages[i]);
				// adding the page fault to the matrix to show the occurance
				matrix[mrow-1][i+1] = -1;
				// page fault tracker
				page_faults++;
			}
		} //end else

		// updating the matrix with the deque trackers
		for (int row=mrow-2;row>=0;row--){
			matrix[row][i+1] = temp_q[row];
		}
	} //end for
	return page_faults;
}

int lrupageFaults(int pages[], int page_num, int frame_size)
{
	for (size_t i = 0; i < mrow; i++)
	{
		for (size_t j = 0; j < mcol; j++)
		{
			matrix[i][j] = fill_mat;
		}
	}
	unordered_set<int> page_set;
	// keeping track of the lru pages
	unordered_map<int, int> indices;

	int page_faults = 0;
	for (int i=0; i<page_num; i++)
	{
		// check for the set empty place
		if (page_set.size() < frame_size)
		{
			// if not in the set then add it to it
			if (page_set.find(pages[i]) == page_set.end())
			{
				page_set.insert(pages[i]);
				temp_q.push_front(pages[i]);
				matrix[mrow-1][i+1] = -1;
				// page fault tracker
				page_faults++;
			}
			// add new page to the deque
			indices[pages[i]] = i;
		} // end if
		else
		{
			// if not in the set then add it to it
			if (page_set.find(pages[i]) == page_set.end())
			{
				// finding lru pages in the set
				int lru = INT_MAX, val;
				unordered_set<int>::iterator iter;
				for (iter = page_set.begin(); iter != page_set.end(); iter++)
				{
					if (indices[*iter] < lru)
					{
						lru = indices[*iter];
						val = *iter;
					}
				}
				// erasing indices page
				page_set.erase(val);
				// adding the new page
				page_set.insert(pages[i]);
				temp_q.push_front(pages[i]);
				matrix[mrow-1][i+1] = -1;
				// Increment page faults
				page_faults++;
			}
			// updating the new page to the indices
			indices[pages[i]] = i;
		} // end else
		// updating the matrix with the deque trackers
		for (int row=mrow-2;row>=0;row--){
			matrix[row][i+1] = temp_q[row];
		}
	} //end for
	return page_faults;
}

int secondChancePageFaults(int pages[], int page_num, int frame_size) {
    for (size_t i = 0; i < mrow; i++) {
        for (size_t j = 0; j < mcol; j++) {
            matrix[i][j] = fill_mat;
        }
    }
    int p = 0, page_faults = 0;
    int inputFrames[frame_size][2];
    for (int j = 0; j < frame_size; j++) {
		// initializing as empty
        inputFrames[j][0] = -1;
		// initializing as zero
        inputFrames[j][1] = 0;
    }
    for (int i = 0; i < page_num; i++) {
        bool check = false;
        for (int j = 0; j < frame_size; j++) {
            if (inputFrames[j][0] == pages[i]) {
                check = true;
                inputFrames[j][1] = 1;
                break;
            }
        }
        if (check == false) {

            while (inputFrames[p][1] == 1) {
                inputFrames[p][1] = 0;
                p++;
                if (p == frame_size)
                    p = 0;
            }
            inputFrames[p][0] = pages[i];
            inputFrames[p][1] = 1;
            temp_q.push_front(pages[i]);
            // adding the page fault to the matrix to show the occurance
            matrix[mrow-1][i+1] = -1;
            page_faults++;
            p++;
            if (p == frame_size)
                p = 0;
        }
        for (int row=mrow-2;row>=0;row--){
			matrix[row][i+1] = temp_q[row];
		}
    } // end for
    return page_faults;
}

int main()
{
	int options, input_options, frame_size, page_num;
	cout << "\nChoose an option [1] FIFO [2] LRU [3] SECOND-CHANCE (eg. 1): ";
	cin >> options;
    cout << "\nEnter frame size (eg. 4): ";
    cin >> frame_size;
    cout << "\nEnter number of pages (eg. 24): ";
    cin >> page_num;
	int pages[page_num];
	cout << "\nChoose an option [0] commandline-input [1] file-input (eg. 1): ";
	cin >> input_options;

	// reading from commandline
	if (input_options == 0){
		cout << "\nEnter pages with space (eg. 2 1 3 5 4 6...): ";
		for (int i = 0; i < page_num; i++) {
			cin >> pages[i];
		}
	}
	// reading from a *.txt file
	if (input_options == 1){
		int number;
		string file_name;
		cout << "\nEnter input file name (eg. file.txt): ";
		cin >> file_name;
		ifstream input_file(file_name);
		for (int i = 0; i < page_num; i++) {
			input_file >> number;
			pages[i] = number;
		}
		input_file.close();
	}

	if (options == 1)
	{
		cout << "--------------------------------------------------" << endl;
		cout << "FIFO Page Replacement Algorithm" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "Page Faults: " << fifopageFaults(pages, page_num, frame_size) << endl;
	}
	if (options == 2)
	{
		cout << "--------------------------------------------------" << endl;
		cout << "LRU Page Replacement Algorithm" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "Page Faults: " << lrupageFaults(pages, page_num, frame_size) << endl;
	}
	if (options == 3)
	{
		cout << "--------------------------------------------------" << endl;
		cout << "SECOND-CHANCE Page Replacement Algorithm" << endl;
		cout << "--------------------------------------------------" << endl;
		cout << "Page Faults: " << secondChancePageFaults(pages, page_num, frame_size) << endl;
	}
	cout << "--------------------------------------------------" << endl;
	for (size_t i = 0; i < mrow; i++)
	{
		for (size_t j = 0; j < mcol; j++)
		{
			if(matrix[i][j] == 0)
                cout <<"  ";
			else if (matrix[i][j] == -1)
				cout << "F ";
            else
				cout << matrix[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "--------------------------------------------------" << endl;
	return 0;
}

// test case:
// frame size: 4
// number of pages: 24
// pages: 2 1 3 5 4 6 3 7 4 7 3 3 5 5 3 1 1 1 7 1 3 4 1 2
// or a *.txt file with the pages numbers with space

// REFERENCES
// I got the idea from the references [1] and [2] but the code was rewroten by 
// myself and also adding the output printing.

// [1] https://github.com/Ghamry0x2/Page-Replacement-Algorithms/blob/master/src/
//     PageReplacementAlgorithms/PageReplacementAlgorithms.java
// [2] https://www.geeksforgeeks.org/second-chance-or-clock-page-replacement-policy/