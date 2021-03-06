//////////////////////////////////////////////////////////////////////////////
//
// Demo program for SuperDog update process
//
//
// Copyright (C) 2012 SafeNet, Inc. All rights reserved.
//
//
// SuperDog DEMOMA key required
//
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdio.h>

#include <string.h>

#include "dog_api_cpp.h"
#include "errorprinter.h"
#include "vendor_code.h"

using namespace std;

//The memory size reserved for the update
const int approxUpdateSize = 20000;

//The file to which the acknowledge data
//generated by the update function is stored
const char* ackFileName = "dog_ack.c2v";


//Prints the error messages for the return values of the functions
ErrorPrinter errorPrinter;

void displayCloseMessage()
{
	cout<<endl<<"press ENTER to close the sample"<<endl;

    fflush(stdin);
    while (getchar() == EOF);
}

int doGetInfoDemo()
{   
    const char* scope = "<dogscope />";

    cout<<"getting update information       : ";

    string updateInfo;
    dogStatus status = CDog::getInfo(scope, CDog::updateInfo(), vendorCode, updateInfo);
    errorPrinter.printError(status);
    cout<<updateInfo;
    cout<<endl;

    if (!DOG_SUCCEEDED(status))
    {
        return 1;
    }

    string fileName;
    cout<<"Please enter C2V file name: ";
    cin>>fileName;
    cout<<endl<<endl;

    //Write the update information to a file
    ofstream f(fileName.c_str());
    if(!f.write(updateInfo.c_str(), static_cast<streamsize>(updateInfo.length())))
    {
        cout<<"Error: could not write "<<fileName<<endl;
        return 1;
    }
    
    cout<<"SuperDog information stored into file "<<fileName<<endl;
    return 0;
}

int doUpdateDemo()
{
    string fileName;
    cout<<"Please enter the name of an available V2C file: ";
    cin>>fileName;
    cout<<endl<<endl;

    //Read the file fileName into the string updateData
    ifstream f(fileName.c_str());
    string updateData;
    updateData.reserve(approxUpdateSize);
    getline(f, updateData, '\0'); //Reads the whole f, because f is base64 coded
    if(updateData.empty())
    {
        cout<<"Error: could not read "<<fileName<<endl;
        return 1;
    }

    cout<<"updating key                     : ";

    string ackData;
    dogStatus status = CDog::update(updateData, ackData);
    errorPrinter.printError(status);
    cout<<endl;

    if (!DOG_SUCCEEDED(status))
    {
        return 1;
    }

    if(!ackData.empty())
    {
        //Write the acknowledge data to a file
        ofstream of(ackFileName);
        if(!of.write(ackData.c_str(), static_cast<streamsize>(ackData.length())))
        {
            cout<<"Error: could not write "<<ackFileName<<endl;
            return 1;
        }

        cout<<"acknowledge data written to file "<<ackFileName<<endl;
    }

    return 0;
}


int main()
{
    cout<<endl;
    cout<<"This is a simple demo program for SuperDog update functions."<<endl;
    cout<<"Copyright (C) SafeNet, Inc. All rights reserved."<<endl<<endl;

    cout<<"Please choose whether to retrieve SuperDog (i)nformation"<<endl;
    cout<<"or to (u)pdate SuperDog "<<endl;
   

    char input;
    do cin>>input; while((input != 'i') && (input != 'u'));
    cout<<endl;

    int retValue;

    if(input == 'i')
    {
        retValue = doGetInfoDemo();
    }
    else if (input == 'u')
    {
        retValue = doUpdateDemo();
    }
    
    
   	displayCloseMessage();
    return retValue;
}
