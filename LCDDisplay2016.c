char *options[1];
const int optionCount = 1;

const int leftButton = 1;
const int centerButton = 2;
const int rightButton = 4;


void setOptions(){
		options[0] = "Wall Sweep";
}

int getAutoOption()
{
	setOptions();
	int option = 0;
	int selection = -1;
	bLCDBacklight = true;
	while(nLCDButtons != centerButton){
 		displayLCDCenteredString(0, options[option]);
 		delay(500);
 		if(nLCDButtons ==	leftButton){
 			if (option == 0)
 				option = optionCount - 1;
 			else
 				option = option - 1;
 		}
 		if(nLCDButtons ==	rightButton){
 			if (option == (optionCount - 1))
 				option = 0;
 			else
 				option = option + 1;
 		}
	}
	 selection = option;
	 displayLCDCenteredString(0, "You selected");
	 displayLCDCenteredString(1, options[selection]);
	 delay(2000);
	 bLCDBacklight = false;
	 return selection;
}
