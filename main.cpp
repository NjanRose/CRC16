#include <iostream>
#include <string.h>
using namespace std;
string addBinary(string a, string b)
{
    string result = ""; // Initialize result
    int s = 0;          // Initialize digit sum
    int i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || s == 1)
    {
        // Comput sum of last digits and carry
        s += ((i >= 0)? a[i] - '0': 0);
        s += ((j >= 0)? b[j] - '0': 0);
        // If current digit sum is 1 or 3, add 1 to result
        result = char(s % 2 + '0') + result;
        // Compute carry
        s /= 2;
        // Move to next digits
        i--; j--;
    }
    return result;
}
int crc(char *ip,char *op,char *poly)
{
    int n;
    strcpy(op,ip);
    char opp[50];
    char *op1 = opp;
    strcpy(op1,ip);
    for(int i = 1;i<strlen(poly);i++)
    {
            strcat(op,"0");
            strcat(op1,"0");
    }
    cout<<"Modified data :"<<op<<endl;
    for(int i =0; i<strlen(ip);i++)
    {
        if(op[i]=='1'){
            for(int j =0;j<strlen(poly);j++)
            {
                if(op[i+j]==poly[j])
                    op[i+j]='0';
                else
                    op[i+j]='1';
            }
        }
    }
    cout<<"Check sum is:"<<op<<endl;
    cout<<"Transmitted message is:"<<addBinary(op1,op)<<endl;
    cout<<"Test error detection? 1-yes, 0-no :" ;
    cin>>n;
    string s = addBinary(op1,op);
    if(n)
    {
        cout<<"Enter the position to flip data :";
        cin>>n;
        if(s[n]=='1')
            s[n]='0';
        else
            s[n]='1';

        cout<<"Erroneous data :"<<s<<endl;
    }
     for(int i =0; i<strlen(ip);i++)
    {
        if(s[i]=='1'){
            for(int j =0;j<strlen(poly);j++)
            {
                if(s[i+j]==poly[j])
                    s[i+j]='0';
                else
                    s[i+j]='1';
            }
        }
    }
    cout<<"CRC Checksum :"<<s<<endl;
    for(int i =0;i<s.length();i++)
        if(s[i]=='1')
            return 1;
    return 0;
}
int main()
{
    char ip[50],op[50],recv[50];
    int c;
    char poly[] = "10001000000100001";
    cout << "Enter the input message in binary :" ;
    cin>>ip;
    if(crc(ip,op,poly))
        cout<<"Error DETECTED!!";
    else
        cout<<"No ERROR, valid data!!";
    return 0;
}
