#include<iostream>
#include <string>
using namespace std;

int main(){

    cout<<"A subnet (short for sub-network) is a smaller, logically isolated segment of a larger IP network created to improve performance, management, and security."<<endl;
    cout<<"A subnet mask is a 32-bit configuration number that defines which specific part of an IP address identifies the network and which part identifies the unique host device."<<endl;

    string ip;
    cout<<"Enter IPV4 address : ";
    cin>>ip;
    string first="";
    int index=0;
    while(ip[index]!='.'){
        first.push_back(ip[index]);
        index++;
    }
    int fod=stoi(first);
    //first octet decimal
    cout<<fod<<endl;

    cout<<"A loopback address is a special, reserved IP address used by a device to send network traffic back to itself for software testing and local service configuration, bypassing the physical network hardware."<<endl;


    cout << "IP Evaluation for First Octet: " << fod << "\n";
    cout << "------------------------------------------\n";

    if (fod >= 0 && fod <= 127) {
        cout << "Class:               Class A\n";
        cout << "IP Range:            0.0.0.0 to 127.255.255.255\n";
        cout << "Default Subnet Mask: 255.0.0.0 (/8)\n";
        cout << "Hosts per Network:   16,777,214 (2^24 - 2)\n";
        cout << " We subtract minus 2 because the Network Address (first IP) identifies the network itself to routers, while the Broadcast Address (last IP) sends data to all devices simultaneously.\n";
        cout << "Number of Networks:  128 (2^7)\n";
        cout << "Note:                127.0.0.0/8 is reserved for loopback testing.\n";
    }
    else if (fod >= 128 && fod <= 191) {
        cout << "Class:               Class B\n";
        cout << "IP Range:            128.0.0.0 to 191.255.255.255\n";
        cout << "Default Subnet Mask: 255.255.0.0 (/16)\n";
        cout << "Hosts per Network:   65,534 (2^16 - 2)\n";
        cout << " We subtract minus 2 because the Network Address (first IP) identifies the network itself to routers, while the Broadcast Address (last IP) sends data to all devices simultaneously.\n";
        cout << "Number of Networks:  16,384 (2^14)\n";
    }
    else if (fod >= 192 && fod <= 223) {
        cout << "Class:               Class C\n";
        cout << "IP Range:            192.0.0.0 to 223.255.255.255\n";
        cout << "Default Subnet Mask: 255.255.255.0 (/24)\n";
        cout << "Hosts per Network:   254 (2^8 - 2)\n";
        cout << " We subtract minus 2 because the Network Address (first IP) identifies the network itself to routers, while the Broadcast Address (last IP) sends data to all devices simultaneously.\n";
        cout << "Number of Networks:  2,097,152 (2^21)\n";
    }
    else if (fod >= 224 && fod <= 239) {
        cout << "Class:               Class D\n";
        cout << "IP Range:            224.0.0.0 to 239.255.255.255\n";
        cout << "Default Subnet Mask: None\n";
        cout << "Hosts per Network:   N/A (Group communication)\n";
        cout << "Purpose:             Multicasting\n";
    }
    else if (fod >= 240 && fod <= 255) {
        cout << "Class:               Class E\n";
        cout << "IP Range:            240.0.0.0 to 255.255.255.255\n";
        cout << "Default Subnet Mask: None\n";
        cout << "Hosts per Network:   N/A\n";
        cout << "Purpose:             Experimental / Research / Future Use\n";
    }
    else {
        cout << "Error: Invalid IPv4 address octet. Value must be between 0 and 255.\n";
    }

    return 0;




   
}