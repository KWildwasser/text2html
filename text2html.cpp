#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main (int argc, char* argv[]) {
  string line;
  char arbiter;
  bool in_list = false;
  ifstream infile (argv[1]);
  ofstream outfile (argv[2]);
  if (infile.is_open() && outfile.is_open())
  {
	  outfile << "<!DOCTYPE html>" << '\n' 
		  << "<html lang=\"de\">" << '\n'
		  << "<meta charset=UTF-8>" << '\n' 
		  << "<body>" << '\n';
    while ( getline (infile,line) )
    {
	if(line.length() == 0) {
		outfile << '\n';	
		continue;
	}
	arbiter = line.at(0);
	if (arbiter ==  '-') {
		line.erase(0,1);
		if(!in_list) outfile << "<ul>" << '\n';

		in_list = true;
		outfile << "<li>" << line << "</li>" << '\n';
	} else if (isdigit(arbiter)) {
		if(in_list) outfile << "</ul>" << '\n';
		in_list = false;
		if(isdigit(line.at(2))) {
			outfile << "<h2>" << line << "</h2>" << '\n';
		} else if (line.at(2) ==  ' ') {
			outfile << "<h1>" << line << "</h1>" << '\n';
		}

	} else {
		if(in_list) outfile << "</ul>" << '\n';
		in_list = false;
		outfile << "<p>" << line << "</p>" << '\n';

	}
      	    
    }
    outfile <<  "</body>" << '\n' << "</html>" << '\n';
    infile.close();
    outfile.close();
  }

  else cout << "Unable to open file" << '\n'; 

  return 0;
}
