#ifndef GLOBAL_H
#define GLOBAL_H

#define PACE_MAKER_RATE 250

struct DataSetEnum {
    enum {
        SLOT_SIZE = 1048576, // 1M values
        SLOT_COUNT = __INT32_MAX__ / DataSetEnum::SLOT_SIZE + 1, // +1 to round up
    };
};

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

struct JobDataEnum{
    enum {
        ROW_COUNT = 1,
        COLUMN_COUNT = 5,

        JOB_NUMBER_COL = 0,
        JOB_DESCRIPTION_COL = 1,
        PART_NAME_COL = 2,
        PART_NUMBER_COL = 3,
        CUSTOMER_COL = 4,
    };
};

#endif // GLOBAL_H
