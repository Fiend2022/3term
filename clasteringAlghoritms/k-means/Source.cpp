#include <iostream>
#include <vector>
#include <fstream>
#include <random>



class Cluster
{
	std::vector<float> cluster;
	float center;
	float max;
	float min;
public:
	Cluster()
	{
		center = 0;
		max = 0;
		min = 0;
	}
	Cluster(float _max, float _min, float _center=0)
	{
		max = _max;
		min = _min;
		center = _center;
	}
	Cluster(std::ifstream& file)
	{
		float value =0;
		int i = 0;
		while (file >> value)
		{
			cluster.push_back(value);
		}
	}
	void print()
	{
		for (size_t i = 0; i < cluster.size();i++)
			std::cout << cluster[i]<< " ";
	}
	bool clusterization_ready()
	{
		float Summ = 0; 
		for (int i = 0; i < cluster.size();i++)
		{
			Summ += cluster[i];
		}
		Summ /= cluster.size();
		return Summ == center;
	}
	float get_max()
	{
		for (int i = 0; i < cluster.size();i++)
		{
			if (cluster.at(i) > max)
				max = cluster.at(i);
		}
		return max;
	}
	float get_min()
	{
		for (int i = 0; i < cluster.size();i++)
		{
			if (cluster.at(i) < min)
				min = cluster.at(i);
		}
		return min;
	}
	void search_center()
	{
		if (cluster.size() == 0)
		{
			center = 0;
			return;
		}
		float Summ = 0;
		for (int i = 0; i < cluster.size();i++)
			Summ += cluster.at(i);
		center = Summ / cluster.size();
	}
	float get_center()
	{
		return center;
	}

	float current_center()
	{
		return center;
	}
	float get_size()
	{
		return cluster.size();
	}
	void get_random_center()
	{
		std::random_device rd;
		std::mt19937 Gen(rd());
		float  NewCenter = Gen() % ((int)max + 1 - (int)min + 1) + (min + 1);
		center = NewCenter;
	}
	void set_center(float& _center)
	{
		center = _center;
	}
	void push_back(float& newElem)
	{
		cluster.push_back(newElem);
	}
	float& operator[](int index)
	{
		if (index < cluster.size() && index >= 0)
		{
			return cluster.at(index);
		}
		else
			throw std::range_error("bad index in safearray");
	}
	void clear()
	{
		cluster.clear();
	}
};


int main()
{
	std::ifstream file;
	size_t numOfClusters = 5;
	file.open("input2.txt");
	Cluster setOfFloat(file);
	setOfFloat.print();
	std::cout << "\n\n\n";
	std::vector<Cluster> clusters;
	std::vector<float> centers;
	for (int i = 0; i < numOfClusters;i++)
	{
		Cluster emptyCluster(setOfFloat.get_max(),setOfFloat.get_min());
		emptyCluster.get_random_center();
		float center = emptyCluster.get_center();
		centers.push_back(center);
		clusters.push_back(emptyCluster);
	}
	while (true)
	{
		for (size_t i = 0; i < setOfFloat.get_size();i++)
		{
			size_t myCluster = 0;
			float Way = abs(setOfFloat[i] - clusters[0].get_center());
			for (size_t j = 0; j < numOfClusters;j++)
			{
				if (abs(setOfFloat[i] - clusters[j].get_center()) < Way)
				{
					Way = abs(setOfFloat[i] - clusters[j].get_center());
					myCluster = j;
				}
			}
			clusters[myCluster].push_back(setOfFloat[i]);
		}
		for (int i = 0; i < numOfClusters;i++)
		{
			std::cout << clusters[i].get_center() << "   ";
			clusters[i].print();
			std::cout << "\n";
		}
		std::cout << "\n\n";
		for (int i = 0; i < numOfClusters;i++)
		{
			clusters[i].search_center();
		}
		int numOfMatch = 0;
		for (int i = 0; i < numOfClusters;i++)
		{
			if (centers[i] == clusters[i].get_center())
				numOfMatch++;
			else 
				centers[i] = clusters[i].get_center();
		}
		if (numOfMatch == numOfClusters)
			break;
		for (int i = 0; i < numOfClusters;i++)
		{
			clusters[i].clear();
		}
	}
	for (int i = 0; i < numOfClusters;i++)
	{
		std::cout << i+1<<" cluster:" << " ";
		clusters[i].print();
		std::cout << "\n";
	}
}