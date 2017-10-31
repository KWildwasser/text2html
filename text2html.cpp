#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main (int argc, char* argv[]) {
  string line;
  /*status*/
  bool in_list = false;
  /*open files*/
  ifstream infile (argv[1]);
  ofstream outfile (argv[2]);
  if (infile.is_open() && outfile.is_open())
  {
	  /*write html head*/
	  outfile << "<!DOCTYPE html>" << '\n' 
		  << "<html lang=\"de\">" << '\n'
		  << "<meta charset=UTF-8>" << '\n' 
		  << "<body>" << '\n';
    /*process infile line by line*/
    while ( getline (infile,line) )
    {
	/*ignore empty lines*/
	if(line.length() == 0) {
		outfile << '\n';	
		continue;
	}
	/*process lists started with a '-'*/
	if (line.at(0) ==  '-') {
		line.erase(0,1);
		if(!in_list) outfile << "<ul>" << '\n';
		in_list = true;
		outfile << "<li>" << line << "</li>" << '\n';
		continue;
	} else {
		if(in_list) {outfile << "</ul>" << '\n';}
		in_list = false;
		
	}
	/*process headings started with a digit*/
	if (isdigit(line.at(0))) {
		if(isdigit(line.at(2))) {
			outfile << "<h2>" << line << "</h2>" << '\n';
		} else if (line.at(2) ==  ' ') {
			outfile << "<h1>" << line << "</h1>" << '\n';
		}
		continue;
	}
	/*default: process textlines as paragraph*/
	outfile << "<p>" << line << "</p>" << '\n';
    }
    /*close html and open lists*/
    if(in_list) {outfile << "</ul>" << '\n';}
    outfile <<  "</body>" << '\n' << "</html>";
    /*close files*/
    infile.close();
    outfile.close();
  }

  else cout << "Unable to open file" << '\n'; 

  return 0;
}
