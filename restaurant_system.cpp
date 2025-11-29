#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <memory>
#include <ctime>
#include <map>
#include <sstream>

class MenuItem {
private:
    std::string itemId;
    std::string name;
    std::string category;
    std::string description;
    double price;
    int preparationTime; // in minutes
    bool isAvailable;
    std::vector<std::string> ingredients;
    std::vector<std::string> allergens;
    int spiceLevel; // 0-5 scale
    int calories;

public:
    MenuItem(std::string id, std::string n, std::string cat, std::string desc, 
             double p, int prepTime, int spice = 0, int cal = 0)
        : itemId(id), name(n), category(cat), description(desc), price(p),
          preparationTime(prepTime), isAvailable(true), spiceLevel(spice), calories(cal) {}

    void addIngredient(const std::string& ingredient) {
        ingredients.push_back(ingredient);
    }

    void addAllergen(const std::string& allergen) {
        allergens.push_back(allergen);
    }

    void updateAvailability(bool available) {
        isAvailable = available;
    }

    void updatePrice(double newPrice) {
        price = newPrice;
    }

    void displayInfo() const {
        std::cout << "\n=== " << name << " ===" << std::endl;
        std::cout << "ID: " << itemId << " | Category: " << category << std::endl;
        std::cout << "Description: " << description << std::endl;
        std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << std::endl;
        std::cout << "Preparation Time: " << preparationTime << " minutes" << std::endl;
        std::cout << "Status: " << (isAvailable ? "Available" : "Unavailable") << std::endl;
        std::cout << "Spice Level: " << spiceLevel << "/5" << std::endl;
        if (calories > 0) std::cout << "Calories: " << calories << std::endl;
        
        if (!ingredients.empty()) {
            std::cout << "Ingredients: ";
            for (const auto& ing : ingredients) std::cout << ing << ", ";
            std::cout << std::endl;
        }
        
        if (!allergens.empty()) {
            std::cout << "Allergens: ";
            for (const auto& alg : allergens) std::cout << alg << ", ";
            std::cout << std::endl;
        }
    }

    std::string getItemId() const { return itemId; }
    std::string getName() const { return name; }
    std::string getCategory() const { return category; }
    double getPrice() const { return price; }
    int getPreparationTime() const { return preparationTime; }
    bool getAvailability() const { return isAvailable; }
    int getCalories() const { return calories; }
};

class Table {
private:
    int tableNumber;
    int capacity;
    bool isOccupied;
    std::string location;
    std::string specialFeatures; // window, private, outdoor, etc.

public:
    Table(int number, int cap, std::string loc, std::string features = "")
        : tableNumber(number), capacity(cap), isOccupied(false), 
          location(loc), specialFeatures(features) {}

    bool reserveTable() {
        if (!isOccupied) {
            isOccupied = true;
            return true;
        }
        return false;
    }

    void freeTable() {
        isOccupied = false;
    }

    void displayInfo() const {
        std::cout << "\nTable " << tableNumber << std::endl;
        std::cout << "Capacity: " << capacity << " people" << std::endl;
        std::cout << "Location: " << location << std::endl;
        std::cout << "Status: " << (isOccupied ? "Occupied" : "Available") << std::endl;
        if (!specialFeatures.empty()) {
            std::cout << "Features: " << specialFeatures << std::endl;
        }
    }

    int getTableNumber() const { return tableNumber; }
    int getCapacity() const { return capacity; }
    bool getOccupancy() const { return isOccupied; }
    std::string getLocation() const { return location; }
};

class Order {
private:
    std::string orderId;
    int tableNumber;
    std::vector<std::pair<std::string, int>> items; // item ID and quantity
    std::string orderTime;
    std::string status; // pending, cooking, ready, served, paid
    double totalAmount;
    std::string specialInstructions;
    int customerCount;

public:
    Order(std::string id, int table, std::string time, int customers)
        : orderId(id), tableNumber(table), orderTime(time), 
          status("pending"), totalAmount(0.0), customerCount(customers) {}

    void addItem(const std::string& itemId, int quantity, double price) {
        items.push_back({itemId, quantity});
        totalAmount += price * quantity;
    }

    void updateStatus(const std::string& newStatus) {
        status = newStatus;
    }

    void addSpecialInstructions(const std::string& instructions) {
        specialInstructions = instructions;
    }

