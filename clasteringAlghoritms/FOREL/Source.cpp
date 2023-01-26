#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>

struct obj
{
	double Elem;
	bool Clusterization;
	int Ind;
};
void Output(std::vector<obj>& Vector)
{
	for (int i = 0; i < Vector.size(); ++i)
	{
		obj Obj = Vector[i];
		std::cout << Obj.Elem << " ";
	}
	std::cout << std::endl;
}

class queue
{
private:
	std::vector<obj> Vector;
public:
	queue(std::ifstream& File)
	{
		double Value;
		int i = 0;
		while (File >> Value)
		{
			obj Object;
			Object.Elem = Value;
			Object.Clusterization = false;
			Vector.push_back(Object);
		}
	}
	double& operator[](int Index)
	{
		if (Index < Vector.size())
		{
			obj Obj = Vector.at(Index);
			return Obj.Elem;
		}
		else
			throw std::range_error("bad index in safearray");
	}
	void Output()
	{
		for (int i = 0; i < Vector.size(); ++i)
		{
			obj Obj = Vector[i];
			std::cout <<  Obj.Elem << " ";
		}
		std::cout << std::endl;
	}
	bool Clusterization()
	{
		for (int i = 0; i < Vector.size();i++)
		{
			if (Vector[i].Clusterization == false)
				return false;
		}
		return true;
	}
	obj GetRandObject()
	{
		while (true)
		{
			std::random_device rd;
			std::mt19937 Gen(rd());
			int Index = Gen() % Vector.size();
			if (Vector[Index].Clusterization == false)
			{
				return Vector[Index];
			}
		}
	}
	std::vector<obj> GetNeighbours(obj& CurrentObj,const double Radius)
	{
		std::vector<obj> NeighbourElems;
		int NumOfNewObj = 0;
		for (int i = 0; i < Vector.size();i++)
		{
			if (Vector[i].Clusterization == false && Vector[i].Elem - CurrentObj.Elem < Radius)
			{
				NeighbourElems.push_back(Vector[i]);
				NeighbourElems.at(NumOfNewObj).Ind = i;
				NumOfNewObj++;
			}
		}
		return NeighbourElems;
	}
	double CenterOfObjects(std::vector<obj>& NeigbourObjects)
	{
		double Summ = 0;
		for (int i = 0; i < NeigbourObjects.size();i++)
		{
			Summ += NeigbourObjects.at(i).Elem;
		}
		return Summ / NeigbourObjects.size();

	}
	void DeleteClusterizationObjects(std::vector<obj>& Objects)
	{
		for (int i = 0; i < Objects.size();i++)
		{
			Vector[Objects.at(i).Ind].Clusterization = true;
		}
	}
};



int main(int Argc, char** Argv, char** Envp)
{
	std::ifstream File;
	double Radius = 10;
	File.open("input2.txt");
	queue Queue(File);
	Queue.Output();
	while (Queue.Clusterization() != true)
	{
		obj CurrentObject = Queue.GetRandObject();
		std::vector<obj> NeigbourObjects = Queue.GetNeighbours(CurrentObject, Radius);
		double CenterElem = Queue.CenterOfObjects(NeigbourObjects);
		while (CurrentObject.Elem != CenterElem)
		{
			CurrentObject.Elem = CenterElem;
			NeigbourObjects = Queue.GetNeighbours(CurrentObject, Radius);
			CenterElem = Queue.CenterOfObjects(NeigbourObjects);
		}
		std::cout << "Cluster:";
		Output(NeigbourObjects);
		Queue.DeleteClusterizationObjects(NeigbourObjects);
		NeigbourObjects.clear();
	}
}