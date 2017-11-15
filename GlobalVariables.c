int rightDriveSpeed = 0;
int leftDriveSpeed = 0;
int mobileArmSpeed = 0;
int clawSpeed = 0;
int turnTableSpeed = 0;

int outerCurrentLineError = 0;
int innerCurrentLineError = 0;
float lineSumError = 0;
float currentLineError = 0;
int lineDeltaPower = 0;

const float PID_KP_LINE = 0.04;
const float PID_KI_LINE = 0.00000;
