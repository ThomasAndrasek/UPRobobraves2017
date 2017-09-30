bool strafeMode = false;
bool sideStrafe = false;

int strafeSpeed = 0;
int rightDriveSpeed = 0;
int leftDriveSpeed = 0;
//int liftSpeed = 0;
int slideLeftSpeed = 0;

int outerCurrentLineError = 0;
int innerCurrentLineError = 0;
float lineSumError = 0;
float currentLineError = 0;
int lineDeltaPower = 0;
float pid_Kp_line = 0.04;
float pid_Ki_line = 0.00000;
