#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Contact {
    std::string name;
    std::string phoneNumber;
};

class Phonebook {
private:
    std::vector<Contact> contacts;

public:
    bool isDuplicate(const Contact& contact) {
        for (const auto& existingContact : contacts) {
            if (existingContact.name == contact.name || existingContact.phoneNumber == contact.phoneNumber) {
                return true;
            }
        }
        return false;
    }

    void addContact(const Contact& contact) {
        if (isDuplicate(contact)) {
            std::cout << "Contact with the same name or phone number already exists." << std::endl;
        } 
        else {
            contacts.push_back(contact);
            std::cout << "Contact added successfully!" << std::endl;
        }
    }

    void viewContacts() {
        if (contacts.empty()) {
            std::cout << "Phonebook is empty." << std::endl;
            return;
        }

        std::cout << "Contacts in the Phonebook:" << std::endl;
        for (const auto& contact : contacts) {
            std::cout << "Name: " << contact.name << ", Phone Number: " << contact.phoneNumber << std::endl;
        }
    }

    void searchContact(const std::string& query) {
        std::cout << "Search Results:" << std::endl;
        for (const auto& contact : contacts) {
            if (contact.name.find(query) != std::string::npos ||
                contact.phoneNumber.find(query) != std::string::npos) {
                std::cout << "Name: " << contact.name << ", Phone Number: " << contact.phoneNumber << std::endl;
            }
        }
    }

    void saveContactsToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Error: Unable to open file for writing." << std::endl;
            return;
        }

        for (const auto& contact : contacts) {
            outFile << contact.name << "," << contact.phoneNumber << std::endl;
        }

        outFile.close();
        std::cout << "Contacts saved to file: " << filename << std::endl;
    }

    void loadContactsFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cerr << "Error: Unable to open file for reading." << std::endl;
            return;
        }

        contacts.clear();
        std::string line;
        while (std::getline(inFile, line)) {
            std::istringstream iss(line);
            std::string name, phoneNumber;

            // Split the line by comma and extract name and phone number
            if (std::getline(iss, name, ',') && std::getline(iss, phoneNumber)) {
                Contact contact = {name, phoneNumber};
                contacts.push_back(contact);
            }
        }

        inFile.close();
        std::cout << "Contacts loaded from file: " << filename << std::endl;
    }
};

int main() {
    Phonebook phonebook;

    // Load contacts from file if it exists
    phonebook.loadContactsFromFile("phonebook.txt");

    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Add Contact" << std::endl;
        std::cout << "2. View Contacts" << std::endl;
        std::cout << "3. Search Contact" << std::endl;
        std::cout << "4. Save Contacts" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string name, phoneNumber;
            std::cout << "Enter Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Enter Phone Number: ";
            std::getline(std::cin, phoneNumber);

            Contact newContact = {name, phoneNumber};
            phonebook.addContact(newContact);
        } else if (choice == 2) {
            phonebook.viewContacts();
        } else if (choice == 3) {
            std::string query;
            std::cout << "Enter search query: ";
            std::cin.ignore();
            std::getline(std::cin, query);

            phonebook.searchContact(query);
        } else if (choice == 4) {
            phonebook.saveContactsToFile("phonebook.txt");
        } else if (choice == 5) {
            // Save contacts to file before exiting
            phonebook.saveContactsToFile("phonebook.txt");
            std::cout << "Exiting Phonebook application." << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
