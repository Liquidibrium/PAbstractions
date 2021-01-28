#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
#include "vector.h"
#include "queue.h"
#include <time.h>
#include "Browser.h"

using namespace std;

void printTestResults(bool passed, int testNum, int & passedCounter) {
	if (passed) {
		cout << "test " << testNum << " passed" << endl;
		passedCounter++;
	} else {
		cout << "test " << testNum << " failed" << endl;
	}
}

bool runBrowserTest(int testNum) {
	Browser b;
	bool passed = true;
	int num = 10000;
	switch (testNum) {
		case 0:
			if (b.Size() != 0) return false;
			b.NewTab();
			b.NewTab();
			b.NewTab();
			return b.Size() == 3;
		case 1:
			b.NewTab();
			b.NewTab();
			b.NewTab();
			b.NewTab();
			b.NewTab();
			if (b.Size() != 5) return false;
			b.CloseTab(3);
			b.CloseTab(2);
			if (b.Size() != 3) return false;
			b.CloseTab(0);
			return b.Size() == 2;
		case 2:
			b.NewTab();
			b.NewTab();
			if (b.GetUrl(0) != "" || b.GetUrl(1) != "") return false;
			b.GoToPage(1, "url1");
			return b.Size() == 2 && b.GetUrl(1) == "url1" && b.GetUrl(0) == "";
		case 3:
			b.NewTab();
			b.NewTab();
			b.GoToPage(0, "urla");
			b.GoToPage(1, "urlb");
			b.GoToPage(1, "urlb_1");
			b.GoToPage(1, "urlb_2");
			b.CloseTab(0);
			return b.Size() == 1 && b.GetUrl(0) == "urlb_2";
		case 4:
			b.NewTab();
			b.NewTab();
			b.GoToPage(0, "urla");
			b.GoToPage(1, "urlb");
			b.GoToPage(1, "urlb_1");
			b.GoToPage(1, "urlb_2");
			b.GoBack(0);
			b.GoBack(1);
			return b.Size() == 2 && b.GetUrl(0) == "" && b.GetUrl(1) == "urlb_1";
		case 5:
			b.NewTab();
			b.GoToPage(0, "urla");
			b.NewTab();
			b.GoToPage(1, "urlb");
			b.GoToPage(1, "urlb_1");
			b.GoToPage(1, "urlb_2");
			b.GoBack(0);
			if (b.GetUrl(0) != "") return false;
			b.GoBack(0);
			b.GoBack(1);
			b.GoBack(1);
			return b.Size() == 2 && b.GetUrl(0) == "" && b.GetUrl(1) == "urlb";
		case 6:
			b.NewTab();
			b.GoToPage(0, "urla");
			b.GoToPage(0, "urla_1");
			b.NewTab();
			b.GoToPage(1, "urlb");
			b.GoToPage(1, "urlb_1");
			b.GoToPage(1, "urlb_2");
			b.GoBack(0);
			if (b.GetUrl(0) != "urla") return false;
			b.GoForward(0);
			b.CloseTab(1);
			return b.Size() == 1 && b.GetUrl(0) == "urla_1";
		case 7:
			b.NewTab();
			b.GoToPage(0, "urla");
			b.GoToPage(0, "urla_1");
			b.CloseTab(0);
			b.NewTab();
			b.GoToPage(0, "urlb");
			b.GoToPage(0, "urlb_1");
			b.GoToPage(0, "urlb_2");
			b.GoBack(0);
			b.GoBack(0);
			if (b.GetUrl(0) != "urlb") return false;
			b.GoForward(0);
			if (b.GetUrl(0) != "urlb_1") return false;
			b.GoForward(0);
			if (b.GetUrl(0) != "urlb_2") return false;
			b.GoForward(0);
			return b.Size() == 1 && b.GetUrl(0) == "urlb_2";
		case 8:
			b.NewTab();
			b.GoToPage(0, "urla");
			b.GoToPage(0, "urla_1");
			b.GoBack(0);
			if (b.GetUrl(0) != "urla") return false;
			b.GoToPage(0, "urla_2");
			b.GoToPage(0, "urla_3");
			if (b.GetUrl(0) != "urla_3") return false;
			b.GoBack(0);
			if (b.GetUrl(0) != "urla_2") return false;
			b.GoBack(0);
			if (b.GetUrl(0) != "urla") return false;
			b.GoBack(0);
			return b.Size() == 1 && b.GetUrl(0) == "";
		case 9:
			b.NewTab();
			b.GoToPage(0, "urla");
			b.GoToPage(0, "urla_1");
			b.GoBack(0);
			b.GoToPage(0, "urla_2");
			b.GoToPage(0, "urla_3");
			if (b.GetUrl(0) != "urla_3") return false;
			b.GoForward(0);
			if (b.GetUrl(0) != "urla_3") return false;
			b.GoBack(0);
			b.GoBack(0);
			if (b.GetUrl(0) != "urla") return false;
			b.GoForward(0);
			return b.Size() == 1 && b.GetUrl(0) == "urla_2";
		case 10:
			for (int i=0; i<num; i++) {
				b.NewTab();
				b.GoToPage(i, string("url_") + integerToString(i));
			}
			b.CloseTab(0);
			b.CloseTab(0);
			return b.Size() == num-2 && b.GetUrl(0) == "url_2" && b.GetUrl(num-3) == "url_" + integerToString(num-1);
		case 11:
			b.NewTab();
			for (int i=0; i<num; i++) {
				b.GoToPage(0, string("url_") + integerToString(i));
			}
			return b.Size() == 1 && b.GetUrl(0) == "url_" + integerToString(num-1);
		case 12:
			b.NewTab();
			for (int i=0; i<num; i++) {
				b.GoToPage(0, string("url_") + integerToString(i));
			}
			for (int i=1; i<=num; i++) {
				if (b.GetUrl(0) != string("url_") + integerToString(num-i)) return false;
				b.GoBack(0);
			}
			return b.Size() == 1 && b.GetUrl(0) == "";
		case 13:
			b.NewTab();
			for (int i=0; i<num; i++) {
				b.GoToPage(0, string("url_") + integerToString(i));
			}
			for (int i=0; i<num; i++) {
				b.GoBack(0);
			}
			for (int i=0; i<num; i++) {
				b.GoForward(0);
				if (b.GetUrl(0) != string("url_") + integerToString(i)) return false;
			}
			return b.Size() == 1;
	}
	return false;
}

const int browserTestsNum = 14;

void runBrowserTests() {
	cout << "### Run Browser tests ###" << endl;
	int passedNum = 0;
	int testNum = 0;

	for (; testNum<browserTestsNum; testNum++) {
		bool res = runBrowserTest(testNum);
		printTestResults(res, testNum, passedNum);
	}

	cout << "###### passed " << passedNum << " tests ######" << endl;
}

int main() {
	runBrowserTests();

	return 0;
}