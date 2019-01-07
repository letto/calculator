/**** 
***********************************************************************************
*   BSD 3-Clause License
*   
*   Copyright (c) 2019, Marius
*   All rights reserved.
*
*   Redistribution and use in source and binary forms, with or without
*   modification, are permitted provided that the following conditions are met:
*
*   * Redistributions of source code must retain the above copyright notice, this
*     list of conditions and the following disclaimer.
*
*   * Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*
*   * Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived from
*     this software without specific prior written permission.
*
*   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
*   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
*   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
*   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
*   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************
****/

// Command-line calculator project for expressions in Polish Notation

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <sstream>

#include <cmath>

using std::cout;
using std::endl;
using std::cin;

using std::string;
using std::strtod;
using std::vector;
using std::istream_iterator;
using std::ostream_iterator;


int main(int argc,char* argv[]) {
    
    while(true) {
	string operation;
	vector<string> words;
    
        cout << "Enter operation: " << endl;
	std::getline( cin, operation);
	if( tolower(operation[0]) == 'x' || tolower(operation[0]) == 'q') {
	    exit(EXIT_SUCCESS);
	}


	// remove trailing white space
	while( !operation.empty() && std::isspace( operation.back())) {
	    operation.pop_back();
	}

	bool valid = true;
	std::istringstream iss( operation);
	char op;
	{
	    iss >> operation;
	    
            if( operation.length() > 2) {
		    cout << "Unrecognized operation: " << operation << endl;
		    valid = false;
            }

	    switch( operation[0]) {
		case '*':
		    if( operation[1] == '*') {
			op = 'p';
		    }
		break;
	    case '>':
		if( operation[1] == '>') {
		    op = 'r';
		}
		break;
	    case '<':
		if( operation[1] == '<') {
		    op = 'l';
		}
		break;
		default:
		    op = operation[0];
	    } 
	    // cout << "Operation is: " << operation << endl << "Op is: " << op << endl;
	}

	vector<double> elements;
	while( iss) {
	    string out;
	    iss >> out;
	    if( out.find_first_not_of(".-+0123456789") != string::npos) {
		cout << "Element " << out << " is not a number." << endl;
		valid = false;
	    }
	    if(iss) {
		elements.push_back( strtod(out.c_str(), nullptr));
		/* cout << "Element " << strtod(out.c_str(), nullptr) 
		     << " added to the elements vector" << endl; */
	    }
	}

	// Display the elements vector.
	// cout << "Vector contains the elements: " << endl;
	// std::copy( elements.begin(), elements.end(), std::ostream_iterator<double>(cout, " "));
	// cout << endl;

	double res;
        switch (op) {
	    case 'x':
	    case 'X':
	    case 'q':
	    case 'Q':
	    case '\0':
		exit(EXIT_SUCCESS);
		break;
	    case '+':
		res = 0;
		for( auto& n: elements) {
		    res += n;
		}
	        break;
	    case '-': {
		res = elements[0];
		for( int i = 1; i < elements.size(); ++i) {
		    res -= elements[i];
		}
	    }
		break;
	    case '*':
		res = 1;
		for( auto& n: elements) {
		    res *= n;
		}
		break;
	    case '/':
		res = elements[0];
		for( int i = 1; i < elements.size(); ++i) {
		    if( elements[i] != 0) {
			    res /= elements[i];
		    } else {
			cout << "Error: Division by 0." << endl;
			valid = false;
			continue;
		    }
		}
		break;
	    case 'p':
		res = elements[0];
		for( int i = 1; i < elements.size(); ++i) {
		    res = pow( res, elements[i]);
		}
		break;
	    case '%': {
                long x = elements[0];
                for( int i = 1; i < elements.size(); ++i) {
                    x %= static_cast<long>( elements[i]);
                }
		res = x;
	    }
		break;
	    case '^':{
		long x = elements[0];
                for( int i = 1; i < elements.size(); ++i) {
		    x ^= static_cast<long>( elements[i]);
                }
		res = x;
	    }
		break;
	    case '|': {
		long x = elements[0];
		for( int i = 1; i < elements.size(); ++i) {
		    x |= static_cast<long>( elements[i]);
		}
		res = x;
	    }
		break;
	    case '&': {
		long x = elements[0];
		for( int i = 1; i < elements.size(); ++i) {
		    x &= static_cast<long>( elements[i]);
		}
		res = x;
	    }
		break;
	    case 'l': {
		long x = elements[0];
		for( int i = 1; i < elements.size(); ++i) {
		    x <<= static_cast<long>( elements[i]);
		}
		res = x;
	    }
		break;
	    case 'r': {
		long x = elements[0];
		for( int i = 1; i < elements.size(); ++i) {
		    x >>= static_cast<long>( elements[i]);
		}
		res = x;
	    }
		break;
	    default:
		cout << "Unrecognized operation: " << operation << endl;
		exit(2);
	}
	if( valid) {
	    cout << "Result: " << res << endl;
	}
    } 
    return EXIT_SUCCESS;
}

