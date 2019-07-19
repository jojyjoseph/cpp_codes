#include<bitset>
#include<string>
#include<iostream>
#include<climits>

// std::bitset is typedef for easy handling and passing as reference
using HomeSwitch=std::bitset<7>;

// enum switches to refer various switches
enum Switches
{
	BEDROOM_FAN=0,
	BEDROOM_LIGHT,
	HALL_FAN,
	HALL_LIGHT,
	TOILET_LIGHT,
	KITCHEN_LIGHT,
	SITOUT_LIGHT
};

// set function uses std::bitset::set
void setSwitch(HomeSwitch& r,Switches s)
{
	r.set(s);
}

// reset funciton uses std::bitset::reset 
void resetSwitch(HomeSwitch& r, Switches s)
{
	r.reset(s);
}


// toggle function uses std::bitset::flip
void toggleSwitch(HomeSwitch& r, Switches s)
{
	r.flip(s);
}

// print function internally converts the std::bitset to string
void print(HomeSwitch& r, std::string s="")
{
	std::cout<<s<<(s.size() ? " " : "")<<r.to_string()<<"\n";
}

int main()
{
	// create a switchpanel from std::bitset<7>
	HomeSwitch switchpanel{0b0000000};
	print(switchpanel, "Before turning on the BEDROOM_FAN");
	
	// switch on the BEDROOM FAN, check the Switches enum
	setSwitch(switchpanel,BEDROOM_FAN);
	print(switchpanel, "After turning on the BEDROOM_FAN");

	// Toggle the Kitchen light
	toggleSwitch(switchpanel, KITCHEN_LIGHT);
	print(switchpanel, "After toggling the kitchen light");
	
	//std::bitset::size
	std::cout<<"Total number of switches are " + std::to_string(switchpanel.size()) +"\n";

	//std::bitset::count
	std::cout<<"Total number of ON switches are " + std::to_string(switchpanel.count()) + "\n";

	//std::bitset::any, std::bitset::none, std::bitset::all
	std::cout<<std::boolalpha;
	std::cout<<"Is any Switch ON - "<<switchpanel.any()<<"\n";
	std::cout<<"Is none of the Switch ON - "<<switchpanel.none()<<"\n";
	std::cout<<"Is all of the Switch ON - "<<switchpanel.all()<<"\n";
	
	//std::bitset::test -- checks bound check else throws std::out_of_range 
	std::cout<<"Is BEDROOM_FAN on ? - "<<switchpanel.test(BEDROOM_FAN)<<"\n";

	//std::bitset::operator[] - no bound check performed
	std::cout<<"Is BEDROOM_LIGHT on ? -"<<switchpanel[BEDROOM_LIGHT]<<"\n";

	// bit operations
	std::cout<<"\n";
	HomeSwitch switch2{0b1110000};
	std::cout<<"New switch for bit operation "<<switch2.to_string()<<"\n";

	std::cout<<"AND operation "<<(switch2 & switchpanel).to_string()<<"\n";
	std::cout<<"OR operation "<<(switch2 | switchpanel).to_string()<<"\n";
	std::cout<<"XOR operation "<<(switch2 ^ switchpanel).to_string()<<"\n";
	std::cout<<"NOT operation "<<(~switchpanel).to_string()<<"\n";
	std::cout<<"Left shift "<<(switch2<<=1).to_string()<<"\n";
	std::cout<<"Right shift "<<(switch2>>1).to_string()<<"\n";

	//Conversion - string, ulong
	std::cout<<"String conversion "<<switch2.to_string()<<"\n";
	std::cout<<"String conversion "<<switch2.to_string('*')<<"\n";
	std::cout<<"String conversion "<<switch2.to_string('S','X')<<"\n";
	std::cout<<"ULONG conversion "<<switch2.to_ulong()<<"\n";

	return 0;

}
