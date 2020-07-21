#ifndef GLOBAL_H
#define GLOBAL_H

#define PACE_MAKER_RATE 250

struct TestProfileEnum {
    enum {
        COLUMN_COUNT = 5,

        DURATION_COL = 0,
        SPEED_COL = 1,
        FB_SPEED_COL = 2,
        DIRECTION_COL = 3,
        COMMENT_COL = 4,
    };
};

struct UnicoDataEnum {
    enum {
        MAX_SPEED = 7000, //[RPM]
        DEV_ID = 1,
        RAMP_RATE_MAX = 1000, //[RPM/s]

        //VFD holding registers
        SPEED_R = 84,
        FB_SPEED_R = 222,
        DIR_R = 427,
        ACC_R = 86,
        DEC_R = 87,
    };
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
