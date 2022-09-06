//Differentiation of expression Code
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

//For addition, subtraction, do not use brackets , ie, (x) - (3sin(x)) <--- X   x - 3sin(x) <--- correct
//For multiplication, do not use brackets , ie, 2x(sin(x)) <--- X    2x*sin(x) <--- correct
//While division , whole numerator and denominator expressions should be in bracket even if one term , ie, sin(x)/cos(x) <---X   (sin(x))/(cos(x)) <--- correct

//Chain rule works only for gof(x) , where f(x) and g(x) are the given functions and not exprressions
//It works for expressions with gof(x), where f(x) and g(x) are the given functions and not exprressions

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
	if(s.length() == 1 && s[0] == '-')
	{
		return -1;
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

int maxArr(int arr[], int n) //Returns max element from Array
{
	int max = arr[0];
	for(int i=1 ; i<n ; i++)
	{
		if(arr[i] > max)
			max = arr[i];
	}
	return max;
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
		if(is_num(s[i]) != 1 && s[i+1] == '^')
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
	else if(is_alph(s[0]) && s[1] == '^')
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

string diff_power(string s,string x ,int type) // Input : original string and type of power it is   //Do not forget to add to original code 
									  // type = 0 , string is a constant return 0
									  // type = 1 , string is x return 1
									  // type = 3 , string is x^(n) return nx^(n-1) 
{
	string coeff = get_coeff(s);
	string xcoeff = get_coeff(x);
	x = remove_coeff(x);
	if(type == 0) //It means s = some char c
		return "0";
	else if(type == 1) //It means s = x
	{
		if(coeff == "")
			return x;
		else
			return int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + x ;
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
		diff = power + x +"^(" + int_to_string(string_to_int(power)-1) + ")"; // n + x + ^ + n-1
	}
	else
	{
		if(power == "1") //If n-1 == 0 so no point in keeping the x
			diff = int_to_string(string_to_int(power) * string_to_int(coeff) * string_to_int(xcoeff))  ;

		else if(power == "2")
			diff = int_to_string(string_to_int(power) * string_to_int(coeff) * string_to_int(xcoeff)) +  x ;
			
		else  // n -1 !=0 
			diff = int_to_string(string_to_int(power) * string_to_int(coeff) * string_to_int(xcoeff)) + x + "^(" + int_to_string(string_to_int(power)-1) + ")"; // n + x + ^ + n-1
	}
	return diff;
}

string diff_exponential(string s, string x ,int type) // Input : original string and type of exponent it is                   //Do not forget to add to original code 
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
			string xcoeff = get_coeff(x);
			if(xcoeff != "")
				return xcoeff + "*" + int_to_string(number) + "^(" + xcoeff + x + ")ln(" + int_to_string(number) + ")" ;
			if(xcoeff == "")
				return  int_to_string(number) + "^("+ x +")ln(" + int_to_string(number) + ")" ;
		}
	}
	string coeff = get_coeff(s);
	s = remove_coeff(s);
	string diff = "";
	
	string xcoeff = get_coeff(x);

	if(type == 4)
	{
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "e^(" +  x +")";  // d(e^(nx)/dx) = ne^(nx)
	}
	else if(type == 5)
	{
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + s[0] +"^(" +  x + ")ln(" + s[0] + ")" ; // d(a^(nx))/dx = na^(nx)lna
	}
	return diff ;
}

string diff_log(string s,string x) //Takes in string and returns a.d(ln(nx))/dx = a.n/nx = a/x                   //Do not forget to add to original code 
{
	string coeff = get_coeff(s);
	s = remove_coeff(s);
	x = remove_coeff(x);
	string diff = "";

	diff = coeff + "/" + x; // d(ln(nx))/dx = n/nx = 1/x

	return diff;
}

