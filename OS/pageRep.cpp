#include <bits/stdc++.h>
using namespace std;

int noOfFrames = 3;

bool find(int frame[], int page){
	for(int i=0; i<noOfFrames; i++){
		if(frame[i] == page)
			return true;
	}
	return false;
}


void print(int frame[]){
	for(int i=0; i<noOfFrames; i++) {
		printf("%d ", frame[i]);
	}
	cout<<endl;
	return;
}
void FIFO(vector<int> refer){
	int frame[noOfFrames];
	memset(frame, -1, sizeof(frame));
	int faults = 0;
	int pos = 0;
	for (int i = 0; i < refer.size(); ++i) {
		if(!find(frame, refer[i])){
			frame[pos] = refer[i];
			faults++;
			pos = (pos+1)%noOfFrames;
		}
		else
			printf("Hit\n");
		print(frame);
		printf("===\n");
	}
	printf("No of faults = %d\n", faults - 3);
}

void Optimal(vector<int> &pages){
	int frame[noOfFrames];
	int faults = noOfFrames;
	int n = pages.size();
	for(int i=0; i < noOfFrames; i++)
		frame[i] = pages[i];
	for(int i=noOfFrames; i < n; i++){
		cout<<"==";
		print(frame);
		if(find(frame, pages[i]))
			continue;
		else{
			int pos = 0, far = i;
			for(int ii=0; ii < noOfFrames; ii++){
				bool found = false;
				for(int jj=i; jj < n; jj++){
					if(frame[ii] == pages[jj]){
						found = true;
						// cout<<frame[ii]<<" at "<<jj<<endl;
						if(jj > far){
							far = jj;
							pos = ii;
						}
						break;
					}
				}
				if(!found){
					pos = ii;
					break;
				}
			}
			frame[pos] = pages[i];
			faults++;
		}
	}
	printf("No of faults: %d\n", faults);
}

void LRUCounter(vector<int> pages){
	int clock = 0;
	int frame[noOfFrames], time[noOfFrames];
	for(int i=0; i<noOfFrames; i++){
		frame[i] = pages[i];
		time[i] = clock++;
	}
	int faults = 3, n = pages.size();
	bool flag = false;
	for(int i=noOfFrames; i < n; i++){
		cout<<"==";
		print(frame);
		flag = false;
		for(int j=0; j<noOfFrames; j++){
			if(frame[j] == pages[i]){
				flag = true;
				time[j] = clock++;
				continue;
			}
		}
		if(!flag){
			int _min = INT_MAX, ind = 0;
			for(int ii=0; ii<noOfFrames; ii++){
				if(time[ii] < _min){
					_min = time[ii];
					ind = ii;
				}
			}
			frame[ind] = pages[i];
			time[ind] = clock++;
			faults++;
		}
	}
	cout<<"==";
	print(frame);
	printf("No of faults: %d\n", faults);
}

void LRUStack(vector<int> pages){
	
}
int main(){
	int temp[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
	vector<int> refer;
	int n;
	int tmp;
	for(int i=0; i<sizeof(temp)/sizeof(temp[0]); i++){
		refer.push_back(temp[i]);
	}
	LRUCounter(refer);
}