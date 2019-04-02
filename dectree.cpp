#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <math.h>
#include <float.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<int> vi;
typedef map<string, int> msi;
typedef vector<double> vd;

struct node													// struct node defines the structure of a node of the decision tree
{
	string splitOn;											// Stores which attribute to split on at a particular node
	string label;											// Stores the class label for leaf nodes. For nodes that are not leaf nodes, it stores the value of the attribute of the parent's' split 
	bool isLeaf;											// boolean flag for leaf nodes
	vector<string> childrenValues;							// Stores the values of the childrens' attributes
	vector<node*> children;									// Stores pointers to the children of a node
};

void parse(string&, vvs&);									// Parses a single line from the input file and stores the information into a vector of vector of strings 
void printAttributeTable(vvs&);								// For debugging purposes only. Prints a data table
vvs pruneTable(vvs&, string&, string);						// Prunes a table based on a column/attribute's name and the value of that attribute. Removes that column and all instances that have that value for that column
node* buildDecisionTree(vvs&, node*, vvs&);					// Builds the decision tree based on the table it is passed
bool isHomogeneous(vvs&);									// Returns true if all instances in a subtable at a node have the same class label
vi countDistinct(vvs&, int);								// Returns a vector of integers containing the counts of all the various values of an attribute/column
string decideSplittingColumn(vvs&);							// Returns the column on which to split on. Decision of column is based on entropy
int returnColumnIndex(string&, vvs&);						// Returns the index of a column in a subtable
bool tableIsEmpty(vvs&);									// Returns true if a subtable is empty
void printDecisionTree(node*);								// For degubbing purposes only. Recursively prints decision tree
string testDataOnDecisionTree(vs&, node*, vvs&, string);	// Runs a single instance of the test data through the decision tree. Returns the predicted class label
int returnIndexOfVector(vs&, string);						// Returns the index of a string in a vector of strings
double printPredictionsAndCalculateAccuracy(vs&, vs&);		// Outputs the predictions to file and returns the accuracy of the classification
vvs generateTableInfo(vvs &dataTable);						// Generates information about the table in a vector of vector of stings
string returnMostFrequentClass(vvs &dataTable);				// Returns the most frequent class from the training data. This class is used as the default class during the testing phase

void parse(string& someString, vvs &attributeTable)
{
	int attributeCount = 0;
	vs vectorOfStrings;
	while (someString.length() != 0 && someString.find(',') != string::npos)
	{
		size_t pos;
		string singleAttribute;
		pos = someString.find_first_of(',');
		singleAttribute = someString.substr(0, pos);
		vectorOfStrings.push_back(singleAttribute);
		someString.erase(0, pos+1);
	}
	vectorOfStrings.push_back(someString);
	attributeTable.push_back(vectorOfStrings);
	vectorOfStrings.clear();
}

/*
 * Prints a vector of vector of strings
 * For debugging purposes only.
 */
void printAttributeTable(vvs &attributeTable)
{
	int inner, outer;
	for (outer = 0; outer < attributeTable.size(); outer++) {
		for (inner = 0; inner < attributeTable[outer].size(); inner++) {
			cout << attributeTable[outer][inner] << "\t";
		}
		cout << endl;
	}
}

/*
 * Prunes a table based on a column/attribute's name
 * and value of that attribute. Removes that column
 * and all rows that have that value for that column.
 */
vvs pruneTable(vvs &attributeTable, string &colName, string value)
{
	int iii, jjj;
	vvs prunedTable;
	int column = -1;
	vs headerRow;
	for (iii = 0; iii < attributeTable[0].size(); iii++) {
		if (attributeTable[0][iii] == colName) {
			column = iii;
			break;
		}
	}
	for (iii = 0; iii < attributeTable[0].size(); iii++) {
		 if (iii != column) {
		 	headerRow.push_back(attributeTable[0][iii]);
		 }
	}
	prunedTable.push_back(headerRow);
	for (iii = 0; iii < attributeTable.size(); iii++) {
		vs auxRow;
		if (attributeTable[iii][column] == value) {
			for (jjj = 0; jjj < attributeTable[iii].size(); jjj++) {
				if(jjj != column) {
					auxRow.push_back(attributeTable[iii][jjj]);
				}
			}
			prunedTable.push_back(auxRow);
		}
	}
	return prunedTable;
}

