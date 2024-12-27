#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<sstream>

// Constants for admin credentials
const std::string admin_username="admin";
const std::string admin_password="admin1234";
// Struct to store customer, account, and transaction information
struct BankAccount{
    struct Customer{
        std::string customerID;       // Customer's unique ID
        std::string password;        // Customer's password
        std::string name;           // Customer's name
        std::string address;       // Customer's address
        std::string phoneNo;      // Customer's phone number
    } customerInfo;
    struct Account{
        std::string accNumber;         // Account number
        std::string customerID;       // Reference to customerID
        std::string accountType;     // Type of account (Savings, Current, etc.)
        float balance;              // Account balance
    } accountInfo;
    struct Transaction{ 
        int transactionID;                  // Unique transaction ID
        std::string customerID;            // Reference to customerID
        std::string transaction_date;     // Date of transaction
        std::string transaction_type;    // Deposit or Withdrawal
        float amount;
    } transactionInfo;
};
 // Function prototypes
void addRecord(int n);
void viewRecord(std::string searchID);
void editRecord();
void deleteRecord();
int searchRecord(std::string user, std::string pass);
void transaction(std::string user, int n);
void transactionRecord(std::string user);
int main(){
	// Variables for user input
    std::string username, password;
    std::string userID;
    int type,num,key;
    std::cout<<"-------------AIR BANKING-------------\n";
    std::cout<<"Enter the Login type: \n 1)ADMIN\n 2)USER\nEnter between 1 and 2: ";
    std::cin>>type;
    bool loop=true;     // Loop control for menu options
    if(type==1){       // Admin login
        std::cout<<"Enter Admin username: ";
        std::cin>>username;
        std::cout<<"Enter Password: ";
        std::cin>>password;
        if(username==admin_username&&password==admin_password){         // Validate admin credentials
           // Admin menu 
		    while(loop){           
                std::cout<<"Enter the function you want to perform \n 1) Add Record\n 2) View Record\n 3) Edit Record\n 4) Delete Record\n 5) Exit\nEnter the fubction from 1 to 5: ";
                std::cin>>key;

                switch(key){
                    case 1:    // Add new records
                        std::cout<<"Enter the number of accounts to add: ";
                        std::cin>>num;
                        addRecord(num);
                        break;
                    case 2:     // View existing records
                        std::cout<<"Enter the customer's ID: ";
                        std::cin>>userID;
                        viewRecord(userID);
                        break;
                    case 3:     // Edit records
                        editRecord();
                        break;
                    case 4:    // Delete records
                        deleteRecord();
                        break;
                    case 5:    // Exit admin menu
                        loop = false;
                        break;
                    default:
                    	// Invalid option
                        std::cout<<"Error! Input should be between 1 and 5.\n";
                        break;
                }
            }
        }
        else{
                // Admin login failed
            std::cout<<"Incorrect Username or Password!\n";
        }
    }
    if(type==2){      // User login
        std::cout<<"Enter your User ID: ";
        std::cin>>username;
        std::cout<<"Enter Password: ";
        std::cin>>password;
        if(searchRecord(username, password)==2){   // Validate user credentials
            while(loop){      // User menu loop
                std::cout<<"Enter the function you want to perform: \n 1)View record\n 2) Deposit Money\n 3) Withdraw Money\n 4) Transaction Record\n 5) EXIT\nChoose a functiom between 1 and 5: ";
                std::cin>>key;
                switch(key){
                    case 1:        // View user's own record
                        viewRecord(username);
                        break;
                    case 2:       // Deposit money
                        transaction(username,1);
                        break;
                    case 3:       // Withdraw money
                        transaction(username,2);
                        break;
                    case 4:       // View transaction record
                        transactionRecord(username);
                        break;
                    case 5:      // Exit user menu
                        loop = false;
                        break;
                    default:     // Invalid option
                        std::cout<<"Error! Input should be between 1 and 4.\n";
                        break;
                }
            }
        }
        else{
        	 // User login failed
            std::cout<<"Incorrect UserID or Password!\n";
        }
    }
    return 0;
}
 // Function to add customer and account records
