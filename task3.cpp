#pragma once
#include "Container.h"
#include "Object.h"
#include <iostream>

int main() {

	Container<Task*>* taskContainer = new Container<Task*>;


	/*tasks to add*/
	BinaryOperationTask* taskAdd1 = new BinaryOperationTask(2, 3, "Adding");
	BinaryOperationTask* taskMultiply = new BinaryOperationTask(2, 5, "Multiplying");
	AmountTask* taskAmount = new AmountTask(taskContainer);
	AmountResultTask* resultAmount = new AmountResultTask(taskContainer);
	BinaryOperationTask* taskDivide1 = new BinaryOperationTask(6, 3, "Dividing");
	BinaryOperationTask* taskDivide2 = new BinaryOperationTask(9, 3, "Dividing");
	ObjectsAmountTask* taskTotalAmount = new ObjectsAmountTask();
	ClearTask* clearTask = new ClearTask(taskContainer);
	BinaryOperationTask* taskAdd2 = new BinaryOperationTask(6, 7, "Adding");
	BinaryOperationTask* taskSubtract = new BinaryOperationTask(56, 49, "Subtracting");

	/*adding tasks*/
	AddTask* task1 = new AddTask(taskContainer, taskAdd1);
	AddTask* task2 = new AddTask(taskContainer, taskMultiply);
	AddTask* task3 = new AddTask(taskContainer, taskAmount);
	AddTask* task4 = new AddTask(taskContainer, resultAmount);
	AddTask* task5 = new AddTask(taskContainer, taskDivide1);
	AddTask* task6 = new AddTask(taskContainer, taskDivide2);
	AddTask* task7 = new AddTask(taskContainer, taskTotalAmount);
	AddTask* task8 = new AddTask(taskContainer, clearTask);
	AddTask* task9 = new AddTask(taskContainer, taskAdd2);
	AddTask* task10 = new AddTask(taskContainer, taskSubtract);

	//probably should have added them in a separate container, sorry, didn't have time
	task1->execute();
	task2->execute();
	task3->execute();
	task4->execute();
	task5->execute();
	task6->execute();
	task7->execute();
	task8->execute();
	task9->execute();
	task10->execute();


	/*executing some of the tasks:*/
	taskAdd1->execute();
	taskMultiply->execute();
	taskDivide2->execute();
	taskAmount->execute();
	taskTotalAmount->execute();
	taskSubtract->execute();

	std::cout << "the size of the container with tasks is " + std::to_string(taskContainer->getSize()) << std::endl << std::endl;

	Container<std::string>* stringContainer = new Container<std::string>;


	auto iter = taskContainer->begin();
	while (iter != taskContainer->end()) {
		
		stringContainer->add_toEnd(iter.value()->toString());
		delete iter.value();
		iter.next();

	}

	

	for (auto iter = stringContainer->begin(); iter != stringContainer->end(); iter.next()) {
		std::cout << iter.value() << std::endl;
	}

	stringContainer->clear();


	//deleting tasks, which are not in containers
	delete task1;
	delete task2;
	delete task3;
	delete task4;
	delete task5;
	delete task6;
	delete task7;
	delete task8;
	delete task9;
	delete task10;




	int counter = Object::getCounter();
	std::cout << std::endl << "the amount of objects is " + std::to_string(counter);




}