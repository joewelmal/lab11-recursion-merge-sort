
/*
 * Course: COEN 2220 - Programming 2
 * Name: [Joewel Maldonado]
 * Lab: Lab 11 - Recursion and Merge Sort
 * Description: Practice - sort a temporary view without changing original tasks
 * Due date: [November 3 2026]
 */

#include <iostream>
#include <string>
using namespace std;

struct RepairTask
{
    string taskId;     // Preserve the identity of the original task.
    int daysUntilDue;  // Smaller values must appear first in the report.
    int minutesNeeded; // Break equal-deadline ties with smaller durations first.
};

bool comesBeforeOrEqual(const RepairTask *left, const RepairTask *right);
void mergeTaskView(RepairTask *view[], RepairTask *temporary[],
                   int first, int middle, int last);
void mergeSortView(RepairTask *view[], RepairTask *temporary[], int first, int last);
void displayOriginal(const RepairTask tasks[], int count);
void displayView(RepairTask *view[], int count);

int main()
{
    const int TASK_COUNT = 8;
    RepairTask tasks[TASK_COUNT] =
    {
        {"RT-101", 3, 30}, {"RT-102", 1, 20},
        {"RT-103", 2, 15}, {"RT-104", 1, 10},
        {"RT-105", 2, 15}, {"RT-106", 3, 10},
        {"RT-107", 1, 20}, {"RT-108", 2, 5}
    };
    RepairTask *view[TASK_COUNT];      // Borrow addresses of existing tasks.
    RepairTask *temporary[TASK_COUNT]; // Hold addresses while merging the view.
    for (int index = 0; index < TASK_COUNT; index++)
    {
        view[index] = &tasks[index]; // Preserve arrival order in the initial view.
    }

    cout << boolalpha;
    cout << "Original arrival order:" << endl;
    displayOriginal(tasks, TASK_COUNT);

    // ===== Resolve these TODOs now (Part C) =====
    // TODO (Part C): Activate the C test block after completing the comparator.

    cout << "Earlier deadline first: "
         << comesBeforeOrEqual(&tasks[1], &tasks[0]) << endl;
    cout << "Shorter duration within same deadline: "
         << comesBeforeOrEqual(&tasks[3], &tasks[1]) << endl;
    cout << "Exact tie keeps left: "
         << comesBeforeOrEqual(&tasks[2], &tasks[4]) << endl;
    cout << "Later deadline first: "
         << comesBeforeOrEqual(&tasks[0], &tasks[1]) << endl;

    // ===== Resolve these TODOs later (Part D) =====
    // TODO (Part D): Call mergeSortView for the complete logical range.
    mergeSortView(view, temporary, 0, TASK_COUNT - 1);

    // TODO (Part D): Display the sorted view with a descriptive heading.
    cout << "Sorted task view:" << endl;
    displayView(view, TASK_COUNT);

    // TODO (Part D): Display tasks again to prove that arrival order did not change.
    cout << "Original arrival order after sorting:" << endl;
    displayOriginal(tasks, TASK_COUNT);

    // Test empty and single-element ranges.
    mergeSortView(view, temporary, 0, -1);
    mergeSortView(view, temporary, 0, 0);

    // Test sorting an already sorted view.
    mergeSortView(view, temporary, 0, TASK_COUNT - 1);

    cout << "Sorted view after repeating merge sort:" << endl;
    displayView(view, TASK_COUNT);

    return 0;
}

bool comesBeforeOrEqual(const RepairTask *left, const RepairTask *right)
{
    // ===== Resolve this TODO now (Part C) =====
    // TODO (Part C): Implement the specified two-field order, including exact ties.

    if (left->daysUntilDue < right->daysUntilDue)
    {
        return true;
    }

    if (left->daysUntilDue > right->daysUntilDue)
    {
        return false;
    }

    return left->minutesNeeded <= right->minutesNeeded;
}

