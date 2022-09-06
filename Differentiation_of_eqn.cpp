//Differentiation Code
//Some conventions:
//Code is very bracket sensetive
//All powers should be in brackets, ie, x^(2), a^(3x), e^(4x),etc
//All powers are in integers
//log needs to be represented by ln , ie, ln(x)
//For trignometry all x and coefficient of x should be inside brackets, ie, sin(x) , cos(3x) ,etc
//cosec is repreented by csc 
//All hypergeometric values are represented as sinh(x) , cosh(x) ,etc.
//cosech is represented by csch
//All inverse trigonometric functions have suffix arc, ie, arcsin(x) , arccos(x) , arccsc(5x) , etc

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int exponent(int x, int n) //finds exponent
{
	int res = 1;
	for(int i=0 ; i<n ; i++)
	{
		res *= x;
	}
	return res;
} 

bool is_alph(char c) //Checks if char is alph or not
{
	if(int(c) < 123 && int(c) > 96)
		return true;
	return false;
}

int is_num(char c) //Returns -1 if not a number else returns the num (0-9)
{
	if(int(c) < 58 && int(c) > 47)
		return int(c) - 48 ;
	return -1;
}

string remove_coeff(string s1) //Only returns the variable substring
{
	for(int i=0 ; i<s1.length() ; i++)
	{
		if(is_num(s1[i]) != -1 && s1[i+1] == '^')
			return s1;
	}

	string var1;
	int k =0 ;
	for(int i=0 ; i<s1.length() ; i++)
	{
		if(int(s1[i]) < 123 && int(s1[i]) > 96) //Identifies alphabets
		{
			k = i;
			break;
		}
	}
	var1 = s1.substr(k,s1.length()-k);
	return var1;
}

string get_coeff(string s1) //Only returns the numerical part
{
	if(s1 == "")
	{
		return "";
	}
	for(int i=0 ; i<s1.length() ; i++)
	{
		if(is_num(s1[i]) != -1 && s1[i+1] == '^')
			return "";
	}
	string var1;
	int k =0 ;
	for(int i=0 ; i<s1.length() ; i++)
	{
		if(int(s1[i]) < 123 && int(s1[i]) > 96) //Identifies alphabets
		{
			k = i;
			break;
		}
	}
	if(k == 1 && s1[0] == '-')  //Cases like -abc
	{
		return "-1";
	}
	if(k==0) //Case like abc
	{
		return "1";
	}
	var1 = s1.substr(0,k);
	return var1;
}
string int_to_string(int num)  //Converts int into string 
{
	if(num == 0)
	{
		return  "0";
	}
	if(num == 1)
	{
		return "";
	}
	if(num == -1)
	{
		return "-";
	}
	string s;
	string n;
	if(num < 0) //Fior the neg sign
	{
		num *= -1;
		s.push_back('-') ;
	}
	while(num > 0)  //Storing the reverse number in n
	{
		n.push_back('0' + num%10);
		num /= 10;
	}

	for(int i=0 ; i<n.length() ; i++) //Storing the number in original order in s
	{
		s.push_back(n[n.length()-i-1]) ;
	}
	return s;
}

string int_to_string2(int num)  //Converts int into string 
{
	if(num == 0)
	{
		return  "0";
	}
	if(num == 1)
	{
		return "1";
	}
	string s;
	string n;
	if(num < 0) //Fior the neg sign
	{
		num *= -1;
		s.push_back('-') ;
	}
	while(num > 0)  //Storing the reverse number in n
	{
		n.push_back('0' + num%10);
		num /= 10;
	}

	for(int i=0 ; i<n.length() ; i++) //Storing the number in original order in s
	{
		s.push_back(n[n.length()-i-1]) ;
	}
	return s;
}

int string_to_int(string s, int k) //Mostly used while finding powers when in bracket
{
	int num = 0 ;
	while(s[k] != ')')
	{
		num = num*10 + (int(s[k]) - 48); //-48 since ASCII 0 is 48
		k++;
	}
	return num;
}