string diff_trig(string s,string x ,int type) // Input : original string and type of exponent it is                   //Do not forget to add to original code
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
	string xcoeff = get_coeff(x);
	x = remove_coeff(x);
	
	if(type == 7)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "cos(" + int_to_string(string_to_int(xcoeff)) + x + ")" ; // d(sin(nx))/dx = ncos(nx)
	else if(type == 8)
		diff = int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "sin(" + int_to_string(string_to_int(xcoeff))  + x +  ")" ; // d(cos(nx))/dx = -nsin(nx)
	else if(type == 9)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "sec^(2)(" + int_to_string(string_to_int(xcoeff))  + x +  ")" ; // d(tan(nx))/dx = nsec^(2)(nx)
	else if(type == 10)
		diff = int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "csc(" + int_to_string(string_to_int(xcoeff))  + x +  ")" + "cot(" + int_to_string(string_to_int(xcoeff)) + x + ")" ; // d(csc(nx))/dx = -ncsc(nx)cot(nx)
	else if(type == 11)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "sec(" + int_to_string(string_to_int(xcoeff)) + x + ")" + "tan(" + int_to_string(string_to_int(xcoeff)) + x + ")" ; // d(sec(nx))/dx = nsec(nx)tan(nx)
	else if(type == 12)
		diff = int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "csc^(2)(" + int_to_string(string_to_int(xcoeff)) + x + ")" ; // d(cot(nx))/dx = -ncsc^(2)(nx)

	return diff;
}

string diff_hyperbolic(string s, string x, int type) // Input : original string and type of exponent it is                   //Do not forget to add to original code
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
	string xcoeff = get_coeff(x);
	x = remove_coeff(x) ;
	
	if(type == 13)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "cosh(" + xcoeff + x + ")" ; // d(sinh(nx))/dx = ncosh(nx)
	else if(type == 14)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + "sinh(" + xcoeff + x + ")" ; // d(cosh(nx))/dx = -nsinh(nx)
	else if(type == 15)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "tanh^(2)(" + xcoeff + x + ")" ; // d(tanh(nx))/dx = n - ntanh^(2)(nx)
	else if(type == 16)
		diff = int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "csch(" + xcoeff + x + ")" + "coth(" + xcoeff + x + ")" ; // d(csch(nx))/dx = -ncsch(nx)coth(nx)
	else if(type == 17)
		diff = int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "sech(" + xcoeff + x + ")" + "tanh(" + xcoeff + x + ")" ; // d(sec(nx))/dx = -nsech(nx)tanh(nx)
	else if(type == 18)
		diff = int_to_string(string_to_int(coeff)*string_to_int(xcoeff)) + int_to_string(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "coth^(2)(" + xcoeff + x + ")" ;  // d(coth(nx))/dx = n - ncoth^(2)(nx)

	return diff;
}

string diff_inv_trig(string s, string x ,int type) // Input : original string and type of exponent it is                   //Do not forget to add to original code
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
	string xcoeff = get_coeff(x);
	x = remove_coeff(x) ;
	
	if(type == 19)
		diff = int_to_string2(string_to_int(coeff)*string_to_int(xcoeff)) + "/sqrt(1-" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + x + "^(2))" ; // d(arcsin(nx))/dx = n/sqrt(1-n^(2)x^(2))
	else if(type == 20)
		diff = int_to_string2(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "/sqrt(1-" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + x + "^(2))" ; // d(arccos(nx))/dx = -n/sqrt(1-n^(2)x^(2))
	else if(type == 21)
		diff = int_to_string2(string_to_int(coeff)*string_to_int(xcoeff)) + "/(1+" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + x + "^(2))" ; // d(arctan(nx))/dx = n/(1+n^(2)x^(2))
	else if(type == 22)
		diff = int_to_string2(-1*string_to_int(coeff)) + "/|x|sqrt(" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + x + "^(2)-1)" ; // d(arccsc(nx))/dx = -1/|x|sqrt(1-n^(2)x^(2))
	else if(type == 23)
		diff = coeff + "/|x|sqrt(" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + x + "^(2)-1)" ; // d(arcsec(nx))/dx = 1/|x|sqrt(1-n^(2)x^(2))
	else if(type == 24)
		diff = int_to_string2(-1*string_to_int(coeff)*string_to_int(xcoeff)) + "/(1+" + int_to_string(string_to_int(xcoeff)*string_to_int(xcoeff)) + x + "^(2))" ; // d(arccot(nx))/dx = -n/(1+n^(2)x^(2))

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
	else if(cf == 4 || cf == 5) //cf = 4,5 represent exponential function
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

string prim_is_trigln(string s)
{
	bool trigln = (is_log(s) == 6) || (is_trig(s) >= 7 && is_trig(s) <= 12) || (is_hyperbolic(s) >= 13 && is_hyperbolic(s) <= 18) || (is_inv_trig(s) >= 19 && is_inv_trig(s) <= 24);
	int k = 0;
	if(trigln == true)
	{
		for(int i=0 ; i<s.length() ; i++)
		{
			if(s[i] == '(') //Cases like trig,inv trig,hypergeometric , log
			{
				k = i;
				break;
			}
		}
		string new_s = s.substr(0,k); // take the substring before bracket
		return new_s + "(x)";
	}
	return "";
}

string prim_is_exponential(string s)
{
	bool powercase = false; // Cases of e^(f(x))
	int k=0 ;
	for(int i=0 ; i<s.length(); i++)
	{
		if(s[i] == '^') // If power exists then set powercase as true
		{
			powercase = true;
			k = i ;
			break;
		}
	}

	if(powercase == true && remove_coeff(s)[0] == 'e') // Takes care of all e^(f(x)) cases
	{
		return "e^(x)";
	}
	else if(powercase == true && is_num(remove_coeff(s)[0]) != -1) // Takes care of all a^(f(x)) cases
	{
		return s.substr(0,k+1) + "(x)" ;
	}

	return "";
}

string prim_is_power(string s) //Cases like f(x)^(n) or f(x) or constants   // sin(x^(2)) ... (sin(x))^(2)
{
	bool func_power = false;
	int k=0;
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == '^' && is_num(s[i+2]) != -1 && s[i-1] == ')')
		{
			func_power = true;
			k = i;
			break;
		}
	}

	if(func_power == true)
	{
		return "x" + s.substr(k,s.length()-k) ; // x + whatever power it was
	}
	return "";
}