    void displayInfo() const {
        std::cout << "\n=== Order " << orderId << " ===" << std::endl;
        std::cout << "Table: " << tableNumber << " | Customers: " << customerCount << std::endl;
        std::cout << "Time: " << orderTime << " | Status: " << status << std::endl;
        std::cout << "Total: $" << std::fixed << std::setprecision(2) << totalAmount << std::endl;
        
        if (!specialInstructions.empty()) {
            std::cout << "Special Instructions: " << specialInstructions << std::endl;
        }
        
        std::cout << "Items:" << std::endl;
        for (const auto& item : items) {
            std::cout << "  Item: " << item.first << " - Qty: " << item.second << std::endl;
        }
    }

    std::string getOrderId() const { return orderId; }
    int getTableNumber() const { return tableNumber; }
    std::string getStatus() const { return status; }
    double getTotalAmount() const { return totalAmount; }
    std::vector<std::pair<std::string, int>> getItems() const { return items; }
};

class Reservation {
private:
    std::string reservationId;
    std::string customerName;
    std::string phone;
    int partySize;
    std::string reservationDate;
    std::string reservationTime;
    int tableNumber;
    std::string specialRequests;

public:
    Reservation(std::string id, std::string name, std::string ph, int size,
                std::string date, std::string time, int table)
        : reservationId(id), customerName(name), phone(ph), partySize(size),
          reservationDate(date), reservationTime(time), tableNumber(table) {}

    void addSpecialRequests(const std::string& requests) {
        specialRequests = requests;
    }

    void displayInfo() const {
        std::cout << "\n=== Reservation " << reservationId << " ===" << std::endl;
        std::cout << "Customer: " << customerName << " | Phone: " << phone << std::endl;
        std::cout << "Party Size: " << partySize << " | Table: " << tableNumber << std::endl;
        std::cout << "Date: " << reservationDate << " | Time: " << reservationTime << std::endl;
        if (!specialRequests.empty()) {
            std::cout << "Special Requests: " << specialRequests << std::endl;
        }
    }

    std::string getReservationId() const { return reservationId; }
    std::string getCustomerName() const { return customerName; }
    std::string getReservationDate() const { return reservationDate; }
    std::string getReservationTime() const { return reservationTime; }
    int getTableNumber() const { return tableNumber; }
    int getPartySize() const { return partySize; }
};

class Restaurant {
private:
    std::vector<std::shared_ptr<MenuItem>> menu;
    std::vector<std::shared_ptr<Table>> tables;
    std::vector<std::shared_ptr<Order>> orders;
    std::vector<std::shared_ptr<Reservation>> reservations;
    std::string restaurantName;
    int nextOrderId;
    int nextReservationId;

    std::string generateOrderId() {
        return "ORD" + std::to_string(nextOrderId++);
    }

    std::string generateReservationId() {
        return "RES" + std::to_string(nextReservationId++);
    }

    std::string getCurrentTime() {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << localTime->tm_hour << ":"
           << std::setw(2) << std::setfill('0') << localTime->tm_min;
        return ss.str();
    }

    std::string getCurrentDate() {
        time_t now = time(0);
        tm* localTime = localtime(&now);
        std::stringstream ss;
        ss << (1900 + localTime->tm_year) << "-" 
           << std::setw(2) << std::setfill('0') << (1 + localTime->tm_mon) << "-" 
           << std::setw(2) << std::setfill('0') << localTime->tm_mday;
        return ss.str();
    }

public:
    Restaurant(std::string name) : restaurantName(name), nextOrderId(1001), nextReservationId(2001) {
        initializeMenu();
        initializeTables();
    }

    void initializeMenu() {
        // Appetizers
        auto bruschetta = std::make_shared<MenuItem>("APP001", "Bruschetta", "Appetizer", 
            "Toasted bread topped with tomatoes and basil", 8.99, 10, 1, 180);
        bruschetta->addIngredient("Bread");
        bruschetta->addIngredient("Tomatoes");
        bruschetta->addIngredient("Basil");
        bruschetta->addAllergen("Gluten");
        menu.push_back(bruschetta);

        // Main Courses
        auto steak = std::make_shared<MenuItem>("MAIN001", "Ribeye Steak", "Main Course",
            "12oz ribeye with mashed potatoes", 29.99, 20, 0, 650);
        steak->addIngredient("Beef");
        steak->addIngredient("Potatoes");
        steak->addIngredient("Butter");
        menu.push_back(steak);

        auto pasta = std::make_shared<MenuItem>("MAIN002", "Fettuccine Alfredo", "Main Course",
            "Creamy pasta with parmesan cheese", 16.99, 15, 0, 480);
        pasta->addIngredient("Pasta");
        pasta->addIngredient("Cream");
        pasta->addIngredient("Parmesan");
        pasta->addAllergen("Gluten");
        pasta->addAllergen("Dairy");
        menu.push_back(pasta);

        // Desserts
        auto cheesecake = std::make_shared<MenuItem>("DES001", "New York Cheesecake", "Dessert",
            "Classic cheesecake with berry compote", 7.99, 5, 0, 320);
        cheesecake->addIngredient("Cream Cheese");
        cheesecake->addIngredient("Graham Cracker");
        cheesecake->addIngredient("Berries");
        cheesecake->addAllergen("Gluten");
        cheesecake->addAllergen("Dairy");
        menu.push_back(cheesecake);
    }

