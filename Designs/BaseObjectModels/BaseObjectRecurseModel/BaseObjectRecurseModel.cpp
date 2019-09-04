#include<memory>
#include<iostream>
#include<string>
#include<set>
#include<functional>


class BaseObject
{
public:
	BaseObject(std::string name, int id)
		:m_name{ name }, m_id{ id }{}
	virtual ~BaseObject() { std::cout << "Destroy "<< getName()<<"\n"; }


	std::shared_ptr<BaseObject> getSharedPtr()
	{
		if (m_weakptr.expired())
		{
			auto p = std::shared_ptr<BaseObject>(this);
			m_weakptr = p;
			return p;
		}
		else
		{
			return m_weakptr.lock();
		}
	}

	/*
	* recurse function
	* f - function object that is invoked in recursion
	* self - determines whether the object participates in recursion
	*/
	virtual bool recurse(std::function<bool(std::shared_ptr<BaseObject>)> f, bool self)
	{
		return self ? f(getSharedPtr()) : true;
	}

	// setter for m_Parent
	void setParent(std::shared_ptr<BaseObject> parent) 	{m_Parent = parent;}
	std::shared_ptr<BaseObject> getParent() {return m_Parent.lock();}
 
	//getters and setters
	std::string getName() { return m_name; }
	int getID() { return m_id; }

private:
	// member variables - name and ID
	std::string m_name;					// 1. name of the Base Object
	int m_id;							// 2. id of the Base Object
	std::weak_ptr<BaseObject> m_Parent;	// 3. Parent of the BaseObject

	// weak pointer to hold self
	std::weak_ptr<BaseObject> m_weakptr;
};

using BaseObjectSet = std::set<std::shared_ptr<BaseObject>>;

class ContainerObject : public BaseObject
{
public:
	ContainerObject(std::string name, int id)
		:BaseObject{ name,id } {}
	virtual ~ContainerObject() {}

	void insertChild(std::shared_ptr<BaseObject> c)
	{
		m_Children.insert(c);
		c->setParent(getSharedPtr());
	}

	// f - function object passed for recursion, self is to determine is the object its
	virtual bool recurse(std::function<bool(std::shared_ptr<BaseObject>)> f, bool self) override
	{
		// if the BaseObject of this returns false, no more recursion on the children
		if (!BaseObject::recurse(f, self))
			return false;

		for (auto child : m_Children)
			child->recurse(f, true);
	}

private:
	BaseObjectSet m_Children;
};

// Tree initialization function
std::shared_ptr<BaseObject> init()
{
	std::shared_ptr<BaseObject> root = (new ContainerObject("RootContainer", 1))->getSharedPtr();

	// create two more containers
	std::shared_ptr<BaseObject> container1 = (new ContainerObject("Container1", 11))->getSharedPtr();
	std::shared_ptr<BaseObject> container2 = (new ContainerObject("Container2", 12))->getSharedPtr();

	// insert container1 and container 2 in root container
	std::static_pointer_cast<ContainerObject>(root)->insertChild(container1);
	std::static_pointer_cast<ContainerObject>(root)->insertChild(container2);

	// insert in container1
	std::static_pointer_cast<ContainerObject>(container1)->insertChild((new BaseObject("Con1_child1", 111))->getSharedPtr());
	std::static_pointer_cast<ContainerObject>(container1)->insertChild((new BaseObject("Con1_child2", 112))->getSharedPtr());
	std::static_pointer_cast<ContainerObject>(container1)->insertChild((new BaseObject("Con1_child3", 113))->getSharedPtr());

	// insert in container2
	std::static_pointer_cast<ContainerObject>(container2)->insertChild((new BaseObject("Con2_child1", 121))->getSharedPtr());
	std::static_pointer_cast<ContainerObject>(container2)->insertChild((new BaseObject("Con2_child2", 122))->getSharedPtr());
	std::shared_ptr<BaseObject> con2_con1 = (new ContainerObject("Con2_Con1", 123))->getSharedPtr();
	std::static_pointer_cast<ContainerObject>(container2)->insertChild(con2_con1);
	std::static_pointer_cast<ContainerObject>(con2_con1)->insertChild((new BaseObject("Con2_Con1_child1", 1231))->getSharedPtr());
	std::static_pointer_cast<ContainerObject>(con2_con1)->insertChild((new BaseObject("Con2_Con1_child2", 1232))->getSharedPtr());
	return root;
}

// main function
int main()
{
	// Tree initialization
	std::shared_ptr<BaseObject> root = init();
	std::cout << root->getName() << "\n";

	// Recurse operation demo
	std::cout << "\nRecurse operation to print name\n";
	root->recurse([](std::shared_ptr<BaseObject> p)->bool {
		std::cout << "Name of the Base Object is " << p->getName() << "\n";
		return true;
	}, true);

	return 0;
}
