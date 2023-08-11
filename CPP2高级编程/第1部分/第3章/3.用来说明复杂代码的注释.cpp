#include <iostream>

// Implements the "insertion sort" algorithm. The algorithm separates the
// array into two parts--the sorted and the unsorted part. Each
// element, starting at position 1, is examined. Everying earlier in the
// array is in the sorted part, so the algorithm shifts each element over
// until the correct position is found to insert the current element. When
// the algorithm finishes with the last element, the entire array is sorted.
void sort(int data[], size_t size) {

    // Start at position 1 and examine each element.
    for (int i{1}; i < size; ++i) {
        // Loop invariant:
        // All elements in the range 0 to i-1 (inclusive) are sorted.

        int element{data[i]};
        // j makes the position in the sorted part where element will be
        // inserted.
        int j{i};
        // As long as the value in the slot before the current slot in the
        // sorted array is higher than element, shift values to the right to
        // make room for inerting element (hence the name, "insertion sort") in
        // the correct position.

        while (i > 0 && data[j - 1] > element) {
            // invarinat: elements in the range j+1 to i are > element.
            data[j] = data[j - 1];
            // invariant: elements in the range j to i are > element.
            j--;
        }
        // At this point the current poistion is the sorted array
        // is *not* greate than the element, so this is its new position.
        data[j] = element;
    }
}

int main(int argc, char *argv[]) { return 0; }