int string_to_int(string s) //Normally converting string numbers to int
{
	if(s == "")
	{
		return 1;
	}
	int num = 0 ;
	int i = 0;
	if(s[0] == '-')
	{
		i = 1;
	}
	while(i < s.length())
	{
		num = num*10 + (int(s[i]) - 48); //-48 since ASCII 0 is 48
		i++;
	}
	if(s[0] == '-')
	{
		num *= -1;
	}
	return num;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int is_power(string s) //Takes a string and returns 
					   //0: if s == x , 1: if s == some char that is not x, 3: a char with power, -1:if it is not a power
{
	s = remove_coeff(s);
	if(s.length() == 1) //Check if the string is just a char and if it it,thrn
	{
		if(s[0] == 'x') //if it is x then return 1
			return 1; // 1 to signify that it is just x plus its answer will be the same as diff
		else
			return 0; // 0 to signify its a char that is not x plus 0 will be the ans of the diff
	}

	int count=0 ;
	for(int i=0; i<s.length()-1 ; i++)
	{
		if(is_alph(s[i]) == true && s[i] == 'x')
			count++;
		if(is_alph(s[i]) == true && s[i+1] == '^' && count <= 1 && s[i] == 'x')
			return 3; // 3 to signify its a power 
	}

	return -1;
}

string diff_power(string s, int type) // Input : original string and type of power it is
									  // type = 0 , string is a constant return 0
									  // type = 1 , string is x return 1
									  // type = 3 , string is x^(n) return nx^(n-1) 
{
	string coeff = get_coeff(s);
	if(type == 0) //It means s = some char c
		return "0";
	else if(type == 1) //It means s = x
	{
		if(coeff == "")
			return "1";
		else
			return coeff ;
	}

	string power, diff;
	
	int i;
	for(i=0 ; i<s.length() ; i++) //Find the position of '^'
	{
		if(s[i] == '^')
			break;
	}

	power = s.substr(i+2,s.length()-i-3); //Finds the power of s

	if(coeff == "")
	{
		diff = power +  "x^(" + int_to_string(string_to_int(power)-1) + ")"; // n + x + ^ + n-1
	}
	else
	{
		if(power == "1") //If n-1 == 0 so no point in keeping the x
			diff = int_to_string(string_to_int(power) * string_to_int(coeff))  ;

		else if(power == "2")
			diff = int_to_string(string_to_int(power) * string_to_int(coeff)) +  "x" ;
			
		else  // n -1 !=0 
			diff = int_to_string(string_to_int(power) * string_to_int(coeff)) +  "x^(" + int_to_string(string_to_int(power)-1) + ")"; // n + x + ^ + n-1
	}
	return diff;
}

int is_exponential(string s) //Takes a string and returns 
							 //4: if it is of the form e^(some function of x) , 5: if it is of the form k^(some function of x) where k is any char except e
{
	for(int i=0 ; i<s.length() ; i++)
	{
		if(is_num(s[i]) != -1 && s[i+1] == '^')
			return 5;
	}
	s = remove_coeff(s) ;
	if(s[0] == 'e' && s[1] == '^') // e^(some expression of x)
	{
		for(int i=2; i<s.length() ; i++)
		{
			if(s[i] == 'x')
				return 4; //4 to signify that its a power of e
		}
	}
	else if(is_alph(s[0]) && s[1] == '^' && s[0] != 'e')
	{
		for(int i=2; i<s.length() ; i++)
		{
			if(s[i] == 'x')
				return 5; //5 to signify that its a power of a random char
		}
	}

	return -1;
}

string diff_exponential(string s, int type) // Input : original string and type of exponent it is
											// type = 4 , string is of form e^x and returns d(e^(nx)/dx) = ne^(nx)
											// type = 5 , string is of form a^x and returns d(a^(nx))/dx = na^(nx)lna
{
	if(type == 5)
	{
		bool is_num_pow_x = false;
		for(int i=0 ; i<s.length() ; i++)
		{
			if(is_num(s[i]) != -1 && s[i+1] == '^')
			{
				is_num_pow_x = true;
				break;
			}
		}
		if(is_num_pow_x == true)
		{
			int number = 0;
			int k=0;
			while(s[k] != '^' )
			{
				number = number*10 + (int(s[k]) - 48);
				k++;
			}
			//Getting the coefficient of x
			int start=0,end=0 ; //Variables to keep track of the start and end of the coefficient of x
			for(int i=0 ; i<s.length()-1 ; i++)
			{
				if(s[i] == '^' && s[i+1] == '(' && start == 0)
				{
					start = i+2;
					i+=2;
				}
				if(start != 0 && s[i] == 'x')
				{
					end = i;
					break;
				}
			}
			string xcoeff = s.substr(start,end-start);
			if(xcoeff != "")
				return xcoeff + "*" + int_to_string(number) + "^(" + xcoeff + "x)ln(" + int_to_string(number) + ")" ;
			if(xcoeff == "")
				return  int_to_string(number) + "^(x)ln(" + int_to_string(number) + ")" ;
		}
	}
	string coeff = get_coeff(s);
	s = remove_coeff(s);
	string diff = "";
	//Getting the coefficient of x
	int start=0,end=0 ; //Variables to keep track of the start and end of the coefficient of x
	for(int i=0 ; i<s.length()-1 ; i++)
	{
		if(s[i] == '^' && s[i+1] == '(' && start == 0)
		{
			start = i+2;
			i+=2;
		}
		if(start != 0 && s[i] == 'x')
		{
			end = i;
			break;
		}
	}
	string xcoeff = s.substr(start,end-start);

	if(type == 4)
	{
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "e^(" + xcoeff + "x)";  // d(e^(nx)/dx) = ne^(nx)
	}
	else if(type == 5)
	{
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + s[0] +"^(" + xcoeff + "x)ln(" + s[0] + ")" ; // d(a^(nx))/dx = na^(nx)lna
	}
	return diff ;
}

int is_log(string s)
{
	s = remove_coeff(s) ;
	if(s[0] == 'l' && s[1] == 'n')
	{
		for(int i=2 ; i<s.length() ; i++)
		{
			if(s[i] == 'x')
				return 6;
		}
	}

	return -1;
}

string diff_log(string s) //Takes in string and returns a.d(ln(nx))/dx = a.n/nx = a/x
{
	string coeff = get_coeff(s);
	s = remove_coeff(s);
	string diff = "";

	diff = coeff + "/x"; // d(ln(nx))/dx = n/nx = 1/x

	return diff;
}

int is_trig(string s)
{
	string trign[6] = {"sin","cos","tan","csc","sec","cot"};

	s = remove_coeff(s);
	string temp = s.substr(0,3);

	if(s[3] == 'h') //It would be sinh, cosh,...etc so its hyperbolic function
		return -1;

	for(int i=0 ; i<6 ; i++)
	{
		if(temp == trign[i])
			return i+7;
	}

	return -1;
}

string diff_trig(string s, int type) // Input : original string and type of exponent it is
									 // type = 7 , d(sin(nx))/dx = ncos(nx)
									 // type = 8 , d(cos(nx))/dx = -nsin(nx)
									 // type = 9 , d(tan(nx))/dx = nsec^(2)(nx)
									 // type = 10 , d(csc(nx))/dx = -ncsc(nx)cot(nx)
									 // type = 11 , d(sec(nx))/dx = nsec(nx)tan(nx)
									 // type = 12 , d(cot(nx))/dx = -ncsc^(2)(nx)
{
	string coeff = get_coeff(s);
	s = remove_coeff(s);
	string diff = "";
	//Getting the coefficient of x
	int start=0,end=0 ; //Variables to keep track of the start and end of the coefficient of x
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == '(' && start == 0)
		{
			start = i+1;
			i+=1;
		}
		if(start != 0 && s[i] == 'x')
		{
			end = i;
			break;
		}
	}
	string xcoeff = s.substr(start,end-start);
	
	if(type == 7)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "cos(" + xcoeff + "x)" ; // d(sin(nx))/dx = ncos(nx)
	else if(type == 8)
		diff = int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "sin(" + xcoeff + "x)" ; // d(cos(nx))/dx = -nsin(nx)
	else if(type == 9)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "sec^(2)(" + xcoeff + "x)" ; // d(tan(nx))/dx = nsec^(2)(nx)
	else if(type == 10)
		diff = int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "csc(" + xcoeff + "x)" + "cot(" + xcoeff + "x)" ; // d(csc(nx))/dx = -ncsc(nx)cot(nx)
	else if(type == 11)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "sec(" + xcoeff + "x)" + "tan(" + xcoeff + "x)" ; // d(sec(nx))/dx = nsec(nx)tan(nx)
	else if(type == 12)
		diff = int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "csc^(2)(" + xcoeff + "x)" ; // d(cot(nx))/dx = -ncsc^(2)(nx)

	return diff;
}

