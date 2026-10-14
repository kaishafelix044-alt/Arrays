#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace {

const int kCapacity = 10;

bool read_integer(const std::string &prompt, int &value)
{
    std::string line;

    for (;;) {
        std::cout << prompt;
        if (!std::getline(std::cin, line)) {
            return false;
        }

        std::istringstream input(line);
        long long parsed;
        std::string extra;
        if (!(input >> parsed) || (input >> extra) ||
            parsed < std::numeric_limits<int>::min() ||
            parsed > std::numeric_limits<int>::max()) {
            std::cout << "Invalid input. Please enter one integer.\n";
            continue;
        }

        value = static_cast<int>(parsed);
        return true;
    }
}

void traverse(const int values[], int count)
{
    if (count == 0) {
        std::cout << "Array is empty.\n";
        return;
    }

    std::cout << "Array:";
    for (int i = 0; i < count; ++i) {
        std::cout << ' ' << values[i];
    }
    std::cout << '\n';
}

void insert_value(int values[], int &count)
{
    if (count == kCapacity) {
        std::cout << "Array is full; insertion is not possible.\n";
        return;
    }

    int position;
    int value;
    if (!read_integer("Position to insert (1-based): ", position)) {
        return;
    }
    if (position < 1 || position > count + 1) {
        std::cout << "Position must be between 1 and " << count + 1 << ".\n";
        return;
    }
    if (!read_integer("Value: ", value)) {
        return;
    }

    for (int i = count; i >= position; --i) {
        values[i] = values[i - 1];
    }
    values[position - 1] = value;
    ++count;
    std::cout << "Value inserted.\n";
}

void delete_value(int values[], int &count)
{
    if (count == 0) {
        std::cout << "Array is empty; nothing to delete.\n";
        return;
    }

    int position;
    if (!read_integer("Position to delete (1-based): ", position)) {
        return;
    }
    if (position < 1 || position > count) {
        std::cout << "Position must be between 1 and " << count << ".\n";
        return;
    }

    std::cout << "Deleted " << values[position - 1] << ".\n";
    for (int i = position - 1; i < count - 1; ++i) {
        values[i] = values[i + 1];
    }
    --count;
}

void update_value(int values[], int count)
{
    if (count == 0) {
        std::cout << "Array is empty; nothing to update.\n";
        return;
    }

    int position;
    int value;
    if (!read_integer("Position to update (1-based): ", position)) {
        return;
    }
    if (position < 1 || position > count) {
        std::cout << "Position must be between 1 and " << count << ".\n";
        return;
    }
    if (!read_integer("New value: ", value)) {
        return;
    }

    values[position - 1] = value;
    std::cout << "Value updated.\n";
}

void search_value(const int values[], int count)
{
    int target;
    if (!read_integer("Value to search for: ", target)) {
        return;
    }

    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (values[i] == target) {
            std::cout << "Found at position " << i + 1 << ".\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Value not found.\n";
    }
}

} // namespace

int main()
{
    int values[kCapacity] = {10, 15, 20, 25};
    int count = 4;

    for (;;) {
        int choice;
        std::cout << "\nArray operations (capacity " << kCapacity << ")\n";
        std::cout << "1. Traverse\n2. Insert\n3. Delete\n4. Update\n";
        std::cout << "5. Search\n0. Exit\n";
        if (!read_integer("Choose an option: ", choice)) {
            std::cout << "\nExiting.\n";
            break;
        }

        switch (choice) {
        case 1:
            traverse(values, count);
            break;
        case 2:
            insert_value(values, count);
            break;
        case 3:
            delete_value(values, count);
            break;
        case 4:
            update_value(values, count);
            break;
        case 5:
            search_value(values, count);
            break;
        case 0:
            return 0;
        default:
            std::cout << "Choose one of the listed options.\n";
        }
    }

    return 0;
}
