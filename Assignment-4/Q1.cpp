//Refer the comments carefully to easily understand the processs involved in solving.
//After running this code on any C++ compiler (does not need any external input), you will get the output which I have also separately attached and explained in .txt file.


#include <bits/stdc++.h>
using namespace std;


//To find XOR of two strings
string XOR_Strings(string first_string, string second_string){

    string result;

    for(long j = 0; j <= first_string.size()-1; j++){

        if(first_string[j] != second_string[j])
            result.push_back('1');
        else
            result.push_back('0');

    }
    return result;
}


//For generating a random k-bits message 
string random_message(long k){

    string str;

    while(k != str.size()){

        str.push_back('0' + rand()%2);

    }
    return str;
}

//Finding the remainder
string CRC(string P, string D){ // p for pattern and D for Data block 

    long k = D.size(), iteration = P.size();
    long n = P.size() + k -1;

    D.append(string(P.size()-1, '0'));

    string present = D.substr(0, iteration);
    
    while(iteration < n+1){
        if(present[0] == '0')
        { 
            
        }

        else{

            present = XOR_Strings(present, P);

        }

        present = present.substr(1);

        if(iteration != n){

        present.push_back(D[iteration]);
        iteration += 1;

        }

        else{

            break;
        }
        
    }
    
    return present;
}

int main(){
    string P, data_block, signal_encoded;
    // Consider 4 sample input cases to verify the code
    // Sample Input 1
    P = "110101"; data_block = "1010001101";
    string remainder_crc = CRC(P, data_block);
    signal_encoded = data_block+remainder_crc;
    cout<<"Following are four sample inputs\n\n";
    cout << "P is " << P << ", D is " << data_block << '\n';
    cout << "The Encoded data is: " << signal_encoded << " with " <<P.size()-1<< " last digits as CRC: " << remainder_crc<<"\n\n"; // CRC will be 01110 and codeword will be 101000110101110
   
    // Sample Input 2
    P = "1010"; data_block = "1010101010";
    remainder_crc = CRC(P,data_block);
    signal_encoded = data_block+remainder_crc;
    cout << "P is " << P << ", D is " << data_block << '\n';
    cout << "The Encoded data is: " << signal_encoded << " with " <<P.size()-1<< " last digits as CRC: " << remainder_crc<<"\n\n"; // CRC will be 100 and codeword will be 1010101010100

    // Sample Input 3
    P = "1011"; data_block = "1010101010";
    remainder_crc = CRC(P, data_block);
    signal_encoded = data_block+remainder_crc;
    cout << "P is " << P << ", D is " << data_block << '\n';
    cout << "The Encoded data is: " << signal_encoded << " with " <<P.size()-1<< " last digits as CRC: " << remainder_crc<<"\n\n"; // CRC will be 101 and codeword will be 1010101010101

    // Smaple Input 4
    P = "1000"; data_block = "1010101011";
    remainder_crc = CRC(P, data_block);
    signal_encoded = data_block+remainder_crc;
    cout << "P is " << P << ", D is " << data_block << '\n';
    cout << "The Encoded data is: " << signal_encoded << " with " <<P.size()-1<< " last digits as CRC: " << remainder_crc<<"\n\n"; // CRC will be 000 and codeword will be 1010101011000



    //Part a) Generate a 10 bit random message
    data_block.clear();
    cout<<"Part a-d begins from here:\n\n";
    srand(time(0));
    
    long k = 10;
    data_block = random_message(k);
    cout << "Random message of 10-bits is: " << data_block << "\n";

    //Part b) Generate the encoded codeword T
    P = "110101";
    remainder_crc= CRC(P, data_block);

    signal_encoded = data_block+remainder_crc;

    cout << "Encoded messsage for pattern P = 110101 is: " << signal_encoded << " having last 5 digits as CRC: "<<remainder_crc<<"\n";

    // Part c) Inroducing errors in transmission frame T
    string error_string = random_message(signal_encoded.size());

    string error_message = XOR_Strings(error_string, signal_encoded);

    cout << "Received erroneous 15 bit message: " << error_message << "\n";

    // Part d) Check if errors are detected and dataword is accepted/rejected
    remainder_crc = CRC(P, error_message);

    long flag = 0;

    for(char c: remainder_crc){
        if(c == '1')
            flag = 1;
    }

    if(flag==1){

        cout << "The message contains error and need re-transmission as the CRC at receiever end is: " << remainder_crc << ", which is, non-zero and dataword is discarded.\n";
    }
    else{

        cout << "No error detected as CRC is zero and dataword accepted is: " << error_message.substr(0, 10)<<'\n';
    }

    if(flag==1){
    //re-transmitting the receiving error free message, only if error is detected
    error_string = string(signal_encoded.size(), '0');
    string error_free_msg = XOR_Strings(error_string, signal_encoded);
    remainder_crc = CRC(P, error_free_msg);
    cout << "Now, error free 15 bit codeword message received on re-transmission: " << error_free_msg << " as CRC obtained at receiver side is: "<<remainder_crc<<'\n';
    cout << "So, 10 bit dataword accepted on re-transmission is: " << signal_encoded.substr(0,10)<< '\n';
    }

}