    void initializeTables() {
        tables.push_back(std::make_shared<Table>(1, 2, "Window", "Window view"));
        tables.push_back(std::make_shared<Table>(2, 4, "Main Hall", ""));
        tables.push_back(std::make_shared<Table>(3, 6, "Private Room", "Private dining"));
        tables.push_back(std::make_shared<Table>(4, 2, "Patio", "Outdoor seating"));
        tables.push_back(std::make_shared<Table>(5, 8, "Main Hall", "Round table"));
    }

    void displayMenu() {
        std::cout << "\n=== " << restaurantName << " Menu ===" << std::endl;
        std::map<std::string, std::vector<std::shared_ptr<MenuItem>>> categorizedMenu;
        
        for (const auto& item : menu) {
            categorizedMenu[item->getCategory()].push_back(item);
        }

        for (const auto& [category, items] : categorizedMenu) {
            std::cout << "\n--- " << category << " ---" << std::endl;
            for (const auto& item : items) {
                if (item->getAvailability()) {
                    std::cout << item->getItemId() << " - " << std::left << std::setw(25) 
                              << item->getName() << " - $" << std::fixed << std::setprecision(2) 
                              << item->getPrice() << " (" << item->getPreparationTime() << " min)" << std::endl;
                }
            }
        }
    }

