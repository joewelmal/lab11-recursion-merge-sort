
/*
 * Course: COEN 2220 - Programming 2
 * Name: [Joewel Maldonado]
 * Lab: Lab 11 - Recursion and Merge Sort
 * Description: Project Application - Delivery Order View
 * Due date: [November 3 2026]
 */

#include <iostream>
#include <string>
using namespace std;

struct OrderPreview
{
    int orderId;
    string orderType;
    string status;
    string building;
    int priority;
};

int main()
{
    const int ORDER_COUNT = 4;

    OrderPreview orders[ORDER_COUNT] =
    {
        {101, "DELIVERY", "PENDING", "Engineering", 2},
        {102, "DINE_IN", "PENDING", "Cafeteria", 1},
        {103, "DELIVERY", "IN_PROGRESS", "Library", 3},
        {104, "DELIVERY", "COMPLETED", "Science", 1}
    };

    OrderPreview *view[ORDER_COUNT];
    int viewCount = 0;

    // Create a temporary view with active DELIVERY orders.
    for (int index = 0; index < ORDER_COUNT; index++)
    {
        if (orders[index].orderType == "DELIVERY" &&
            (orders[index].status == "PENDING" ||
             orders[index].status == "IN_PROGRESS"))
        {
            view[viewCount] = &orders[index];
            viewCount++;
        }
    }

    // Display the filtered delivery report.
    cout << "Active DELIVERY Orders:" << endl;

    for (int index = 0; index < viewCount; index++)
    {
        cout << "Order ID: " << view[index]->orderId
             << " | Type: " << view[index]->orderType
             << " | Status: " << view[index]->status
             << " | Building: " << view[index]->building
             << " | Priority: " << view[index]->priority
             << endl;
    }

    // Display the original orders to verify their order.
    cout << endl;
    cout << "Original Orders:" << endl;

    for (int index = 0; index < ORDER_COUNT; index++)
    {
        cout << "Order ID: " << orders[index].orderId
             << " | Type: " << orders[index].orderType
             << " | Status: " << orders[index].status
             << endl;
    }

    return 0;
}
