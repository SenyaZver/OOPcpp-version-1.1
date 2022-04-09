#pragma once
#include <string>
#include "Container.h"

class Object
{

protected:
	static int count;

public:

	static void addInstance() { count++; }
	static void deleteInstance() { count--; }
	static int getCounter() { return count; }

	virtual std::string toString() const = 0;
};

int Object::count = 0;

class Task : public Object
{
public:
	Task(bool isResultPossible) : resultPossible(isResultPossible) {
		addInstance();
	}
	virtual void execute() = 0;
	bool resultPossible;
	~Task() {
		deleteInstance();
	}


};

class Named : public Object
{
protected:
	std::string name;

public:
	Named(std::string newName) {
		this->name = newName;
	}
};


class BinaryOperationTask : public Task, public Named
{
private:
	const double arg1;
	const double arg2;

	double result = NULL;


public:
	BinaryOperationTask(double newArg1, double newArg2, std::string newName) : Task(true), Named(newName), arg1(newArg1), arg2(newArg2) {}


	virtual void execute() {
		if (name == "Adding") {
			this->result = arg1 + arg2;
		}
		else if (name == "Subtracting") {
			this->result = arg1 - arg2;
		}
		else if (name == "Dividing") {
			this->result = arg1 / arg2;
		}
		else if (name == "Multiplying") {
			this->result = arg1 * arg2;
		}
		else {
			throw "invalid operation name";
		}
	}

	double getResult() {
		this->execute();

		return this->result;
	}


	virtual std::string toString() const {
		if (this->result == NULL) {
			std::string result = std::string("Binary Operation is ") + this->name;

			return result;
		}
		std::string result = std::string("Binary Operation is ") + this->name + std::string(", The result is ") + std::to_string(this->result);

		return result;
	}


};

class AddTask : public Task, public Named {
private:
	Container<Task*>* container;
	Task* task;

public:
	AddTask(Container<Task*>* newContainer, Task* newTask) : Task(false), Named("Adding task"),
		container(newContainer), task(newTask) {}

	virtual void execute() {
		container->add_toEnd(this->task);
	}


	virtual std::string toString() const {
		std::string result = this->name + this->task->toString();
		return result;
	}

	~AddTask() {}
};


class AmountTask : public Task, public Named {
private:
	Container<Task*>* container;
	int result = NULL;

public:
	AmountTask(Container<Task*>* newContainer) : Task(true), Named("Amount of Tasks"), container(newContainer) {}

	virtual void execute() {
		this->result = container->getSize();
	}

	virtual std::string toString() const {
		if (result == NULL) {
			std::string result = this->name;
			return result;
		}

		std::string result = this->name + " there are " + std::to_string(this->result) + " tasks";
		return result;
	}

	~AmountTask() {};
};

class AmountResultTask : public Task, public Named {
private:
	Container<Task*>* container;
	int result = NULL;

public:
	AmountResultTask(Container<Task*>* newContainer) : Task(true), Named("Amount of Tasks with results"), container(newContainer) {}

	virtual void execute() {

		for (auto iter = container->begin(); iter != container->end(); iter.next()) {
			if (iter.value()->resultPossible) {
				this->result++;
			}
		}

	}

	virtual std::string toString() const {
		if (result == NULL) {
			std::string result = this->name;
			return result;
		}

		std::string result = this->name + " there are " + std::to_string(this->result) + " tasks";
		return result;
	}

	~AmountResultTask() {}

};

class ClearTask : public Task {
private:
	Container<Task*>* container;

public:
	ClearTask(Container<Task*>* newContainer) : Task(false), container(newContainer) {}

	virtual void execute() {
		this->container->clear();
	}

	virtual std::string toString() const {
		std::string result = "Clearing Container task";
		return result;
	}
};

class ObjectsAmountTask : public Task, public Named {
	int result = NULL;
public:
	ObjectsAmountTask() : Task(true), Named("Amount of Objects task") {}

	virtual void execute() {
		this->result = getCounter();
	}

	virtual std::string toString() const {
		std::string result = this->name;
		if (this->result != NULL) {
			result = result + " , the amount is: " + std::to_string(this->result);
		}
		return result;
	}

};