string findPrimary(string s) //Finds the function outside , ie input -> gof(x) ; output -> g(x) 
{
	if(prim_is_power(s) != "")
		return prim_is_power(s);
	else if(prim_is_exponential(s) != "")
		return prim_is_exponential(s);
	else if(prim_is_trigln(s) != "")
		return prim_is_trigln(s);

	return s;
}

string findFPow(string s) //Find f(x) in case of power (f(x)) ^ n cases
{
	int k=0;
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == '^' && is_num(s[i+2]) != -1)
		{
			k = i;
			break;
		}
	}
	return s.substr(1,k-2) ; // string before power 
}

string findFExpo(string s) //Find f(x) in Cases for e^(f(x)) and k^(f(x))
{
	int k=0 ; 
	for(int i=0 ; i<s.length() ; i++) //Finding th index of "^"
	{
		if(s[i] == '^')
		{
			k = i;
			break;
		}
	}
	return s.substr(k+2,s.length()-k-3); //Taking the poertion after '^'
}

string findFTrigln(string s)
{
	int k=0 ; 
	for(int i=0 ; i<s.length() ; i++)
	{
		if(s[i] == '(')
		{
			k = i;
			break;
		}
	}
	return s.substr(k+1,s.length()-k-2);
}
string findF(string s)
{
	if(prim_is_power(s) != "")
		return findFPow(s);
	else if(prim_is_exponential(s) != "")
		return findFExpo(s);
	else if(prim_is_trigln(s) != "")
		return findFTrigln(s);
	return "x";
}

string differentiation_chain_rule(string s)                   //Do not forget to add to original code
{
	string primary = findPrimary(s);
	string secondary = findF(s) ;

	// cout << primary << "  " << secondary << endl;

	int cf = check_function(primary);
	if(remove_coeff(secondary) == "x")
		return differentiation(s,cf);

	// (2sin(3x))^(2) = 2*(2sin(3x))*(3cos(3x)) but without remove_coeff(secondary) it gives (4sin(3x))*(6cos(3x)) <-- 6 shouldnt be here

	if(cf == 0 || cf == 1 || cf == 3) // cf = 0,1,3 represnt power function
		return "(" + diff_power(primary,secondary,cf) + ")*(" + differentiation(remove_coeff(secondary),check_function(secondary)) + ")"  ;
	else if(cf == 4 || cf == 5)
		return "(" + diff_exponential(primary,secondary,cf) + ")*(" + differentiation(remove_coeff(secondary),check_function(secondary))  + ")"  ;
	else if(cf == 6)
		return "(" + diff_log(primary,secondary) + ")*(" + differentiation(remove_coeff(secondary),check_function(secondary))  + ")"  ;
	else if(cf >= 7 && cf <= 12)
		return "(" + diff_trig(primary,secondary,cf) + ")*(" + differentiation(remove_coeff(secondary),check_function(secondary))  + ")"  ;
	else if(cf >= 13 && cf <= 18)
		return "(" + diff_hyperbolic(primary,secondary,cf) + ")*(" + differentiation(remove_coeff(secondary),check_function(secondary))  + ")"  ;
	else if(cf >= 19 && cf <= 24)
		return "(" + diff_inv_trig(primary,secondary,cf) + ")*(" + differentiation(remove_coeff(secondary),check_function(secondary))  + ")"  ;
}

