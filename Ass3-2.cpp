#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// Convert IP address string into 4 integers
vector<int> parseIP(string ip) {
    vector<int> parts;
    string temp;
    stringstream ss(ip);

    while (getline(ss, temp, '.')) {
        parts.push_back(stoi(temp));
    }

    return parts;
}

// Print a 32-bit number as an IP address
void printIP(unsigned int ip) {
    cout << ((ip >> 24) & 255) << "."
         << ((ip >> 16) & 255) << "."
         << ((ip >> 8) & 255) << "."
         << (ip & 255);
}

int main() {

    string ip;
    int requiredSubnets;

    cout << "Enter IP address: ";
    cin >> ip;

    cout << "Enter number of required subnets: ";
    cin >> requiredSubnets;

    // -------------------------------
    // Step 1: Parse IP
    // -------------------------------

    vector<int> addr = parseIP(ip);

    // -------------------------------
    // Step 2: Find IP Class
    // -------------------------------

    char ipClass;
    int defaultBits;

    if (addr[0] >= 1 && addr[0] <= 126) {
        ipClass = 'A';
        defaultBits = 8;
    }
    else if (addr[0] >= 128 && addr[0] <= 191) {
        ipClass = 'B';
        defaultBits = 16;
    }
    else if (addr[0] >= 192 && addr[0] <= 223) {
        ipClass = 'C';
        defaultBits = 24;
    }
    else {
        cout << "Class D/E address. Not supported.\n";
        return 0;
    }

    cout << "\nIP Class: " << ipClass << endl;

    // -------------------------------
    // Step 3: Calculate borrowed bits
    // -------------------------------

    int borrowedBits = 0;
    int possibleSubnets = 1;

    while (possibleSubnets < requiredSubnets) {
        borrowedBits++;
        possibleSubnets *= 2;
    }

    cout << "Borrowed bits: " << borrowedBits << endl;
    cout << "Actual number of subnets: "
         << possibleSubnets << endl;

    // -------------------------------
    // Step 4: Calculate host bits
    // -------------------------------

    int totalNetworkBits = defaultBits + borrowedBits;
    int hostBits = 32 - totalNetworkBits;

    int addressesPerSubnet = 1 << hostBits;

    cout << "Subnet prefix: /"
         << totalNetworkBits << endl;

    cout << "Addresses per subnet: "
         << addressesPerSubnet << endl;

    cout << "Usable IP addresses per subnet: "
         << addressesPerSubnet - 2 << endl;

    // -------------------------------
    // Step 5: Create subnet mask
    // -------------------------------

    unsigned int mask;

    if (totalNetworkBits == 32)
        mask = 0xFFFFFFFF;
    else
        mask = 0xFFFFFFFF << (32 - totalNetworkBits);

    cout << "Subnet Mask: ";
    printIP(mask);
    cout << endl;

    // -------------------------------
    // Step 6: Convert IP to 32-bit
    // -------------------------------

    unsigned int ipValue =
        ((unsigned int)addr[0] << 24) |
        ((unsigned int)addr[1] << 16) |
        ((unsigned int)addr[2] << 8) |
        (unsigned int)addr[3];

    // Find first network address
    unsigned int network = ipValue & mask;

    // -------------------------------
    // Step 7: Print subnet details
    // -------------------------------

    cout << "\n-----------------------------------------------\n";

    for (int i = 0; i < possibleSubnets; i++) {

        unsigned int subnetNetwork =
            network + (i * addressesPerSubnet);

        unsigned int broadcast =
            subnetNetwork + addressesPerSubnet - 1;

        unsigned int firstIP = subnetNetwork + 1;
        unsigned int lastIP = broadcast - 1;

        cout << "\nSubnet " << i + 1 << endl;

        cout << "Network Address : ";
        printIP(subnetNetwork);

        cout << "\nFirst IP        : ";
        printIP(firstIP);

        cout << "\nLast IP         : ";
        printIP(lastIP);

        cout << "\nBroadcast       : ";
        printIP(broadcast);

        cout << "\n-----------------------------------------------\n";
    }

    return 0;
}

