#ifndef GLOBAL_H
#define GLOBAL_H

#define PACE_MAKER_RATE 250

enum class VFDDataColumn : int {
    ControlSpeed = 0,
    RampSpeed = 1,
    FeedbackSpeed = 2,
    Direction = 3,
    Acceleration = 4,
    Deceleration = 5,
};

enum class JobDataEnum : int {
    RowCount = 1,
    ColumnCount = 5,

    JobNumber = 0,
    JobDescription = 1,
    PartName = 2,
    PartNumber = 3,
    Customer = 4,
};

#endif // GLOBAL_H
