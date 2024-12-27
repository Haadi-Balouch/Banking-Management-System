# Banking System Application

This project implements a simple command-line banking system for managing customer accounts, transactions, and records. It supports functionalities like adding, deleting, updating customer details, performing deposits and withdrawals, and viewing transaction records.

---

## Features

- **Customer Management**
  - Add new customer records.
  - Search for existing customers by ID or credentials.
  - Delete customers and their associated accounts.

- **Account Management**
  - Create and maintain accounts linked to customers.
  - Update account balances based on transactions.

- **Transactions**
  - Deposit or withdraw money from accounts.
  - Log all transactions in a separate file.
  - View transaction history for individual customers.

- **File-Based Data Storage**
  - Customer details are stored in `Customer.txt`.
  - Account details are stored in `Account.txt`.
  - Transactions are logged in `Transaction.txt`.

---

## File Structure

| File            | Description                                   |
|-----------------|-----------------------------------------------|
| `Customer.txt`  | Stores customer details: ID, password, name, address, and phone number. |
| `Account.txt`   | Stores account details: Account number, customer ID, account type, and balance. |
| `Transaction.txt` | Logs transaction details: Transaction ID, customer ID, transaction type, date, and amount. |

---

## Code Details

### Functions Overview

1. **`deleteRecord()`**
   - Deletes a customer record and associated accounts by Customer ID.
   - Updates `Customer.txt` and `Account.txt` accordingly.

2. **`searchRecord(user, pass)`**
   - Searches for a customer record by ID and password.
   - Returns a status indicating whether the record exists.

3. **`transaction(user, n)`**
   - Handles deposits or withdrawals for a customer account.
   - Updates account balances and logs the transaction.

4. **`transactionRecord(user)`**
   - Displays the transaction history for a specific customer.

### Key Components
- **File Handling**: Temporary files are used to safely update records without data loss.
- **Error Handling**: Ensures operations like file opening, reading, and writing are verified for success.
- **User Input Validation**: Validates input for transaction amounts and user credentials.

---

## How to Run the Program

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Banking-System.git
   cd Banking-System