// Output
// Enter IP address: 195.1.1.0
// Enter number of required subnets: 10
// IP Class: C
// Borrowed bits: 4
// Actual number of subnets: 16
// Subnet prefix: /28
// Addresses per subnet: 16
// Usable IP addresses per subnet: 14
// Subnet Mask: 255.255.255.240
// -----------------------------------------------
// Subnet 1
// Network Address : 195.1.1.0
// First IP        : 195.1.1.1
// Last IP         : 195.1.1.14
// Broadcast       : 195.1.1.15
// -----------------------------------------------
// Subnet 2
// Network Address : 195.1.1.16
// First IP        : 195.1.1.17
// Last IP         : 195.1.1.30
// Broadcast       : 195.1.1.31
// -----------------------------------------------
// Subnet 3
// Network Address : 195.1.1.32
// First IP        : 195.1.1.33
// Last IP         : 195.1.1.46
// Broadcast       : 195.1.1.47
// -----------------------------------------------
// Subnet 4
// Network Address : 195.1.1.48
// First IP        : 195.1.1.49
// Last IP         : 195.1.1.62
// Broadcast       : 195.1.1.63
// -----------------------------------------------
// Subnet 5
// Network Address : 195.1.1.64
// First IP        : 195.1.1.65
// Last IP         : 195.1.1.78
// Broadcast       : 195.1.1.79
// -----------------------------------------------
// Subnet 6
// Network Address : 195.1.1.80
// First IP        : 195.1.1.81
// Last IP         : 195.1.1.94
// Broadcast       : 195.1.1.95
// -----------------------------------------------
// Subnet 7
// Network Address : 195.1.1.96
// First IP        : 195.1.1.97
// Last IP         : 195.1.1.110
// Broadcast       : 195.1.1.111
// -----------------------------------------------
// Subnet 8
// Network Address : 195.1.1.112
// First IP        : 195.1.1.113
// Last IP         : 195.1.1.126
// Broadcast       : 195.1.1.127
// -----------------------------------------------
// Subnet 9
// Network Address : 195.1.1.128
// First IP        : 195.1.1.129
// Last IP         : 195.1.1.142
// Broadcast       : 195.1.1.143
// -----------------------------------------------
// Subnet 10
// Network Address : 195.1.1.144
// First IP        : 195.1.1.145
// Last IP         : 195.1.1.158
// Broadcast       : 195.1.1.159
// -----------------------------------------------
// Subnet 11
// Network Address : 195.1.1.160
// First IP        : 195.1.1.161
// Last IP         : 195.1.1.174
// Broadcast       : 195.1.1.175
// -----------------------------------------------

// Subnet 12
// Network Address : 195.1.1.176
// First IP        : 195.1.1.177
// Last IP         : 195.1.1.190
// Broadcast       : 195.1.1.191
// -----------------------------------------------
// Subnet 13
// Network Address : 195.1.1.192
// First IP        : 195.1.1.193
// Last IP         : 195.1.1.206
// Broadcast       : 195.1.1.207
// -----------------------------------------------
// Subnet 14
// Network Address : 195.1.1.208
// First IP        : 195.1.1.209
// Last IP         : 195.1.1.222
// Broadcast       : 195.1.1.223
// -----------------------------------------------
// Subnet 15
// Network Address : 195.1.1.224
// First IP        : 195.1.1.225
// Last IP         : 195.1.1.238
// Broadcast       : 195.1.1.239
// -----------------------------------------------
// Subnet 16
// Network Address : 195.1.1.240
// First IP        : 195.1.1.241
// Last IP         : 195.1.1.254
// Broadcast       : 195.1.1.255
// -----------------------------------------------


