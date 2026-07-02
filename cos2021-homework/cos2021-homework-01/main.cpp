#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <iomanip>

using namespace std;

// Enumeration for the discount type options - amount and percentage
enum DiscountType {
    amount,
    percentage
};

// Vector that will be used to ensure text keys are unique
vector<string> allTextKeys;

// Function to ensure key uniqueness and add new keys
void CheckTextKeyUniqueness(const string& textKey) {
    // Ensure that the key to add is unique
    assert(find(allTextKeys.begin(), allTextKeys.end(), textKey) == allTextKeys.end() && "Text key must be unique!");

    // Add current key to the vector with all keys
    allTextKeys.push_back(textKey);
}

class Category
{
public:
    // Default constructor
    Category() : textKey(""), name(""), description(""), parent(nullptr) {
        CheckTextKeyUniqueness("");
    }

    // Partial constructor
    Category(const string& textKey, const string& name) : textKey(textKey), name(name), description(""), parent(nullptr) {
        CheckTextKeyUniqueness(textKey);
    }

    // Full constructor
    Category(const string& textKey, const string& name, const string& description, Category* parent) : textKey(textKey), name(name), description(description), parent(parent) {
        CheckTextKeyUniqueness(textKey);
    }

    // Getters and setters for data members

    string GetTextKey() const {
        return textKey;
    }

    void SetTextKey(const string& newTextKey) {
        // Remove old text key from the vector
        auto oldKey = find(allTextKeys.begin(), allTextKeys.end(), textKey);
        allTextKeys.erase(oldKey);

        CheckTextKeyUniqueness(newTextKey);

        // Set new text key once ensured it is unique
        textKey = newTextKey;
    }

    string GetName() const {
        return name;
    }

    void SetName(const string& newName) {
        name = newName;
    }

    string GetDescription() const {
        return description;
    }

    void SetDescription(const string& newDescription) {
        description = newDescription;
    }

    Category* GetParent() const {
        return parent;
    }

    void SetParent(Category* newParent) {
        parent = newParent;
    }

// Data members
private:
    string textKey;
    string name;
    string description;
    Category* parent;
};

class Product
{
public:
    // Default constructor
    Product() : textKey(""), name(""), description(""), category(new Category()), price(0.0), discount(0.0), discountType(amount), quantity(0) {}

    // Partial constructor
    Product(const string& textKey, const string& name, double price, int quantity) : textKey(textKey), name(name), description(""), category(new Category()), price(price), discount(0.0), discountType(amount), quantity(quantity) {
        // Ensure the price and quantity are non-negative
        assert(price >= 0 && quantity >= 0);
    }

    // Full constructor
    Product(const string& textKey, const string& name, const string& description, Category* category, double price, double discount, DiscountType discountType, int quantity) : textKey(textKey), name(name), description(description), category(category), price(price), discount(discount), discountType(discountType), quantity(quantity) {
        // Ensure price, discount, and quantity are non-negative + category is not empty
        assert(price >= 0 && discount >= 0 && quantity >= 0);
        assert(category != nullptr && "Category is required.");
    }

    // Getters and setters

    string GetTextKey() const {
        return textKey;
    }

    void SetTextKey(const string& newTextKey) {
        textKey = newTextKey;
    }

    string GetName() const {
        return name;
    }

    void SetName(const string& newName) {
        name = newName;
    }

    string GetDescription() const {
        return description;
    }

    void SetDescription(const string& newDescription) {
        description = newDescription;
    }

    Category* GetCategory() const {
        return category;
    }

    void SetCategory(Category* newCategory) {
        category = newCategory;
    }

    double GetPrice() const {
        return price;
    }

    void SetPrice(double newPrice) {
        assert(newPrice >= 0);
        price = newPrice;
    }

    double GetDiscount() const {
        return discount;
    }

    void SetDiscount(double newDiscount) {
        assert(newDiscount >= 0);
        discount = newDiscount;
    }

    DiscountType GetDiscountType() const {
        return discountType;
    }

    void SetDiscountType(DiscountType newDiscountType) {
        discountType = newDiscountType;
    }

    int GetQuantity() const {
        return quantity;
    }

    void SetQuantity(int newQuantity) {
        assert(newQuantity >= 0);
        quantity = newQuantity;
    }

    // Method for calculating the effective cost based on the discount type
    double GetEffectivePrice() {
        double effectivePrice = 0.0;

        if (discountType == amount)
            effectivePrice = price - discount;
        else
            effectivePrice = price - price * (discount / 100);

        assert(effectivePrice >= 0);
        return effectivePrice;
    };

    // Method for calculating the total cost of the product
    virtual double GetTotalPrice() {
        double totalPrice = quantity * GetEffectivePrice();

        assert(totalPrice >= 0);
        return totalPrice;
    }

// Data members
private:
    string textKey;
    string name;
    string description;
    Category* category;
    double price;
    double discount;
    DiscountType discountType;
    int quantity;
};