string addition(string s1, string s2) //This function is not being used
{
	return "(" + differentiation(s1,check_function(s1)) + ") + (" + differentiation(s2,check_function(s2)) + ")";
}

string subtraction(string s1, string s2) //This function is not being used
{
	return "(" + differentiation(s1,check_function(s1)) + ") - (" + differentiation(s2,check_function(s2)) + ")";
}

string multiplication(string s1,string s2) // Multiplication rule (f*g)' = f'g + g'f 
{
	return "{(" + s2 + ")*(" + differentiation_chain_rule(s1) + ") + (" + s1 + ")*(" + differentiation_chain_rule(s2) + ")}" ;
}

string divide(string s1, string s2) // s1 = numerator , s2 = denominator // This function is not being used
{
	return "{(" + s2 + ")*(" + differentiation(s1,check_function(s1)) + ") - (" + s1 + ")*(" + differentiation(s2,check_function(s2)) + ")}/{(" + s2 + ")^(2) }" ;
}

string diff_expression(string func[], string oper[], int count) //Input : array of functions, operators, number of operators ;  Output:  String of the differentiated expression
{
	if(func[0] == "")
		return "";
	string exp_prime = "";
	int k=0;
	for(int i=0 ; i<count ;i++)
	{
		string f_prime;
		if(oper[i] == "+")    //If it is a sum we just differentiate it
			f_prime = differentiation_chain_rule(func[i]) ;
		else if(oper[i] == "-")    //If it is a sum we just differentiate it
			f_prime = differentiation_chain_rule(func[i]) ;
		else if(oper[i] == "*")
		{
			f_prime = multiplication(func[i],func[i+1]);
			i++;
		}
		if(i>0) //For terms not the first term approprite sign is important
		{
			if(f_prime[0] == '-')
			{
				if(oper[k] == "+" || oper[k] == "*") // - + = -
					exp_prime += " " + f_prime;
				else if(oper[k] == "-")             // - - = +
					exp_prime += " + " + f_prime;
			}
			else
			{
				if(oper[k] == "+" || oper[k] == "*") // + + = +
					exp_prime += " + " + f_prime;
				else if(oper[k] == "-")            // + - = -
					exp_prime += " - " + f_prime;
			}
		}
		else //If it it the first term exp_prime = f_prime
			exp_prime += f_prime;
		k = i;
	}
	string temp;
	if(k != count ) //For cases when there is only one term , eg sin(x)
	{
		temp = differentiation_chain_rule(func[k+1]) ;
		if(temp[0] == '-')
		{	
			if(oper[count-1] == "+" || oper[count-1] == "*")
				exp_prime += " " + temp;
			else if(oper[count-1] == "-")
				exp_prime += "+" + temp;
		}
		else
		{
			if(oper[count-1] == "+" || oper[count-1] == "*")
				exp_prime += " + " + temp;
			else if(oper[count-1] == "-")
				exp_prime += "-" + temp;
		}
	}
	if(count == 0)
	{
		exp_prime += differentiation_chain_rule(func[0]);
		// cout << "f = " << func[0] << endl;
	}

	return exp_prime;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	fstream myfile ;
	myfile.open("input3.txt");
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

	/*
	So, below what i have done is as follows
	First, I made an array (called bracket) of 1 for ( and -1 for ) and 6 for  / and other operators
	I start from the index where breacket[i] = 6, and traverse both ways
	I traverse(both ways) till sum(both the sums) becomes 0, since ( is 1 and ) is -1, this helps in bracket matching
	I store 4 indexes start, end , num_end and denom_start
	Then store them in arrays for cases where there are multiple divisions (actually i counted number of 6's in bracket[i] and stored in count and then in n later)
	Then using substr function of strings to store the substrings and the operators in an array of strings which i use later
	I make a new string new_string_without _fraction where I remove the fraction terms and only contains only +,- and * operations
	I differentiate new_string_without _fraction using diff_expression
	Then i store the result in a string
	Now, i need to differentiate the fraction term
	So, first I separate the numerator and denominators and store in a 2d string array here i use the frction function i made earlier
	Then I further break the numerators and denomnators into individual function and operators
	I do this as it is required for the diff_expression 
	i find num_prime and denom_prime using diff_expression
	then i use the division rule f/g = (gf' - fg' )/ g^2
	Here f and g are numerators and f' and g' are num_prime and denom_prime
	*/

	int bracket[new_exp.length()] ; //Keep an arrray of int to keep track of brackets and operators
	count = 0;
	for(int i=0 ; i<new_exp.length(); i++)
	{
		bracket[i] = 0;
		if(new_exp[i] == '(')
			bracket[i] = 1;
		else if(new_exp[i] == ')')
			bracket[i] = -1;
		else if(new_exp[i] == '+')
			bracket[i] = 3;
		else if(new_exp[i] == '-' && new_exp[i-1] != '(')
			bracket[i] = 4;
		else if(new_exp[i] == '*')
			bracket[i] = 5;
		else if(new_exp[i] == '/')
		{
			bracket[i] = 6;
			count++;
		}
	}


	//Special Requirement for fractions
	string fractions[count] ;
	string oper_frac[count] ; // Stores operators before fraction
	int n = count;
	int start[count],end[count]; //Stores the starting index and ending ndexes of all fraction
	int numer_end[count], denom_start[count]; //Stores the ending index of the numerator and starting index of denominator 

	if(count != 0)
	{
		int count1 = 0 ;
		for(int i=0 ; i<new_exp.length() ; i++)
		{
			if(bracket[i] == 6) //Checking for bracket
			{
				int p = i-1, q = i-2; //Setting indexes before and 2 places before fration
				int l = i+1 ,m = i+2; //Setting indexes after and 2 places after fration
				int sumpq, sumlm; //Keeps status whther the bracket are complete or not, if sum = 0,then complete otherise incomplete
				
				sumpq = bracket[p]+bracket[q]; 
				sumlm = bracket[l]+bracket[m];
				q--;
				m++;
				while(sumpq != 0 ||  sumlm != 0) //We continue the loop till the ) and ( brakets match
				{
					if((bracket[q] == 1 || bracket[q] == -1) && sumpq != 0) //If the qth index is ( or ) we add 1 or -1 respectively to the sum
					{
						sumpq += bracket[q]; 
					}
					if((bracket[m] == 1 || bracket[m] == -1) && sumlm != 0) //If the mth index is ( or ) we add 1 or -1 respectively to the sum
					{
						sumlm += bracket[m]; 
					}
					if(sumpq != 0) //We continue decrementing it till brackets are matched or sumpq == 0
						q--;
					if(sumlm != 0) //We continue decrementing it till brackets are matched or sumlm == 0
						m++;
				}
				start[count1] = q; // q is the starting index of the fracttion 
				numer_end[count1] = p; //p is the ending index of numerator
				denom_start[count1] = l; // l is the starting inde of denominator
				end[count1++] = m; // m is the ending index of the fraction
			}
		}	
	}



	for(int i=0 ; i<count ; i++)
	{
		fractions[i] = new_exp.substr(start[i],end[i] - start[i] + 1); //Uses the start and end array to get substrings 
		if(start[i] != 0)
			oper_frac[i] = new_exp.substr(start[i]-1,1) ;
		else if(start[i] == 0)
			oper_frac[i] = "";
	}
	
	string new_exp_without_fraction = "";
	//Basically new_exp_without_fraction = end(prev) to start(next)  , where end and start are indexes of fractions
	if(count > 0 && start[0] == 0)
		new_exp_without_fraction += new_exp.substr(end[0]+1,start[1]-end[0]-2);	
	if(start[0] != 0)
		new_exp_without_fraction += new_exp.substr(0,start[0]-1);
	for(int i=0 ; i<count ; i++)
	{
		if(start[i] != 0)
			new_exp_without_fraction += new_exp.substr(end[i]+1,start[i+1] - end[i] -2);
	}
	// cout << new_exp_without_fraction << endl;



	//Breaking the new_exp_without_fraction into array of functions;
	count = 0;
	for(int i=0 ; i<new_exp_without_fraction.length(); i++)
	{
		if(new_exp_without_fraction[i] == '+' || new_exp_without_fraction[i] == '*' || (new_exp_without_fraction[i] == '-' && new_exp_without_fraction[i-1] != '(' && i!=0))
			count++;
	}
	string func[count+1] ;
	string oper[count] ;

	int k=0 ,l=0,m=0;
	for(int i=0 ; i<new_exp_without_fraction.length() ; i++)
	{
		if(new_exp_without_fraction[i] == '+' || new_exp_without_fraction[i] == '*' || (new_exp_without_fraction[i] == '-' && new_exp_without_fraction[i-1] != '(' && i!=0))
		{
			func[l] = new_exp_without_fraction.substr(k,i-k);
			oper[l++] = new_exp_without_fraction.substr(i,1);
			k = i+1;
		}
	}
	func[l] = new_exp_without_fraction.substr(k,new_exp_without_fraction.length()-k);
/////////////////////////////////////////////////////
//ACTUAL DIFFERENTIATION PART
////////////////////////////////////////////////////////////////////////////////////////////////////
	string diff_exp = diff_expression(func,oper,count);

	//Now i will do the same thing for the division
	string numerator[n];
	string denominator[n];

	int index[n][2]; //Mainly for storing the number of opers and functions
	for(int i=0 ; i<n ; i++)
	{
		numerator[i] = new_exp.substr(start[i]+1,numer_end[i] - start[i] - 1); //Using the num_end array and start array to get the numerator of the fraction
		denominator[i] = new_exp.substr(denom_start[i] + 1, end[i] - denom_start[i] - 1); //Using the denom_start array and end array to get the denominator of the fraction
	}

	for(int j=0 ; j<n ; j++)
	{
		count = 0;
		//Counting the number of operator in the numerator
		for(int i=0 ; i<numerator[j].length(); i++)
		{
			if(numerator[j][i] == '+' || numerator[j][i] == '*' || (numerator[j][i] == '-' && numerator[j][i-1] != '(' && i!=0)) //If operator is found then increment count
				count++;
		}
		index[0][j] = count; //0 for numerator

		count = 0;
		//Counting the number of operator in the denominator
		for(int i=0 ; i<denominator[j].length(); i++)
		{
			if(denominator[j][i] == '+' || denominator[j][i] == '*' || (denominator[j][i] == '-' && denominator[j][i-1] != '(' && i!=0))////If operator is found then increment count
				count++;
		}
		index[1][j] = count; // 1 for denominator
	}


	string func_num[n][maxArr(index[0],n)+1] ;
	string oper_num[n][maxArr(index[1],n)+1] ;

	string func_denom[n][maxArr(index[0],n)+1] ;
	string oper_denom[n][maxArr(index[1],n)+1] ;
	

	for(int j=0 ; j<n ; j++)
	{
		k=0;
		l=0;
		m=0;
		for(int i=0 ; i<numerator[j].length() ; i++)
		{
			if(numerator[j][i] == '+' || numerator[j][i] == '*' || (numerator[j][i] == '-' && numerator[j][i-1] != '(' && i!=0))
			{
				func_num[j][l] = numerator[j].substr(k,i-k);
				oper_num[j][l++] = numerator[j].substr(i,1);
				k = i+1;
			}
		}
		func_num[j][l] = numerator[j].substr(k,numerator[j].length()-k);

		k=0;
		l=0;
		m=0;
		for(int i=0 ; i<denominator[j].length() ; i++)
		{
			if(denominator[j][i] == '+' || denominator[j][i] == '*' || (denominator[j][i] == '-' && denominator[j][i-1] != '(' && i!=0))
			{
				func_denom[j][l] = denominator[j].substr(k,i-k);
				oper_denom[j][l++] = denominator[j].substr(i,1);
				k = i+1;
			}
		}
		func_denom[j][l] = denominator[j].substr(k,denominator[j].length()-k);
	}

	string num_prime[n];
	string denom_prime[n];

	for(int i=0 ; i<n ; i++) //Applying differentiation on numerator and denominator
	{
		num_prime[i] = diff_expression(func_num[i],oper_num[i],index[0][i]);
		denom_prime[i] = diff_expression(func_denom[i],oper_denom[i],index[1][i]);	
	}

	string div_diff = "";
	for(int i=0 ; i<n ; i++)
	{
		string div = "";
		div = "[{ (" + denominator[i] + ") * {(" + num_prime[i] + ")} - { {" + numerator[i] + "} * (" + denom_prime[i] + ")} } / { (" + denominator[i] + ")^(2) }]" ; //Division rule 
		diff_exp += " " + oper_frac[i] + " " + div;
	}
	cout << diff_exp << endl;
}
