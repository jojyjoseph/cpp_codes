#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cctype>
#include<sstream>

//class Command - Base class for commands of different types
class Command
{
	public:
		Command(int value):m_value{value}{}
		virtual ~Command(){}

		// for apply the operation on the data
		virtual void apply(int & value)=0;

		// retrive the operated value
		virtual int value(){return m_value;}

	protected:
		int m_value=0;


};

// Undo Redo stack
class CommandStack
{
	public:
		CommandStack(){}
		virtual ~CommandStack(){}

		// insert a new undo redo command, called whenever a new command is called. corresponding undo command is automatically created
		void insert(Command * fwdcommand, Command * undocommand)
		{
			/*
			 * When the pos is not pointing to the end of the vector,
			 * Then the insertion has to be done after deleting all the elements after the position
			 */
			if((pos<vectorCommands.size()-1) && !vectorCommands.empty())
			{
				vectorCommands.erase(vectorCommands.begin()+pos+1,vectorCommands.end());
			}
			
			// insert the command and undo command pair
			vectorCommands.push_back({fwdcommand,undocommand});
			// set the pos to the end of the new end.
			pos=vectorCommands.size()-1;
			
		}

		void apply(int & answer)
		{
			try
			{
				//apply the command based on the pos
				vectorCommands.at(pos).first->apply(answer);
			}
			catch(...)
			{}
		}

		void undo(int & answer)
		{
			// if the position is at the beginning of the vector commands, undo can't work
			if(pos != -1)
			{
				vectorCommands.at(pos).second->apply(answer);
				pos--;
			}	
		}

		void redo(int & answer)
		{
			// if the position is at the end of the vector commands, redo can't work
			if(pos != vectorCommands.size() -1)
			{
				pos++;
				vectorCommands.at(pos).first->apply(answer);
			}
		}

	private:
		std::vector<std::pair<Command*,Command*>> vectorCommands{};
		int pos{-1};
}stack;

// sub class for Adding operation
class AddCommand : public Command
{
	public:
		AddCommand(int value):Command{value}
		{}
		virtual void apply(int & value) override
		{
			value +=m_value;
		}


};

// sub class for subtraction operation
class SubCommand : public Command
{
	public:
		SubCommand(int value):Command{value}
		{}
		virtual void apply(int & value) override
		{
			value -=m_value;
		}
};

// This function is called from the main by the user.
void performOperation(int & answer, std::string &s)
{
	// lambda definitions
	

	// Checks if the user input is valid, if so then returns true.
	auto sanityCheck=[](const std::string &s)->int
	{
		// check if s is "redo" or "undo"
		if(s =="redo" || s =="undo")
			return 0;

		// check for any non-acceptable characters
		bool nonAcceptableChars = std::any_of(std::begin(s),std::end(s),[](const char c)->bool{ return !(c=='+' || c=='-' || std::isdigit(c));});
		if(nonAcceptableChars)
			return 1;

		// only one +/- allowed
		int countSign = std::count_if(s.begin(),s.end(), [](const char c)->bool{return (c=='+' || c=='-');});
		if(countSign != 1)
			return 2;
		
		// atleast one digit should be there
		int countNum = std::count_if(s.begin(),s.end(), [](const char c)->bool{return std::isdigit(c);});
		if(!countNum)
			return 3;
		
		// first char should be +/-
		if(s[0] != '+' && s[0] != '-')
			return 4;

		return 0;
	};

	/*
	 * read the integer value
	 * value exists from the second to the last as the first is the sign character
	 */
	auto getValue=[](const std::string &s)->int{
		std::stringstream ss(std::string(s.begin() + 1, s.end()));
		int value;
		ss>>value;
		return value;
	};

	/*
	 * creates a commands based on the string.
	 */
	auto createCommand=[&](const std::string &s)->Command*{
		Command * command;
		if(s[0] == '+')
		{
			command = new AddCommand(getValue(s));
		}
		else if(s[0] == '-')
		{
			command = new SubCommand(getValue(s));
		}
		else
			command = nullptr;

		return command;
	};
	
	/*
	 * Create undo command based on the command
	 */
	auto createundoCommand=[](Command * command)->Command *{
		if(dynamic_cast<AddCommand*>(command))
		{
			return new SubCommand(command->value());
		}
		else if(dynamic_cast<SubCommand*>(command))
		{
			return new AddCommand(command->value());
		}

		return nullptr;
	};

	/*
	 * Apply value based on user input
	 */
	auto applyValue=[&](int & answer, const std::string &s)->void{
	
		if(s=="redo")
		{
			stack.redo(answer); // apply the redo operation 
		}
		else if(s=="undo")
		{
			stack.undo(answer); // apply the undo operation
		}
		else
		{
			/*
			 * For normal operations like +2 , -3 etc
			 * create the command and the undocommand
			 * insert it to the stack and apply the latest command from the stack
			 */
			Command * command = createCommand(s);
			Command * undocommand = createundoCommand(command);
			stack.insert(command, undocommand);
			stack.apply(answer);
		}

	};


	// This is the called sequence below
	//remove whitespace	
	s.erase(std::remove_if(std::begin(s), std::end(s), [](const char c)->bool{return std::isspace(c);}),s.end());

	// do nothing if input string is not proper
	if(int res = sanityCheck(s))
	{
		std::cout<<"sanity check failed - no operation performed - failure reason code : "<<res<<"\n";
		return;
	}

	// if input passes the Sanity check, apply the value
	applyValue(answer,s);
}

int main()
{
	int answer=0;
	std::string str;
	
	do
	{
		str="";// reset the string
		std::cout<<"\nEnter next operation : e.g. (+3, -5, undo, redo , exit) -only addition and subtraction\n";
		std::cin>>str;
		
		// Functions that does the operation
		performOperation(answer,str);

		std::cout<<"Operation : "<<str<<", Answer = "<<answer<<"\n";
	}
	while(str != "exit");

	return 0;
}


