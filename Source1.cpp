#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int Sum(int a, int b){
    int x = a ^ b;
    int c = a & b;

    if (c == 0)
        return x;
    else
        return Sum(x, c << 1);
}

int Subtract(int a, int b){
    if(b != 0){
        int c = (~a) & b;
        a = a ^ b;
        b = c << 1;
        Subtract(a, b);
    } else
        return a;
}

std::string Extract(std::string s, std::string temp, int& i){
    temp.at(0) = s.at(i);
    temp.at(1) = s.at(Sum(i, 1));
    temp.at(2) = s.at(Sum(i, 2));
    temp.at(3) = s.at(Sum(i, 3));
    temp.at(4) = s.at(Sum(i, 4));
//    std::cout << temp << std::endl;

    return temp;
}

int Code(std::string s){
    if(s == "00000")
        return 31;
    if(s == "00001")
        return 30;
    if(s == "00010")
        return 29;
    if(s == "00011")
        return 28;
    if(s == "00100")
        return 27;
    if(s == "00101")
        return 26;
    if(s == "00110")
        return 25;
    if(s == "00111")
        return 24;
    if(s == "01000")
        return 23;
    if(s == "01001")
        return 22;
    if(s == "01010")
        return 21;
    if(s == "01011")
        return 20;
    if(s == "01100")
        return 19;
    if(s == "01101")
        return 18;
    if(s == "01110")
        return 17;
    if(s == "01111")
        return 16;
    if(s == "10000")
        return 15;
    if(s == "10001")
        return 14;
    if(s == "10010")
        return 13;
    if(s == "10011")
        return 12;
    if(s == "10100")
        return 11;
    if(s == "10101")
        return 10;
    if(s == "10110")
        return 9;
    if(s == "10111")
        return 8;
    if(s == "11000")
        return 7;
    if(s == "11001")
        return 6;
    if(s == "11010")
        return 5;
    if(s == "11011")
        return 4;
    if(s == "11100")
        return 3;
    if(s == "11101")
        return 2;
    if(s == "11110")
        return 1;
    if(s == "11111")
        return 0;

}

int Decode(std::string s){
    int value = 0;
    if(s.at(31) == '1')
        value = Sum(value, 1);
    if(s.at(30) == '1')
        value = Sum(value, 2);
    if(s.at(29) == '1')
        value = Sum(value, 4);
    if(s.at(28) == '1')
        value = Sum(value, 8);
    if(s.at(27) == '1')
        value = Sum(value, 16);
    if(s.at(26) == '1')
        value = Sum(value, 32);
    if(s.at(25) == '1')
        value = Sum(value, 64);
    if(s.at(24) == '1')
        value = Sum(value, 128);
    if(s.at(23) == '1')
        value = Sum(value, 256);
    if(s.at(22) == '1')
        value = Sum(value, 512);
    if(s.at(21) == '1')
        value = Sum(value, 1024);
    if(s.at(20) == '1')
        value = Sum(value, 2048);
    if(s.at(19) == '1')
        value = Sum(value, 4096);
    if(s.at(18) == '1')
        value = Sum(value, 8192);
    if(s.at(17) == '1')
        value = Sum(value, 16384);
    if(s.at(16) == '1')
        value = Sum(value, 32768);
    if(s.at(15) == '1')
        value = Sum(value, 65536);
    if(s.at(14) == '1')
        value = Sum(value, 131072);
    if(s.at(13) == '1')
        value = Sum(value, 262144);
    if(s.at(12) == '1')
        value = Sum(value, 524288);
    if(s.at(11) == '1')
        value = Sum(value, 1048576);
    if(s.at(10) == '1')
        value = Sum(value, 2097152);
    if(s.at(9) == '1')
        value = Sum(value, 4194304);
    if(s.at(8) == '1')
        value = Sum(value, 8388608);
    if(s.at(7) == '1')
        value = Sum(value, 16777216);
    if(s.at(6) == '1')
        value = Sum(value, 33554432);
    if(s.at(5) == '1')
        value = Sum(value, 67108864);
    if(s.at(4) == '1')
        value = Sum(value, 134217728);
    if(s.at(3) == '1')
        value = Sum(value, 268435456);
    if(s.at(2) == '1')
        value = Sum(value, 536870912);
    if(s.at(1) == '1')
        value = Sum(value, 1073741824);
    if(s.at(0) == '1')
        value = Sum(value, 2147483648);

    return value;
}