// ===== Resolve these TODOs later (Part D) =====
void mergeSortView(RepairTask *view[], RepairTask *temporary[], int first, int last)
{
    // TODO (Part D): Implement recursive merge sort using inclusive indices.

    if (first >= last)
    {
        return;
    }

    int middle = first + (last - first) / 2;

    mergeSortView(view, temporary, first, middle);
    mergeSortView(view, temporary, middle + 1, last);

    mergeTaskView(view, temporary, first, middle, last);
}

void mergeTaskView(RepairTask *view[], RepairTask *temporary[],
                   int first, int middle, int last)
{
    // TODO (Part D): Merge two sorted segments using comesBeforeOrEqual.
    int leftIndex = first;
    int rightIndex = middle + 1;
    int tempIndex = first;

    while (leftIndex <= middle && rightIndex <= last)
    {
        if (comesBeforeOrEqual(view[leftIndex], view[rightIndex]))
        {
            temporary[tempIndex] = view[leftIndex];
            leftIndex++;
        }
        else
        {
            temporary[tempIndex] = view[rightIndex];
            rightIndex++;
        }

        tempIndex++;
    }

    // TODO (Part D): Preserve pending pointers and copy the merged segment back.
    while (leftIndex <= middle)
    {
        temporary[tempIndex] = view[leftIndex];
        leftIndex++;
        tempIndex++;
    }

    while (rightIndex <= last)
    {
        temporary[tempIndex] = view[rightIndex];
        rightIndex++;
        tempIndex++;
    }

    for (int index = first; index <= last; index++)
    {
        view[index] = temporary[index];
    }
}

void displayOriginal(const RepairTask tasks[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Task: " << tasks[index].taskId
             << " | Days until due: " << tasks[index].daysUntilDue
             << " | Minutes: " << tasks[index].minutesNeeded << endl;
    }
}

void displayView(RepairTask *view[], int count)
{
    for (int index = 0; index < count; index++)
    {
        cout << "Task: " << view[index]->taskId
             << " | Days until due: " << view[index]->daysUntilDue
             << " | Minutes: " << view[index]->minutesNeeded << endl;
    }
}

/*
 * Analysis Answers
 *
 * C5 - Two-field decision
 * Explain the result for RT-103 compared with RT-108. Which field decides it?
 * Answer:
 * RT-103 and RT-108 both have 2 days until due.
 * The minutesNeeded field decides their order.
 * RT-108 comes first because it needs 5 minutes,
 * while RT-103 needs 15 minutes.
 *
 * D1 - Recursive ranges
 * Show first, last, middle, and the base-case evaluations along the first branch
 * starting at 0..7. Identify where execution resumes after the call for 0..0.
 * Answer:
 * The first call uses first = 0 and last = 7, with middle = 3.
 * The left branch is 0..3, with middle = 1.
 * Then it continues to 0..1, with middle = 0.
 * The call 0..0 reaches the base case because first >= last.
 * Execution resumes in the call for 0..1, which then
 * processes 1..1 before merging both elements.
 *
 * D2 - Stable ties
 * Identify both pairs of tasks that tie in the two sort fields. Explain how the
 * comparator and the merge preserve their arrival order.
 * Answer:
 * RT-102 and RT-107 both have 1 day and 20 minutes.
 * RT-103 and RT-105 both have 2 days and 15 minutes.
 * The comparator returns true when both fields are equal.
 * This makes the merge choose the left pointer first,
 * preserving the original arrival order of tied tasks.
 *
 * D3 - Time, space, and original data
 * Give the sorting time and auxiliary-space order of this pointer-array version.
 * Compare with the linked-list sort in Part B and explain why the original task
 * storage order is preserved here but the node order changes in Part B.
 * Answer:
 * The pointer-array merge sort takes O(n log n) time
 * because it divides the array and merges the halves.
 * It uses O(n) auxiliary space for the temporary pointer
 * array and O(log n) space for recursive calls, giving
 * O(n) total auxiliary space.
 *
 * The linked-list merge sort in Part B also takes
 * O(n log n) time, but uses O(log n) auxiliary space
 * for recursion because it reconnects existing nodes.
 *
 * In Part D, only the pointers in view are reordered.
 * The original tasks array stays in arrival order.
 * In Part B, the links between nodes are changed,
 * so the linked-list order changes.
 */
