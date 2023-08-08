#include <iostream>

struct Record {};

// Saves the given record to the database.
// 
// Parmeters:
// record: If the given record does not yet have a database ID, then the method
// modified the record object to store the ID assigned by the database.
// Returns: int
// An integer representing the ID of the saved record.
// Throws:
// DatabaseNotOpenException if the openDatabase() method has not
// been called yet.
int saveRecord(Record &record);

int main(int argc, char *argv[]) { return 0; }