    void displayAvailableTables() {
        std::cout << "\n=== Available Tables ===" << std::endl;
        bool found = false;
        for (const auto& table : tables) {
            if (!table->getOccupancy()) {
                table->displayInfo();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No available tables at the moment." << std::endl;
        }
    }

    void makeReservation() {
        std::string name, phone, date, time;
        int partySize;

        std::cout << "\n=== Make Reservation ===" << std::endl;
        std::cin.ignore();
        std::cout << "Customer Name: ";
        std::getline(std::cin, name);
        std::cout << "Phone: ";
        std::getline(std::cin, phone);
        std::cout << "Party Size: ";
        std::cin >> partySize;
        std::cout << "Date (YYYY-MM-DD): ";
        std::cin >> date;
        std::cout << "Time (HH:MM): ";
        std::cin >> time;

        // Find suitable table
        std::shared_ptr<Table> selectedTable = nullptr;
        for (const auto& table : tables) {
            if (!table->getOccupancy() && table->getCapacity() >= partySize) {
                selectedTable = table;
                break;
            }
        }

        if (selectedTable) {
            std::string reservationId = generateReservationId();
            auto reservation = std::make_shared<Reservation>(reservationId, name, phone, partySize, date, time, selectedTable->getTableNumber());
            
            std::cin.ignore();
            std::string requests;
            std::cout << "Special Requests: ";
            std::getline(std::cin, requests);
            if (!requests.empty()) {
                reservation->addSpecialRequests(requests);
            }

            selectedTable->reserveTable();
            reservations.push_back(reservation);
            std::cout << "Reservation confirmed! ID: " << reservationId << std::endl;
        } else {
            std::cout << "No suitable tables available for the requested time." << std::endl;
        }
    }

    void createOrder() {
        int tableNumber;
        std::cout << "\n=== Create New Order ===" << std::endl;
        std::cout << "Table Number: ";
        std::cin >> tableNumber;

        // Check if table exists and is occupied
        auto tableIt = std::find_if(tables.begin(), tables.end(),
            [tableNumber](const std::shared_ptr<Table>& t) {
                return t->getTableNumber() == tableNumber && t->getOccupancy();
            });

        if (tableIt == tables.end()) {
            std::cout << "Table not found or not occupied." << std::endl;
            return;
        }

        int customerCount;
        std::cout << "Number of customers: ";
        std::cin >> customerCount;

        std::string orderId = generateOrderId();
        std::string orderTime = getCurrentTime();
        auto order = std::make_shared<Order>(orderId, tableNumber, orderTime, customerCount);

        bool addingItems = true;
        while (addingItems) {
            displayMenu();
            std::string itemId;
            int quantity;

            std::cout << "Enter Item ID (or 'done' to finish): ";
            std::cin >> itemId;

            if (itemId == "done") {
                addingItems = false;
                continue;
            }

            auto itemIt = std::find_if(menu.begin(), menu.end(),
                [&itemId](const std::shared_ptr<MenuItem>& m) {
                    return m->getItemId() == itemId && m->getAvailability();
                });

            if (itemIt == menu.end()) {
                std::cout << "Item not found or unavailable." << std::endl;
                continue;
            }

            std::cout << "Quantity: ";
            std::cin >> quantity;

            order->addItem(itemId, quantity, (*itemIt)->getPrice());
            std::cout << "Added " << quantity << " x " << (*itemIt)->getName() << std::endl;
        }

        std::cin.ignore();
        std::string instructions;
        std::cout << "Special Instructions: ";
        std::getline(std::cin, instructions);
        if (!instructions.empty()) {
            order->addSpecialInstructions(instructions);
        }

        orders.push_back(order);
        std::cout << "Order created successfully! Order ID: " << orderId << std::endl;
        std::cout << "Total Amount: $" << order->getTotalAmount() << std::endl;
    }

    void updateOrderStatus() {
        std::string orderId;
        std::cout << "Enter Order ID: ";
        std::cin >> orderId;

        auto orderIt = std::find_if(orders.begin(), orders.end(),
            [&orderId](const std::shared_ptr<Order>& o) {
                return o->getOrderId() == orderId;
            });

        if (orderIt != orders.end()) {
            std::cout << "Current status: " << (*orderIt)->getStatus() << std::endl;
            std::cout << "New status (pending/cooking/ready/served/paid): ";
            std::string newStatus;
            std::cin >> newStatus;
            (*orderIt)->updateStatus(newStatus);
            
            if (newStatus == "paid") {
                // Free the table
                auto tableIt = std::find_if(tables.begin(), tables.end(),
                    [orderIt](const std::shared_ptr<Table>& t) {
                        return t->getTableNumber() == (*orderIt)->getTableNumber();
                    });
                if (tableIt != tables.end()) {
                    (*tableIt)->freeTable();
                }
            }
            
            std::cout << "Order status updated!" << std::endl;
        } else {
            std::cout << "Order not found!" << std::endl;
        }
    }

    void displayActiveOrders() {
        std::cout << "\n=== Active Orders ===" << std::endl;
        bool found = false;
        for (const auto& order : orders) {
            if (order->getStatus() != "paid") {
                order->displayInfo();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No active orders." << std::endl;
        }
    }

    void displayTodayReservations() {
        std::string today = getCurrentDate();
        std::cout << "\n=== Reservations for " << today << " ===" << std::endl;
        bool found = false;
        for (const auto& reservation : reservations) {
            if (reservation->getReservationDate() == today) {
                reservation->displayInfo();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No reservations for today." << std::endl;
        }
    }

    void generateDailyReport() {
        std::string today = getCurrentDate();
        double totalRevenue = 0.0;
        int ordersCompleted = 0;
        int customersServed = 0;

        for (const auto& order : orders) {
            if (order->getStatus() == "paid") {
                totalRevenue += order->getTotalAmount();
                ordersCompleted++;
                // Estimate customers from order (simplified)
                customersServed += order->getItems().size();
            }
        }

        std::cout << "\n=== Daily Report - " << today << " ===" << std::endl;
        std::cout << "Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << std::endl;
        std::cout << "Orders Completed: " << ordersCompleted << std::endl;
        std::cout << "Estimated Customers Served: " << customersServed << std::endl;
        std::cout << "Average Order Value: $" << (ordersCompleted > 0 ? totalRevenue / ordersCompleted : 0) << std::endl;
    }

    void displayMenu() {
        std::cout << "\n=== " << restaurantName << " Management System ===" << std::endl;
        std::cout << "1. Display Menu" << std::endl;
        std::cout << "2. Display Available Tables" << std::endl;
        std::cout << "3. Make Reservation" << std::endl;
        std::cout << "4. Create Order" << std::endl;
        std::cout << "5. Update Order Status" << std::endl;
        std::cout << "6. Display Active Orders" << std::endl;
        std::cout << "7. Display Today's Reservations" << std::endl;
        std::cout << "8. Generate Daily Report" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
    }
};

int main() {
    Restaurant restaurant("Bella Cucina");
    
    int choice;
    do {
        restaurant.displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                restaurant.displayMenu();
                break;
            case 2:
                restaurant.displayAvailableTables();
                break;
            case 3:
                restaurant.makeReservation();
                break;
            case 4:
                restaurant.createOrder();
                break;
            case 5:
                restaurant.updateOrderStatus();
                break;
            case 6:
                restaurant.displayActiveOrders();
                break;
            case 7:
                restaurant.displayTodayReservations();
                break;
            case 8:
                restaurant.generateDailyReport();
                break;
            case 0:
                std::cout << "Thank you for using Restaurant Management System!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