void addRecord(int n){
    BankAccount b[n];    // Create an array of BankAccount structures
    for(int i=0; i<n; i++){
    	  // Gather input for each customer's details
        std::cout<<"*********Customer "<<i+1<<"**********\n";
        std::cin.ignore();
        std::cout<<"Enter the Customer ID: ";
        std::getline(std::cin,b[i].customerInfo.customerID);
        std::cout<<"Enter the Customer password: ";
        std::getline(std::cin,b[i].customerInfo.password);
        std::cout<<"Enter the Customer's name: ";
        std::getline(std::cin,b[i].customerInfo.name);
        std::cout<<"Enter the Customer's address: ";
        std::getline(std::cin,b[i].customerInfo.address);
        std::cout<<"Enter the Customer's Phone number: ";
        std::getline(std::cin,b[i].customerInfo.phoneNo);
        std::cout<<"Enter the Customer's Account Number: ";
        std::getline(std::cin,b[i].accountInfo.accNumber);
        std::cout<<"Enter the Customer's Account Type: ";
        std::getline(std::cin,b[i].accountInfo.accountType);
        std::cout<<"Enter the Customer's Balance: ";
        std::cin>>b[i].accountInfo.balance;
        std::cin.ignore();
    }
     // Open files for appending customer and account information
    std::ofstream onfile1;
    std::ofstream onfile2;
    onfile1.open("Customer.txt", std::ios::app);
    onfile2.open("Account.txt", std::ios::app);
    // Write the gathered information to files
    for (int i = 0; i <n; i++){
    	// Check if the current customer's ID and password do not exist in the system
        if(searchRecord(b[i].customerInfo.customerID,b[i].customerInfo.password)==0){
            onfile1<<b[i].customerInfo.customerID<<"|";
            onfile1<<b[i].customerInfo.password<<"|";
            onfile1<<b[i].customerInfo.name<<"|";
            onfile1<<b[i].customerInfo.address<<"|";
            onfile1<<b[i].customerInfo.phoneNo<<"|\n";

            onfile2<<b[i].accountInfo.accNumber<<"|";
            onfile2<<b[i].customerInfo.customerID<<"|";
            onfile2<<b[i].accountInfo.accountType<<"|";
            onfile2<<b[i].accountInfo.balance<<"|\n";
        }
    }
    onfile1.close();   // Close customer file
    onfile2.close();  // Close account file
}
void viewRecord(std::string searchID){
    std::ifstream infile1;
    infile1.open("Customer.txt");
    std::ifstream infile2;
    infile2.open("Account.txt");
    if(!infile1.is_open()||!infile2.is_open()){
        std::cerr << "Error: Could not open file.\n";
        return;
    }
    bool recFound=false;
    std::string line1, line2;
  // Check customer file for matching customer ID
    while(std::getline(infile1, line1)){
        std::istringstream ss1(line1);
        std::string customerID,password, name, address, phoneNo;
        std::getline(ss1, customerID, '|');
        std::getline(ss1, password, '|');
        std::getline(ss1, name, '|');
        std::getline(ss1, address, '|');
        std::getline(ss1, phoneNo, '|');

        if(searchID==customerID){
            std::cout<<"*********Record Found**********\n";
            std::cout<<"Customer ID: ";
            std::cout<<customerID<<'\n';
            std::cout<<"Customer Password: ";
            std::cout<<password<<'\n';
            std::cout<<"Customer's Name: ";
            std::cout<<name<<'\n';
            std::cout<<"Customer's Address: ";
            std::cout<<address<<'\n';
            std::cout<<"Customer's Phone Number: ";
            std::cout<<phoneNo<<'\n';
        
         // Check account file for associated account details
            while(std::getline(infile2, line2)){
                std::istringstream ss2(line2);
                std::string accNum, accCustomerID,accType, balance;

                std::getline(ss2, accNum, '|');
                std::getline(ss2, accCustomerID, '|');
                std::getline(ss2, accType, '|');
                std::getline(ss2, balance,'|');

                if(searchID==accCustomerID){
                    std::cout<<"Account Number: ";
                    std::cout<<accNum<<'\n';
                    std::cout<<"Account Type: ";
                    std::cout<<accType<<'\n';
                    std::cout<<"Account Balance: ";
                    std::cout<<balance<<'\n';
                    break;
                }
            }
            recFound=true;
            break;
        }
    }
    if(recFound==false){
        std::cout<<"Record NOT Found";
    }
    infile1.close();
    infile2.close();
}
  // Function to edit customer and account details based on Customer ID.