/*
 * Recursively builds the decision tree based on
 * the data that it is passed and tha table info.
 */
node* buildDecisionTree(vvs &table, node* nodePtr, vvs &tableInfo)
{
	if (tableIsEmpty(table)) {
		return NULL;
	}
	if (isHomogeneous(table)) {
		nodePtr->isLeaf = true;
		nodePtr->label = table[1][table[1].size()-1];
		return nodePtr;
	} else {
		string splittingCol = decideSplittingColumn(table);
		nodePtr->splitOn = splittingCol;
		int colIndex = returnColumnIndex(splittingCol, tableInfo);
		int iii;
		for (iii = 1; iii < tableInfo[colIndex].size(); iii++) {
			node* newNode = (node*) new node;
			newNode->label = tableInfo[colIndex][iii];
			nodePtr->childrenValues.push_back(tableInfo[colIndex][iii]);
			newNode->isLeaf = false;
			newNode->splitOn = splittingCol;
			vvs auxTable = pruneTable(table, splittingCol, tableInfo[colIndex][iii]);
			nodePtr->children.push_back(buildDecisionTree(auxTable, newNode, tableInfo));
		}
	}
	return nodePtr;
}

/*
 * Returns true if all rows in a subtable
 * have the same class label.
 * This means that that node's class label
 * has been decided.
 */
bool isHomogeneous(vvs &table)
{
	int iii;
	int lastCol = table[0].size() - 1;
	string firstValue = table[1][lastCol];
	for (iii = 1; iii < table.size(); iii++) {
		if (firstValue != table[iii][lastCol]) {
			return false;
		}
	}
	return true;
}

/*
 * Returns a vector of integers containing the counts
 * of all the various values of an attribute/column.
 */
vi countDistinct(vvs &table, int column)
{
	vs vectorOfStrings;
	vi counts;
	bool found = false;
	int foundIndex;
	for (int iii = 1; iii < table.size(); iii++) {
		for (int jjj = 0; jjj < vectorOfStrings.size(); jjj++) {
			if (vectorOfStrings[jjj] == table[iii][column]) {
				found = true;
				foundIndex = jjj;
				break;
			} else {
				found = false;
			}
		}
		if (!found) {
			counts.push_back(1);
			vectorOfStrings.push_back(table[iii][column]);
		} else {
			counts[foundIndex]++;
		}
	}
	int sum = 0;
	for (int iii = 0; iii < counts.size(); iii++) {
		sum += counts[iii];
	}
	counts.push_back(sum);
	return counts;
}

/*
 * Decides which column to split on
 * based on entropy. Returns the column
 * with the least entropy.
 */
string decideSplittingColumn(vvs &table)
{
	int column, iii;
	double minEntropy = DBL_MAX;
	int splittingColumn = 0;
	vi entropies;
	for (column = 0; column < table[0].size() - 1; column++) {
		string colName = table[0][column];
		msi tempMap;
		vi counts = countDistinct(table, column);
		vd attributeEntropy;
		double columnEntropy = 0.0;
		for (iii = 1; iii < table.size()-1; iii++) {
			double entropy = 0.0;
			if (tempMap.find(table[iii][column]) != tempMap.end()) { 	// IF ATTRIBUTE IS ALREADY FOUND IN A COLUMN, UPDATE IT'S FREQUENCY
				tempMap[table[iii][column]]++;
			} else { 							// IF ATTRIBUTE IS FOUND FOR THE FIRST TIME IN A COLUMN, THEN PROCESS IT AND CALCULATE IT'S ENTROPY
				tempMap[table[iii][column]] = 1;
				vvs tempTable = pruneTable(table, colName, table[iii][column]);
				vi classCounts = countDistinct(tempTable, tempTable[0].size()-1);
				int jjj, kkk;
				for (jjj = 0; jjj < classCounts.size(); jjj++) {
					double temp = (double) classCounts[jjj];
					entropy -= (temp/classCounts[classCounts.size()-1])*(log(temp/classCounts[classCounts.size()-1]) / log(2));
				}
				attributeEntropy.push_back(entropy);
				entropy = 0.0;
			}
		}
		for (iii = 0; iii < counts.size() - 1; iii++) {
			columnEntropy += ((double) counts[iii] * (double) attributeEntropy[iii]);
		}
		columnEntropy = columnEntropy / ((double) counts[counts.size() - 1]);
		if (columnEntropy <= minEntropy) {
			minEntropy = columnEntropy;
			splittingColumn = column;
		}
	}
	return table[0][splittingColumn];
}

