#pragma once
#include <vector>

class BoundingBox
{
public:

	BoundingBox(
		int minX, 
		int maxX, 
		int minY, 
		int maxY, 
		int id, 
		std::vector<int> neightbours
	) : 
		x({ minX, maxX }),
		y({ minY, maxY }),
		m_id(id),
		m_neightbours(neightbours)
	{}

private:

	int m_id;
	std::vector<int> m_neightbours;
	std::pair<int, int> x; // represents the bounds on the x-axis
	std::pair<int, int> y; // represents the bounds on the y-axis

};