void editRecord(){
    std::string searchID;
    std::cout<<"Enter the Customer ID that you want to edit: ";
    std::cin>>searchID;   // Input Customer ID to edit.
    std::string filename1= "Customer.txt";
    std::string filename2= "Account.txt";
  // File streams for reading and temporary files for writing updated records.
    std::ifstream infile1;
    infile1.open("Customer.txt");
    std::ifstream infile2;
    infile2.open("Account.txt");
    std::ofstream temp1;
    temp1.open("Temp1.txt");
    std::ofstream temp2;
    temp2.open("Temp2.txt");
  // Check if any file failed to open.
    if(!infile1.is_open()||!infile2.is_open()||!temp1.is_open()||!temp2.is_open()){
        std::cerr << "Error: Could not open file.\n";
        return;
    }

    std::string line1,line2;
    bool found=false;     // Flag to check if record is found.

    while(std::getline(infile1, line1)){
        std::istringstream ss1(line1);
        std::string customerID,password, name, address, phoneNo;
        // Cheak customer details from the line.
        std::getline(ss1, customerID, '|');
        std::getline(ss1, password, '|');
        std::getline(ss1, name, '|');
        std::getline(ss1, address, '|');
        std::getline(ss1, phoneNo, '|');

        if(searchID==customerID){
        	 // If matching Customer ID is found, allow user to update details
            std::cin.ignore();
            std::cout<<"Enter the Customer ID: ";
            std::getline(std::cin,customerID);
            std::cout<<"Enter the Customer Password: ";
            std::getline(std::cin,password);
            std::cout<<"Enter the Customer's name: ";
            std::getline(std::cin,name);
            std::cout<<"Enter the Customer's address: ";
            std::getline(std::cin,address);
            std::cout<<"Enter the Customer's Phone number: ";
            std::getline(std::cin,phoneNo);
      
          // Write updated details to temporary file.
            temp1<<customerID<<"|";
            temp1<<password<<"|";
            temp1<<name<<"|";
            temp1<<address<<"|";
            temp1<<phoneNo<<"|\n";
              // Process account records for the same Customer ID.
            while(std::getline(infile2, line2)){
                std::istringstream ss2(line2);
                std::string accNum, accCustomerID,accType, balance;

                std::getline(ss2, accNum, '|');
                std::getline(ss2, accCustomerID, '|');
                std::getline(ss2, accType, '|');
                std::getline(ss2, balance,'|');
                if(searchID==accCustomerID){
                 // If matching account found, allow user to update account type	
                    std::cout<<"Enter the Customer's Account Number: ";
                    std::getline(std::cin,accNum);
                    std::cout<<"Enter the Customer's Account Type: ";
                    std::getline(std::cin,accType);
                    std::cout<<"Enter the Customer's Balance: ";
                    std::cin>>balance;
                // Write updated account details to temporary file.
                    temp2<<accNum<<"|";
                    temp2<<customerID<<"|";
                    temp2<<accType<<"|";
                    temp2<<balance<<"|";
                }
                else{
                // Write unchanged account records to temporary file.
                    temp2<<line2<<"\n";
                }
            }
            found = true;  // Mark record as found
        }
        else{
        	 // Write unchanged customer records to temporary file.
            temp1<<line1<<"\n";
        }
    }
    if(!found){
    	 // Notify if no matching record is found.
        std::cout<<"Record not found!"<<"\n";
    }
     // Close all file streams
    infile1.close();
    infile2.close();
    temp1.close();
    temp2.close();

  // Replace original files with updated temporary files.
    if(remove(filename1.c_str()) != 0){
        std::cerr<<"Error deleting the original file." <<'\n';
    }
    else if(remove(filename2.c_str()) != 0){
        std::cerr<<"Error deleting the original file." <<'\n';
    }
    else if(rename("Temp1.txt", filename1.c_str()) != 0){
        std::cerr<<"Error renaming the temporary file."<<'\n';
    }
    else if(rename("Temp2.txt", filename2.c_str()) != 0){
        std::cerr<<"Error renaming the temporary file."<<'\n';
    }
    else{
        std::cout<<"Record updated successfully!"<<'\n';
    }
}
  // Function to delete customer and associated account records based on Customer ID.