/*
 * Returns an integer which is the
 * index of a column passed as a string
 */
int returnColumnIndex(string &columnName, vvs &tableInfo)
{
	int iii;
	for (iii = 0; iii < tableInfo.size(); iii++) {
		if (tableInfo[iii][0] == columnName) {
			return iii;
		}
	}
	return -1;
}

/*
 * Returns true if the table is empty
 * returns false otherwise
 */
bool tableIsEmpty(vvs &table)
{
	return (table.size() == 1);
}

/*
 * Recursively prints the decision tree
 * For debugging purposes only
 */
void printDecisionTree(node* nodePtr)
{
	if(nodePtr == NULL) {
		return;
	}
	if (!nodePtr->children.empty()) {
		cout << " Value: " << nodePtr->label << endl;
		cout << "Split on: " << nodePtr->splitOn;
		int iii;
		for (iii = 0; iii < nodePtr->children.size(); iii++) {   
			cout << "\t";
			printDecisionTree(nodePtr->children[iii]);
		}
		return;
        } else {
		cout << "Predicted class = " << nodePtr->label;
		return;
	}
}

/*
 * Takes a row and traverses that row through
 * the decision tree to find out the 
 * predicted class label. If none is found
 * returns the default class label which is
 * the class label with the highest frequency.
 */
string testDataOnDecisionTree(vs &singleLine, node* nodePtr, vvs &tableInfo, string defaultClass)
{
	string prediction;
	while (!nodePtr->isLeaf && !nodePtr->children.empty()) {
		int index = returnColumnIndex(nodePtr->splitOn, tableInfo);
		string value = singleLine[index];
		int childIndex = returnIndexOfVector(nodePtr->childrenValues, value);
		nodePtr = nodePtr->children[childIndex];
		if (nodePtr == NULL) {
			prediction = defaultClass;
			break;
		}
		prediction = nodePtr->label;
	}
	return prediction;
}

/*
 * Returns an integer which is the index
 * of a string in a vector of strings
 */
int returnIndexOfVector(vs &stringVector, string value)
{
	int iii;
	for (iii = 0; iii < stringVector.size(); iii++) {
		if (stringVector[iii] == value)	{
			return iii;
		}
	}
	return -1;
}

/*
 * Outputs the predictions to file
 * and returns the accuracy of the classification
 */
double printPredictionsAndCalculateAccuracy(vs &givenData, vs &predictions)
{
	ofstream outputFile;
	outputFile.open("decisionTreeOutput.txt");
	int correct = 0;
	outputFile << setw(3) << "#" << setw(16) << "Given Class" << setw(31) << right << "Predicted Class" << endl;
	outputFile << "--------------------------------------------------" << endl;
	for (int iii = 0; iii < givenData.size(); iii++) {
		outputFile << setw(3) << iii+1 << setw(16) << givenData[iii];
		if (givenData[iii] == predictions[iii]) {
			correct++;
			outputFile << "  ------------  ";
		} else {
			outputFile << "  xxxxxxxxxxxx  ";
		}
		outputFile << predictions[iii] << endl;
	}
	outputFile << "--------------------------------------------------" << endl;
	outputFile << "Total number of instances in test data = " << givenData.size() << endl;
	outputFile << "Number of correctly predicted instances = " << correct << endl;
	outputFile.close();
	return (double) correct/50 * 100;
}

/*
 * Returns a vvs which contains information about
 * the data table. The vvs contains the names of
 * all the columns and the values that each
 * column can take
 */
vvs generateTableInfo(vvs &dataTable)
{
	vvs tableInfo;
	for (int iii = 0; iii < dataTable[0].size(); iii++) {
		vs tempInfo;
		msi tempMap;
		for (int jjj = 0; jjj < dataTable.size(); jjj++) {
			if (tempMap.count(dataTable[jjj][iii]) == 0) {
				tempMap[dataTable[jjj][iii]] = 1;
				tempInfo.push_back(dataTable[jjj][iii]);
			} else	{
				tempMap[dataTable[jjj][iii]]++;
			}
		}
		tableInfo.push_back(tempInfo);
	}
	return tableInfo;
}