int is_hyperbolic(string s)
{
	string trign[6] = {"sinh","cosh","tanh","csch","sech","coth"};

	s = remove_coeff(s);
	string temp = s.substr(0,4);
	for(int i=0 ; i<6 ; i++)
	{
		if(temp == trign[i])
			return i+13;
	}

	return -1;
}

string diff_hyperbolic(string s, int type) // Input : original string and type of exponent it is
									 // type = 13 , d(sinh(nx))/dx = ncosh(nx)
									 // type = 14 , d(cosh(nx))/dx = -nsinh(nx)
									 // type = 15 , d(tanh(nx))/dx = n - ntanh^(2)(nx)
									 // type = 16 , d(csch(nx))/dx = -ncsch(nx)coth(nx)
									 // type = 17 , d(sec(nx))/dx = -nsech(nx)tanh(nx)
									 // type = 18 , d(coth(nx))/dx = n - ncoth^(2)(nx)
{
	string coeff = get_coeff(s);
	s = remove_coeff(s);
	string diff = "";
	//Getting the coefficient of x
	int start=0,end=0 ; //Variables to keep track of the start and end of the coefficient of x
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == '(' && start == 0)
		{
			start = i+1;
			i+=1;
		}
		if(start != 0 && s[i] == 'x')
		{
			end = i;
			break;
		}
	}
	string xcoeff = s.substr(start,end-start);
	
	if(type == 13)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "cosh(" + xcoeff + "x)" ; // d(sinh(nx))/dx = ncosh(nx)
	else if(type == 14)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "sinh(" + xcoeff + "x)" ; // d(cosh(nx))/dx = -nsinh(nx)
	else if(type == 15)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "tanh^(2)(" + xcoeff + "x)" ; // d(tanh(nx))/dx = n - ntanh^(2)(nx)
	else if(type == 16)
		diff = int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "csch(" + xcoeff + "x)" + "coth(" + xcoeff + "x)" ; // d(csch(nx))/dx = -ncsch(nx)coth(nx)
	else if(type == 17)
		diff = int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "sech(" + xcoeff + "x)" + "tanh(" + xcoeff + "x)" ; // d(sec(nx))/dx = -nsech(nx)tanh(nx)
	else if(type == 18)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "coth^(2)(" + xcoeff + "x)" ;  // d(coth(nx))/dx = n - ncoth^(2)(nx)

	return diff;
}