void deleteRecord(){
    std::string searchID;
    std::cout<<"Enter the Customer ID that you want to edit: ";
    std::cin>>searchID;    // Input Customer ID to delete.
    std::string filename1= "Customer.txt";
    std::string filename2= "Account.txt";

  // File streams for reading and temporary files for writing updated records.
    std::ifstream infile1;
    infile1.open("Customer.txt");
    std::ifstream infile2;
    infile2.open("Account.txt");
    std::ofstream temp1;
    temp1.open("Temp1.txt");
    std::ofstream temp2;
    temp2.open("Temp2.txt");

   // Check if any file failed to open.
    if(!infile1.is_open()||!infile2.is_open()||!temp1.is_open()||!temp2.is_open()){
        std::cerr << "Error: Could not open file.\n";
        return;
    }

    std::string line1,line2;
    bool found=false;

    while(std::getline(infile1, line1)){
        std::istringstream ss1(line1);
        std::string customerID,password, name, address, phoneNo;
        // Parse customer details from the line.
        std::getline(ss1, customerID, '|');
        std::getline(ss1, password, '|');
        std::getline(ss1, name, '|');
        std::getline(ss1, address, '|');
        std::getline(ss1, phoneNo, '|');

        if(searchID==customerID){
        	// If matching Customer ID is found, skip writing to temporary file

            while(std::getline(infile2, line2)){   // Process account records to remove associated accounts.
                std::istringstream ss2(line2);
                std::string accNum, accCustomerID,accType, balance;
          // Parse customer details from the line.
                std::getline(ss2, accNum, '|');
                std::getline(ss2, accCustomerID, '|');
                std::getline(ss2, accType, '|');
                std::getline(ss2, balance,'|');

                if(searchID==accCustomerID){
                	 // Skip writing this account record.
                }
                else{
                	 // Write unchanged account records to temporary file.
                    temp2<<line2<<"\n";
                }
            }
            found = true;
        }
        else{
            temp1<<line1<<"\n";
        }
    }
    if(!found){
    	// Notify if no matching record is found.
        std::cout<<"Record not found!"<<"\n";
    }
     // Close all file streams.
    infile1.close();
    infile2.close();
    temp1.close();
    temp2.close();

    // Replace original files with updated temporary files.
    if(remove(filename1.c_str()) != 0){
        std::cerr<<"Error deleting the original file." <<'\n';
    }
    else if(remove(filename2.c_str()) != 0){
        std::cerr<<"Error deleting the original file." <<'\n';
    }
    else if(rename("Temp1.txt", filename1.c_str()) != 0){
        std::cerr<<"Error renaming the temporary file."<<'\n';
    }
    else if(rename("Temp2.txt", filename2.c_str()) != 0){
        std::cerr<<"Error renaming the temporary file."<<'\n';
    }
    else{
        std::cout<<"Record updated successfully!"<<'\n';
    }
}
  // Function to search records