/*
 * Returns the most frequent class from the training data
 * This class will be used as the default class label
 */
string returnMostFrequentClass(vvs &dataTable)
{
	msi trainingClasses;           													 // Stores the classlabels and their frequency
	for (int iii = 1; iii < dataTable.size(); iii++) {
		if (trainingClasses.count(dataTable[iii][dataTable[0].size()-1]) == 0) {
			trainingClasses[dataTable[iii][dataTable[0].size()-1]] = 1;
		} else {
			trainingClasses[dataTable[iii][dataTable[0].size()-1]]++;
		}
	}   
	msi::iterator mapIter;
	int highestClassCount = 0;
	string mostFrequentClass;
	for (mapIter = trainingClasses.begin(); mapIter != trainingClasses.end(); mapIter++) {
		if (mapIter->second >= highestClassCount) {
			highestClassCount = mapIter->second;
			mostFrequentClass = mapIter->first;
		}   
	}
	return mostFrequentClass;
}

int main(int argc, const char *argv[])
{
	ifstream inputFile;												// Input file stream
	string singleInstance;											// Single line read from the input file 
	vvs dataTable;													// Input data in the form of a vector of vector of strings

	inputFile.open("train.dat");
	if (!inputFile)													// If input file does not exist, print error and exit
	{
		cerr << "Error: Training data file not found!" << endl;
		exit(-1);
	}

	/* 
	 * Decision tree training phase
	 * In this phase, the training data is read
	 * from the file and stored into a vvs using
	 * the parse() function. The generateTableInfo()
	 * function extracts the attribute (column) names
	 * and also the values that each column can take.
	 * This information is also stored in a vvs.
	 * buildDecisionTree() function recursively
	 * builds trains the decision tree.
	 */
	while (getline(inputFile, singleInstance))						// Read from file, parse and store data
	{
		parse(singleInstance, dataTable);
	}
	inputFile.close(); 												// Close input file
	vvs tableInfo = generateTableInfo(dataTable);					// Stores all the attributes and their values in a vector of vector of strings named tableInfo
	node* root = new node;											// Declare and assign memory for the root node of the Decision Tree
	root = buildDecisionTree(dataTable, root, tableInfo);			// Recursively build and train decision tree
	string defaultClass = returnMostFrequentClass(dataTable);		// Stores the most frequent class in the training data. This is used as the default class label
	dataTable.clear(); 												// clear dataTable of training data to store testing data


	/*
	 * Decision tree testing phase
	 * In this phase, the testing is read
	 * from the file, parsed and stored.
	 * Each row in the table is made to
	 * traverse down the decision tree
	 * till a class label is found.
	 */
	inputFile.clear();
	inputFile.open("test.dat"); 										// Open test file
	if (!inputFile) 												// Exit if test file is not found
	{
		cerr << "Error: Testing data file not found!" << endl;
		exit(-1);
	}
	while (getline(inputFile, singleInstance)) 						// Store test data in a table
	{
		parse(singleInstance, dataTable);
	}
	vs predictedClassLabels;										// Stores the predicted class labels for each row
	vs givenClassLabels;											// Stores the given class labels in the test data
	for (int iii = 1; iii < dataTable.size(); iii++)				// Store given class labels in vector of strings named givenClassLabels
	{
		string data = dataTable[iii][dataTable[0].size()-1];
		givenClassLabels.push_back(data);
	}
	for (int iii = 1; iii < dataTable.size(); iii++)				// Predict class labels based on the decision tree
	{
		string someString = testDataOnDecisionTree(dataTable[iii], root, tableInfo, defaultClass);
		predictedClassLabels.push_back(someString);
	}
	dataTable.clear();

	/* Print output */
	ofstream outputFile;
	outputFile.open("decisionTreeOutput.txt", ios::app);
	outputFile << endl << "--------------------------------------------------" << endl;
	double accuracy = printPredictionsAndCalculateAccuracy(givenClassLabels, predictedClassLabels);			// calculate accuracy of classification
	outputFile << "Accuracy of decision tree classifier = " << accuracy << "%"; 							// Print out accuracy to console
	return 0;
}