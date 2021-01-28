#ifndef Browser_Included
#define Browser_Included

#include "console.h"
using namespace std;

class Browser {
	public: 
		Browser();  // done
		void NewTab(); //done
		void CloseTab(int tabIndex); // done
		int Size(); // done
		void GoToPage(int tabIndex, string url); 
		string GetUrl(int tabIndex);
		void GoBack(int tabIndex);
		void GoForward(int tabIndex);

	private:
		

};

#endif;