void IterateString(std::string s, int i, int *a, int negative = 0, std::string Container = "00000000000000000000000000000000"){
    if(i < s.length()){
        std::string temp = "     ";
        std::string temp1;
        int code;
        if(s.at(i) != ' '){
            temp1 = Extract(s, temp, i);  //extract 5 element string
            code = Code(temp1);               //code string to integer
            Container.at(code) = '1';
            code = Decode(Container);
            *a = code;

//            std::cout << *a << std::endl;
//            std::cout << Container << std::endl;
//            std::cout << code << std::endl;
            i = Sum(i, 5);

            IterateString(s, i, a, negative, Container);
        }
        else if(s.at(i) == ' '){       //if space present then skip it
            i = Sum(i, 1);
            IterateString(s, i, a, negative, Container);
        }
    }
}

std::string DecToBin(int value, std::string& Output, int i = 32){
    if(value % 2 == 0 and value != 0){
        i = Subtract(i, 1);
        value /= 2;
        DecToBin(value, Output, i);
    } else if(value % 2 != 0){
        i = Subtract(i, 1);
        value = Subtract(value, 1);
        value /= 2;
        Output.at(i) = '1';    //fix me
        DecToBin(value, Output, i);
    }

    return Output;
}

std::string DecodeInt(int *value){
    std::string Output = "00000000000000000000000000000000";
    int negative = 0;
    if(*value < 0){
        *value = Sum(*value, 2147483648);
        negative = 1;
    }
    if(negative == 1)
        Output.at(0) = '1';

    DecToBin(*value, Output);

    return Output;
}

void Insert2(std::string s, int *a){
    int i = 0;
    int B = 0;
    int *ptr2 = &B;
    IterateString(s, i, ptr2);
    *a = *a | *ptr2;
//    std::cout << *a;
}

int BitCount(int a){
    int negative = 0;
    if(a == Subtract(0,2147483648))
        return 1;
    if(a < 0){
        a = Sum(a,2147483648);
        negative = 1;
    }

    if (a == 0)
        return 0;
    else
        return Sum(Sum((a & 1) , BitCount(a >> 1)), negative);
}
void Emplace(std::string s, int *a){
    int i = 0;
    *a = 0;
    IterateString(s, i, a);
//    std::cout << *a << std::endl;
}

void Insert(std::string s, int *a){
    Insert2(s, a);
}

void Erase(std::string s, int *a){
    int i = 0;
    int B = 0;
    int *ptr2 = &B;
    IterateString(s, i, ptr2);
    *ptr2 = ~(*ptr2);
    *a &= *ptr2;
}