// Class Service inherits from Product
class Service : public Product
{
public:
    // Default constructor
    Service() : Product(), duration(0.0), rate(0.0), rateDiscount(0.0), rateDiscountType(amount) {}

    // Partial constructor
    Service(const string& textKey, const string& name, const string& description, Category* category, double price, double discount, DiscountType discountType, int quantity, double duration, double rate) : Product(textKey, name, description, category, price, discount, discountType, quantity), duration(duration), rate(rate), rateDiscount(0.0), rateDiscountType(amount) {
        assert(duration >= 0 && rate >= 0);
    }

    // Full constructor
    Service(const string& textKey, const string& name, const string& description, Category* category, double price, double discount, DiscountType discountType, int quantity, double duration, double rate, double rateDiscount, DiscountType rateDiscountType) : Product(textKey, name, description, category, price, discount, discountType, quantity), duration(duration), rate(rate), rateDiscount(rateDiscount), rateDiscountType(rateDiscountType) {
        assert(duration >= 0 && rate >= 0 && rateDiscount >= 0);
    }

    // Getters and setters

    double GetDuration() const {
        return duration;
    }

    void SetDuration(double newDuration) {
        assert(newDuration >= 0);
        duration = newDuration;
    }

    double GetRate() const {
        return rate;
    }

    void SetRate(double newRate) {
        assert(newRate >= 0);
        rate = newRate;
    }

    double GetRateDiscount() const {
        return rateDiscount;
    }

    void SetRateDiscount(double newRateDiscount) {
        assert(newRateDiscount >= 0);
        rateDiscount = newRateDiscount;
    }

    DiscountType GetRateDiscountType() const {
        return rateDiscountType;
    }

    void SetRateDiscountType(DiscountType newRateDiscountType) {
        rateDiscountType = newRateDiscountType;
    }

    // Method for calculating the effective rate based on the discount type
    double GetEffectiveRate() {
        double effectiveRate = 0.0;

        if (rateDiscountType == amount)
            effectiveRate = rate - rateDiscount;
        else
            effectiveRate = rate - rate * (rateDiscount / 100);

        assert(effectiveRate >= 0);
        return effectiveRate;
    }

    // Overriding method for calculating the total price
    double GetTotalPrice() {
        double totalPrice = Product::GetTotalPrice() + GetEffectiveRate() * duration;

        assert(totalPrice >= 0);
        return totalPrice;
    }

// Data members
private:
    double duration;
    double rate;
    double rateDiscount;
    DiscountType rateDiscountType;
};

// Main method (entry point)
int main()
{
    // Declaration of vectors with pointers to categories, products, and services
    vector<Category*> categories;
    vector<Product*> products;
    vector<Service*> services;

    // Adding data to the vectors
    categories.push_back(new Category("ABCD-EFGH-1234", "Electronics", "Electronic devices", nullptr));
    categories.push_back(new Category("DBCA-HGFE-4321", "Clothes", "Male, female and kids clothes", nullptr));
    categories.push_back(new Category("HDSQ-1234-DFOL", "For Home", "Everything for your home", nullptr));

    products.push_back(new Product("ASD-234-SDF", "Apple Macbook", "Macbook 16 inch 256 GB M3 chip", categories[0], 4399.99, 20, percentage, 2));
    products.push_back(new Product("JSD-724-POI", "Apple iPad", "iPad pro 12 for digital artists", categories[0], 1239.99, 10, amount, 3));
    products.push_back(new Product("KRQ-FHW-357", "Yellow Dress", "Beautiful summer yellow dress", categories[1], 29.99, 30, percentage, 1));

    services.push_back(new Service("KRH-234-ASD", "Window Cleaning", "Fast and spotless window cleaning for your home", categories[2], 39.99, 10, amount, 3, 1.5,  20.50, 3.5, amount));
    services.push_back(new Service("LWE-234-FGW", "Clothes Washing", "Fast and spotless machine clothes washing", categories[1], 19.99, 24, percentage, 3, 2.5,  15.50, 2.5, percentage));
    services.push_back(new Service("ASD-543-KJH", "Technical Support", "Assistance with all your electronic devices", categories[0], 49.99, 5, amount, 5, 5,  50, 5, amount));

    // Printing the name and total price of all products
    for (int i = 0; i < products.size(); i++) {
        string name = products[i]->GetName();
        double totalPrice = products[i]->GetTotalPrice();

        cout << "Name: " << name << endl;
        cout << "Total price: " << fixed << setprecision(2) << totalPrice << endl;
        cout << "------------------" << endl;
    }

    // Printing the name and total price of all services
    for (int i = 0; i < services.size(); i++) {
        string name = services[i]->GetName();
        double totalPrice = services[i]->GetTotalPrice();

        cout << "Name: " << name << endl;
        cout << "Total price: " << fixed << setprecision(2) <<totalPrice << endl;
        cout << "------------------" << endl;
    }

    return 0;
}