int is_inv_trig(string s)
{
	string trign[6] = {"sin","cos","tan","csc","sec","cot"};

	s = remove_coeff(s);
	string temp = s.substr(0,6);

	for(int i=0 ; i<6 ; i++)
	{
		if(temp == "arc" + trign[i])
			return i+19;
	}

	return -1;
}

string diff_inv_trig(string s, int type) // Input : original string and type of exponent it is
									 // type = 19 , d(arcsin(nx))/dx = n/sqrt(1-n^(2)x^(2))
									 // type = 20 , d(arccos(nx))/dx = -n/sqrt(1-n^(2)x^(2))
									 // type = 21 , d(arctan(nx))/dx = n/(1+n^(2)x^(2))
									 // type = 22 , d(arccsc(nx))/dx = -1/|x|sqrt(1-n^(2)x^(2))
									 // type = 23 , d(arcsec(nx))/dx = 1/|x|sqrt(1-n^(2)x^(2))
									 // type = 24 , d(arccot(nx))/dx = -n/(1+n^(2)x^(2))
{
	string coeff = get_coeff(s);
	s = remove_coeff(s);
	string diff = "";
	//Getting the coefficient of x
	int start=0,end=0 ; //Variables to keep track of the start and end of the coefficient of x
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == '(' && start == 0)
		{
			start = i+1;
			i+=1;
		}
		if(start != 0 && s[i] == 'x')
		{
			end = i;
			break;
		}
	}
	string xcoeff = s.substr(start,end-start);
	
	if(type == 19)
		diff = int_to_string2(string_to_int(coeff)*string_to_int(xcoeff)) + "/sqrt(1-" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + "x^(2))" ; // d(arcsin(nx))/dx = n/sqrt(1-n^(2)x^(2))
	else if(type == 20)
		diff = int_to_string2(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "/sqrt(1-" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + "x^(2))" ; // d(arccos(nx))/dx = -n/sqrt(1-n^(2)x^(2))
	else if(type == 21)
		diff = int_to_string2(string_to_int(coeff)*string_to_int(xcoeff)) + "/(1+" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + "x^(2))" ; // d(arctan(nx))/dx = n/(1+n^(2)x^(2))
	else if(type == 22)
		diff = int_to_string2(-1*string_to_int(coeff)) + "/|x|sqrt(" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + "x^(2)-1)" ; // d(arccsc(nx))/dx = -1/|x|sqrt(1-n^(2)x^(2))
	else if(type == 23)
		diff = coeff + "/|x|sqrt(" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + "x^(2)-1)" ; // d(arcsec(nx))/dx = 1/|x|sqrt(1-n^(2)x^(2))
	else if(type == 24)
		diff = int_to_string2(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "/(1+" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + "x^(2))" ; // d(arccot(nx))/dx = -n/(1+n^(2)x^(2))

	return diff;
}
int check_function(string s)
{
	//First check for power function
	if(is_power(s) == 0 || is_power(s) == 1 ||is_power(s) == 3)
		return is_power(s);

	//Check for exponential
	if(is_exponential(s) == 4 || is_exponential(s) == 5)
		return is_exponential(s);

	//Check for log
	if(is_log(s) == 6)
		return 6;

	//Check for triginometry
	if(is_trig(s) >= 7 && is_trig(s) <= 12)
		return is_trig(s) ;

	//Check for hyperbolic
	if(is_hyperbolic(s) >= 13 && is_hyperbolic(s) <= 18)
		return is_hyperbolic(s) ;

	//Check for inverse trigonometric function
	if(is_inv_trig(s) >= 19 && is_inv_trig(s) <= 24)
		return is_inv_trig(s) ;
}

string differentiation(string s, int cf)
{
	if(cf == 0 || cf == 1 || cf == 3) // cf = 0,1,3 represnt power function
		return diff_power(s,cf);
	else if(cf == 4 || cf == 5)  //cf = 4,5 represent exponential function
		return diff_exponential(s,cf); 
	else if(cf == 6) // cf = 6 reprsent log 
		return diff_log(s);
	else if(cf >= 7 && cf <= 12) // 7 <= cf <= 12 represent triginometry
		return diff_trig(s,cf);
	else if(cf >= 13 && cf <= 18) // 13 <= cf <= 18 represent hyperbolic function
		return diff_hyperbolic(s,cf);
	else if(cf >= 19 && cf <= 24) // 19 <= cf <= 24 represent invere trigonomtric function
		return diff_inv_trig(s,cf);
}

int main()
{
	fstream myfile ;
	myfile.open("input1.txt");
	string exp;
	getline(myfile,exp) ;
	myfile.close() ;
	int count = 0;
	for(int i=0 ; i<exp.length() ; i++)
	{
		if(exp[i] != ' ')  //Basically swaps space with char that is not space
		{
			exp[count++] = exp[i] ;
		}
	}
	exp[count] = '\n'; //Acts as an indicator
	string new_exp ;

	for(int i=0 ; i<exp.length() ; i++) //Adds char to new s till we reach to the indicator
	{
		if(exp[i] == '\n')
		{
			break;
		}
		new_exp.push_back(exp[i]) ;
	}
	// cout << check_function(new_exp) << endl;
	cout << differentiation(new_exp,check_function(new_exp));
}