void Print(int code, std::string *s){
    *s = "";
    std::stringstream stream;
    int *ptrcode = &code;
//    std::cout << *ptrcode;
    std::string decoded = DecodeInt(ptrcode);   //decode int into 32 bit string
    if(decoded == "00000000000000000000000000000000"){
        *s = "empty";
        cout << *s << endl;
        return;
    }
    else{
        if(decoded.at(0) == '1')
            stream << "11111" << " ";
        if(decoded.at(1) == '1')
            stream << "11110" << " ";
        if(decoded.at(2) == '1')
            stream << "11101" << " ";
        if(decoded.at(3) == '1')
            stream << "11100" << " ";
        if(decoded.at(4) == '1')
            stream << "11011" << " ";
        if(decoded.at(5) == '1')
            stream << "11010" << " ";
        if(decoded.at(6) == '1')
            stream << "11001" << " ";
        if(decoded.at(7) == '1')
            stream << "11000" << " ";
        if(decoded.at(8) == '1')
            stream << "10111" << " ";
        if(decoded.at(9) == '1')
            stream << "10110" << " ";
        if(decoded.at(10) == '1')
            stream << "10101" << " ";
        if(decoded.at(11) == '1')
            stream << "10100" << " ";
        if(decoded.at(12) == '1')
            stream << "10011" << " ";
        if(decoded.at(13) == '1')
            stream << "10010" << " ";
        if(decoded.at(14) == '1')
            stream << "10001" << " ";
        if(decoded.at(15) == '1')
            stream << "10000" << " ";
        if(decoded.at(16) == '1')
            stream << "01111" << " ";
        if(decoded.at(17) == '1')
            stream << "01110" << " ";
        if(decoded.at(18) == '1')
            stream << "01101" << " ";
        if(decoded.at(19) == '1')
            stream << "01100" << " ";
        if(decoded.at(20) == '1')
            stream << "01011" << " ";
        if(decoded.at(21) == '1')
            stream << "01010" << " ";
        if(decoded.at(22) == '1')
            stream << "01001" << " ";
        if(decoded.at(23) == '1')
            stream << "01000" << " ";
        if(decoded.at(24) == '1')
            stream << "00111" << " ";
        if(decoded.at(25) == '1')
            stream << "00110" << " ";
        if(decoded.at(26) == '1')
            stream << "00101" << " ";
        if(decoded.at(27) == '1')
            stream << "00100" << " ";
        if(decoded.at(28) == '1')
            stream << "00011" << " ";
        if(decoded.at(29) == '1')
            stream << "00010" << " ";
        if(decoded.at(30) == '1')
            stream << "00001" << " ";
        if(decoded.at(31) == '1')
            stream << "00000" << " ";

        std::string m = stream.str();
        *s = m;
        cout << m << endl;
    }
//
//    std::cout << *s;
//    std::cout << stream.str();
}

bool Emptiness(int a){
    return a == 0;
}

bool Nonempty(int a){
    return a != 0;
}

bool Member(std::string s, int a){  //fix me
    int B = 0;
    int *ptr = &B;
    int i = 0;
    int a2 = a;
    IterateString(s, i, ptr);

    a2 |= *ptr;

    return a2 == a;
}

bool Disjoint(int a, int b){
    return !(a & b);
}

bool Conjunctive(int a, int b){
    return a & b;
}

bool Equality(int a, int b){
    return a == b;
}

bool Inclusion(int a, int b){
    int c = ~a;
    c |= b;
    return c == ~(0);

}

void Union(int a, int b, int *c = 0){
    int d = a | b;
    *c = d;
}

void Intersection(int a, int b, int *c = 0){
    int d = a & b;
    *c = d;
}

void Symmetric(int a, int b, int *c = 0){
    int d = a ^ b;
    *c = d;
}

void Difference(int a, int b, int *c = 0){
    b = ~b;
    int d = a & b;
    *c = d;
}

void Complement(int a, int *b){
    *b = ~(a);
}

bool LessThen(int a, int b){
    int amounta = BitCount(a);
    int amountb = BitCount(b);

    if(amounta == amountb){
        return (unsigned int) a < (unsigned int) b;
    }

    return amounta < amountb;
}

bool LessEqual(int a, int b){
    int amounta = BitCount(a);
    int amountb = BitCount(b);

    if(amounta == amountb){
        return (unsigned int) a <= (unsigned int) b;
    }


    return amounta <= amountb;
}

bool GreatEqual(int a, int b){
    int amounta = BitCount(a);
    int amountb = BitCount(b);

    if(amounta == amountb){
        return (unsigned int) a >= (unsigned int) b;
    }

    return amounta >= amountb;
}

bool GreatThen(int a, int b){
    int amounta = BitCount(a);
    int amountb = BitCount(b);

    if(amounta == amountb){
        return (unsigned int) a > (unsigned int) b;
    }

    return amounta > amountb;
}

int main() {
//    string s = "11100 00100 11111 11001 11101 11111 11111";
//    int A = 0;
//    int *ptr = &A;
//    Emplace(s, ptr);
//    cout << *ptr << endl;
    string s = "";
    string *ptr2 = &s;
    Print(0, ptr2);


}