int searchRecord(std::string user, std::string pass){
 
    std::ifstream infile1;
    infile1.open("Customer.txt");
    std::ifstream infile2;
    infile2.open("Account.txt");
     // Check if files are opened successfully
    if(!infile1.is_open()||!infile2.is_open()){
        std::cerr << "Error: Could not open file.\n";
        return 0;
    }
    
    int recFound=0;    // Variable to track the record's status
    std::string line1, line2;
     // Iterate through each line in the customer file
    while(std::getline(infile1, line1)){
        std::istringstream ss1(line1);
      // Extract customer details from the line
        std::string customerID,password, name, address, phoneNo;
        std::getline(ss1, customerID, '|');
        std::getline(ss1, password, '|');
        std::getline(ss1, name, '|');
        std::getline(ss1, address, '|');
        std::getline(ss1, phoneNo, '|');
          // Check if the customer ID matches the input
        if(user==customerID){
            recFound=1;    // Record found with matching customer ID
            // Check if both customer ID and password match
            if(user==customerID&&pass==password){
                recFound=2;   // Record found with matching credentials
            }
            break;
        }
    }
     // Close the file streams
    infile1.close();
    infile2.close();
    // Return the status of the record search
    return recFound;
}
void transaction(std::string user, int n){
	// Create an instance of BankAccount to store transaction details
    BankAccount b;
    std::string filename2= "Account.txt";
    // Flag to track transaction success
    bool success= true;

    std::ofstream onfile3;
     // Open transaction file for appending new transactions
    onfile3.open("Transaction.txt", std::ios::app);
    std::ifstream infile2;
     // Open account file for reading
    infile2.open("Account.txt");
    std::ofstream temp2;
    // Open a temporary file for updating account records
    temp2.open("Temp2.txt");
    std::string line2;
     // Check if files are opened successfully
    if(!infile2.is_open()||!temp2.is_open()){
        std::cerr << "Error: Could not open file.\n";
        return;
    }
    // Generate a random transaction ID
    srand(time(0));
    b.transactionInfo.transactionID=rand()%9000000+1000000;
     // Set the customer ID for the transaction
    b.transactionInfo.customerID=user;
    // Determine the type of transaction based on the input
    if(n==1){
        b.transactionInfo.transaction_type="Deposit";
    }
    if(n==2){
        b.transactionInfo.transaction_type="Withdraw";
    }
     // Prompt the user to enter transaction details
    std::cout<<"Enter the date of transaction: ";
    std::cin>>b.transactionInfo.transaction_date;
    std::cout<<"Enter The amount to Deposit/Withdraw: ";
    std::cin>>b.transactionInfo.amount;
      // Process each line in the account file
    while(std::getline(infile2, line2)){
        std::istringstream ss2(line2);
         // Extract account details from the line
        std::string accNum, accCustomerID,accType, balance;

        std::getline(ss2, accNum, '|');
        std::getline(ss2, accCustomerID, '|');
        std::getline(ss2, accType, '|');
        std::getline(ss2, balance,'|');
         // Check if the account belongs to the current customer
        if(user==accCustomerID){
           // Convert balance to a float
            float balance_float = std::stof(balance);   
             // Update balance based on the transaction type
            if(n==1){
            	// Deposit
                balance_float+=b.transactionInfo.amount;
            }
            else if(n==2 && b.transactionInfo.amount<=balance_float){
            	// Withdraw
                balance_float-=b.transactionInfo.amount;
            }
            else{
            	// Insufficient funds for withdrawal
                success=false;
            }
            // Write updated account details to the temporary file
            temp2<<accNum<<"|";
            temp2<<accCustomerID<<"|";
            temp2<<accType<<"|";
            temp2<<balance_float<<"|";
        }
        else{
         // Write the original account details to the temporary file
            temp2<<line2<<"\n";
        }
    }
    // If the transaction was successful, log it to the transaction file
    if(success){
        onfile3<<b.transactionInfo.transactionID<<"|";
        onfile3<<b.transactionInfo.customerID<<"|";
        onfile3<<b.transactionInfo.transaction_type<<"|";
        onfile3<<b.transactionInfo.transaction_date<<"|";
        onfile3<<b.transactionInfo.amount<<"|\n";
    }
    else{
    	// Inform user of failure
        std::cout<<"Error! Insufficient Balance.\n";
    }
    onfile3.close();
    infile2.close();
    temp2.close();
     // Remove the original account file and replace it with the updated temporary file
    if(remove(filename2.c_str()) != 0){
        std::cerr<<"Error deleting the original file." <<'\n';
    }
    else if(rename("Temp2.txt", filename2.c_str()) != 0){
        std::cerr<<"Error renaming the temporary file."<<'\n';
    }
    else{
        std::cout<<"Record updated successfully!"<<'\n';
    }
}
// Function for keeping records of transection
void transactionRecord(std::string user){
	// Open the transaction file for reading
    std::ifstream infile3;
    infile3.open("Transaction.txt");
    // Declare a string to store each line from the transaction file
    std::string line3;
    // Print the header for transaction records
    std::cout<<"Transaction ID|Customer ID|Transaction ID|Transaction Type|Amount\n";
     // Iterate through each line in the transaction file
    while(std::getline(infile3,line3)){
  	  // Use istringstream to parse the line into individual fields
        std::istringstream ss3(line3);
        std::string transID, custID, trans_date, trans_type, amount;
      // Extract each field separated by the delimiter '|'
        std::getline(ss3, transID, '|');
        std::getline(ss3, custID, '|');
        std::getline(ss3, trans_date, '|');
        std::getline(ss3, trans_type, '|');
        std::getline(ss3, amount, '|');
     // Check if the transaction belongs to the current user
        if(user==custID){
   	 // Print the transaction details for the user
            std::cout<<transID<<" | "
                     <<custID<<" | "
                     <<trans_date<<" | "
                     <<trans_type<<" | "
                     <<amount<<"\n";
        }
    }
     // Close the transaction file after reading
    infile3.close();
}