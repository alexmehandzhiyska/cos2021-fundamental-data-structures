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

// Abstract class Item
class Item
{
public:
    // Pure virtual (abstract) method for calculating the total price
    virtual double GetTotalPrice() const = 0;

    // Overloading the less than operator to compare items
    bool operator<(const Item& otherItem) const {
        return this->GetTotalPrice() < otherItem.GetTotalPrice();
    }
};

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

class Product : public Item
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
    double GetEffectivePrice() const {
        double effectivePrice = 0.0;

        if (discountType == amount)
            effectivePrice = price - discount;
        else
            effectivePrice = price - price * (discount / 100);

        assert(effectivePrice >= 0);
        return effectivePrice;
    };

    // Method for calculating the total cost of the product
     virtual double GetTotalPrice() const override  {
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
    double GetEffectiveRate() const {
        double effectiveRate = 0.0;

        if (rateDiscountType == amount)
            effectiveRate = rate - rateDiscount;
        else
            effectiveRate = rate - rate * (rateDiscount / 100);

        assert(effectiveRate >= 0);
        return effectiveRate;
    }

    // Overriding method for calculating the total price
    double GetTotalPrice() const override {
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

// Forward declaration of the version that takes the full range
void quicksort(vector<Item*>& items, int low, int high);

// Define insertionSort before quicksort
void insertionSort(vector<Item*>& a, int low, int high) {
    for (int p = low + 1; p <= high; ++p) {
        Item* temp = a[p];
        int j;
        for (j = p; j > low && *temp < *a[j - 1]; --j) {
            a[j] = a[j - 1];
        }
        a[j] = temp;
    }
}

// Now define quicksort, with insertionSort available
void quicksort(vector<Item*>& items, int low, int high) {
    // Call insertion sort for small subarrays
    if (low + 10 > high) {
        insertionSort(items, low, high);  // Use the correct insertionSort function
    } else {
        int middle = (low + high) / 2;   // Sort low, middle, high
        if (*items[middle] < *items[low]) swap(items[low], items[middle]);
        if (*items[high] < *items[low]) swap(items[low], items[high]);
        if (*items[high] < *items[middle]) swap(items[middle], items[high]);

        auto pivot = items[middle];
        swap(items[middle], items[high - 1]);

        // Begin partitioning
        int i = low, j = high - 1;
        for (;;) {
            while (*items[++i] < *pivot) {}
            while (*pivot < *items[--j]) {}

            if (i < j) {
                swap(items[i], items[j]);
            } else {
                break;
            }
        }
        swap(items[i], items[high - 1]);    // Restore the pivot

        quicksort(items, low, i - 1);   // Sort small elements
        quicksort(items, i + 1, high);  // Sort large elements
    }
}

// Then define the quicksort that only takes the vector
void quicksort(vector<Item*>& a) {
    quicksort(a, 0, a.size() - 1);  // Call the full version
}


// Main method (entry point)
int main()
{
    // Declaration of vectors with pointers to categories, products, and services
    vector<Category*> categories;
    vector<Item*> items;

    // Adding data to the vectors
    categories.push_back(new Category("ABCD-EFGH-1234", "Electronics", "Electronic devices", nullptr));
    categories.push_back(new Category("DBCA-HGFE-4321", "Clothes", "Male, female and kids clothes", nullptr));
    categories.push_back(new Category("HDSQ-1234-DFOL", "For Home", "Everything for your home", nullptr));

    items.push_back(new Product("ASD-234-SDF", "Apple Macbook", "Macbook 16 inch 256 GB M3 chip", categories[0], 4399.99, 20, percentage, 2));
    items.push_back(new Product("JSD-724-POI", "Apple iPad", "iPad pro 12 for digital artists", categories[0], 1239.99, 10, amount, 3));
    items.push_back(new Product("KRQ-FHW-357", "Yellow Dress", "Beautiful summer yellow dress", categories[1], 29.99, 30, percentage, 1));

    items.push_back(new Service("KRH-234-ASD", "Window Cleaning", "Fast and spotless window cleaning for your home", categories[2], 39.99, 10, amount, 3, 1.5,  20.50, 3.5, amount));
    items.push_back(new Service("LWE-234-FGW", "Clothes Washing", "Fast and spotless machine clothes washing", categories[1], 19.99, 24, percentage, 3, 2.5,  15.50, 2.5, percentage));
    items.push_back(new Service("ASD-543-KJH", "Technical Support", "Assistance with all your electronic devices", categories[0], 49.99, 5, amount, 5, 5,  50, 5, amount));

    quicksort(items);

    // Printing the name and total price of all items
    for (int i = 0; i < items.size(); i++) {
        double totalPrice = items[i]->GetTotalPrice();
        cout << "Total price: " << fixed << setprecision(2) << totalPrice << endl;
        cout << "------------------" << endl;
    }

    return 0;
}