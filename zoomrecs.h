//The struct that we were given
struct ZoomRecord
{
    char email[60]; // email of the student
    char name[60]; // name of the student
    int durations[9]; // duration for each lab.
    struct ZoomRecord *next;
};

extern struct ZoomRecord *head;