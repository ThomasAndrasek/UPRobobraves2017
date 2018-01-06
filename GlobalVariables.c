int rightDriveSpeed = 0;
int leftDriveSpeed = 0;
int lifterSpeed = 0;
int coneIntakeSpeed = 0;
int armSpeedLeft = 0;
int armSpeedRight = 0;
int intakeElbowSpeed = 0;

int armPosition = 0;
int position = 0;
int elbowPosition = 0;

int outerCurrentLineError = 0;
int innerCurrentLineError = 0;
float lineSumError = 0;
float currentLineError = 0;
int lineDeltaPower = 0;

const float PID_KP_LINE = 0.04;
const float PID_KI_LINE = 0.00000;

int leftCurrentArmError = 0;
int rightCurrentArmError = 0;
float armSumError = 0;
float currentArmError = 0;
int armDeltaPower = 0;

const float PID_KP_ARM = 0.04;
const float PID_KI_ARM = 0.00001;
