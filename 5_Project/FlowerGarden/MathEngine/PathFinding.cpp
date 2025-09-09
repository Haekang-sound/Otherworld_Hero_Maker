///
/// �ε��� ������ �߻�������
/// ���������� �۵��Ѵ�.
/// 
/// �ٸ� �۾��� ���� �������� ����
/// �����Ϸ� ���� ����
///

#include "PathFinding.h"

#include "FindPosition.h"

#include <list>
#include <fstream>

namespace Algorithm
{
	PathFinding::PathFinding()
		: m_nodes(nullptr)
		, m_mapWidth(0)
		, m_mapHeight(0)
		, m_startNode(nullptr)
		, m_endNode(nullptr)
		, m_finalPath{}
		, m_findPotition{new FindPosition()}
		, m_isTherePath(true)
	{

	}
	PathFinding::~PathFinding()
	{
		if (m_nodes) { delete[] m_nodes; }
		if (m_findPotition) { delete m_findPotition; }
	}

	// ������ �о �� �����
	void PathFinding::ReadSource(std::string path)
	{
		std::wifstream ifs;
		ifs.open(path);

		std::wstring mapName;
		ifs >> mapName;
		std::wstring temp;
		float size;
		ifs >> temp >> temp >> temp >> size;

		int* tempArr = new int[(int)size * (int)size];

		MathEngine::Vector2 center = { 72.f, 108.f };
		MathEngine::Vector2 nowCenter;

		for (int x = 0; x < (int)size; ++x)
		{
			for (int y = 0; y < (int)size; ++y)
			{
				// ���� �о���� 
				int index = x * (int)size + y;
				ifs >> tempArr[index];

				// codinatetion
				MathEngine::Vector2 nowCoodinates = {(float)x, (float)y};

				// location
				nowCenter = { center.x + 72.f * (float)y, center.y + 36.f * (float)y};
				MathEngine::Vector2 newLocation = {nowCenter.x, nowCenter.y};

				// ��ã�� �����Ϳ� ����
				m_findPotition->Insert(nowCoodinates, nowCenter);
				
				// ���� location
			}
			center = { center.x - 72 , center.y + 36 };
		}
		ifs.close();

		CreateMap(tempArr, (int)size, (int)size);

		delete[] tempArr;
	}

	// �������� �ʸ����
	void PathFinding::CreateMap(const int* mapArr, const int& sizeOfX, const int& sizeOfY)
	{
		m_mapWidth = sizeOfX;
		m_mapHeight = sizeOfY;
		m_nodes = new Node[m_mapWidth * m_mapHeight];


		//Ÿ�� �� ��� �ʱ�ȭ
		for (int x = 0; x < m_mapWidth; ++x)
		{
			for (int y = 0; y < m_mapHeight; ++y)
			{
				int index = x * (int)m_mapWidth + y;

				Node& currentNode = m_nodes[index];
				currentNode.x = x;
				currentNode.y = y;
				
				// ��ֹ� ����
				if (mapArr[index] == 0) { currentNode.obstacle = false; }
				else if (mapArr[index] == 1) { currentNode.obstacle = true;}

				currentNode.visited = false;
				currentNode.globalGoal = FLT_MAX;
				currentNode.localGoal = FLT_MAX;
				currentNode.parent = nullptr;
			}
		}
		
		// �̿��ϴ� ��� �ʱ�ȭ
		for (int x = 0; x < m_mapWidth; ++x)
		{
			for (int y = 0; y < m_mapHeight; ++y)
			{
				int index = x * m_mapWidth + y;

				if (x > 0)
					m_nodes[index].neigbours.push_back(
						&m_nodes[(x - 1) * m_mapWidth + (y - 0)]);

				if (x < m_mapWidth - 1)
					m_nodes[index].neigbours.push_back(
						&m_nodes[(x + 1) * m_mapWidth + (y + 0)]);

				if (y > 0)  // ù ��° ���� ����
					m_nodes[index].neigbours.push_back(
						&m_nodes[(x - 0) * m_mapWidth + (y - 1)]);

				if (y < m_mapHeight - 1) // ������ �� ����
					m_nodes[index].neigbours.push_back(
						&m_nodes[(x + 0) * m_mapWidth + (y + 1)]);
			}
		}
	}

	void PathFinding::Init()
	{
		// ���� ��� ����
		m_finalPath.clear();

		// ��� ��� ���� �ʱ�ȭ
		for (int x = 0; x < m_mapWidth; x++)
		{
			for (int y = 0; y < m_mapHeight; y++)
			{
				Node& currentNode = m_nodes[x * m_mapWidth + y];
				currentNode.visited = false;
				currentNode.globalGoal = FLT_MAX;
				currentNode.localGoal = FLT_MAX;
				currentNode.parent = nullptr;
			}
		}
	}

	void PathFinding::SolveAstar()
	{
		Init();

		if (!m_startNode || !m_endNode) 
		{
			m_isTherePath = false;
			return;
		}

		// �Ÿ���� �����Լ�
		auto distance = [](Node* a, Node* b)
		{
			return sqrtf(
				(float)(a->x - b->x) * (float)(a->x - b->x) +
				(float)(a->y - b->y) * (float)(a->y - b->y));
		};

		// �޸���ƽ ���ϴ� �����Լ�
		auto heuristic = [distance](Node* a, Node* b)
		{
			return distance(a, b);
		};

		// ���� ��� �ʱ�ȭ
		Node* currentNode = m_startNode;
		m_startNode->localGoal = 0.0f;
		m_startNode->globalGoal = heuristic(m_startNode, m_endNode);

		// Ž������ �ʴ� ����Ʈ
		std::list<Node*> listNotTestedNodes;
		listNotTestedNodes.push_back(currentNode);

		// �˻� ����
		while (!listNotTestedNodes.empty() && // Ž�� ����Ʈ�� ������� �ʰ�
			currentNode != m_endNode) // �˻� ���� ��尡 ��ǥ��尡 �ƴ� ��
		{
			// �������� ������ ����
			listNotTestedNodes.sort([](const Node* lhs, const Node* rhs){
				return lhs->globalGoal < rhs->globalGoal; });

			// �湮�� ���� ����
			while (!listNotTestedNodes.empty() && // Ž�� ����Ʈ�� ������� �ʰ�
				listNotTestedNodes.front()->visited) // ����Ʈ �� �� ��尡 �湮�Ǿ��ٸ�
			{
				listNotTestedNodes.pop_front(); // ����Ʈ �� �� ���� �ϳ� ����
			}

			// ������ ���� ������
			if (listNotTestedNodes.empty())
			{
				std::cout << "<! ��θ� ã�� �� ���� !>" << std::endl;
				m_isTherePath = false;

				break;
			}

			// ���� �˻� ��� �缳��
			currentNode = listNotTestedNodes.front();
			currentNode->visited = true; // �̸� �˻��������� ����

			// �̿� ���� �˻�
			for (auto neighborNode : currentNode->neigbours)
			{
				if (!neighborNode->visited && // �湮���� �ʴ� ����
					neighborNode->obstacle == false) // ���ع��� �ƴϸ�
				{
					// �˻� ��Ͽ� ����
					listNotTestedNodes.push_back(neighborNode); 
				}

					// �ִ� �Ÿ� �˻�
				float possiblyLowerGoal = currentNode->localGoal +
					distance(currentNode, neighborNode);

				// �ִܰŸ��� ���� �Ÿ����� ª�ٸ�
				if (possiblyLowerGoal < neighborNode->localGoal)
				{
					// �̿� ����� �θ� ����� �θ� ��带 �������
					neighborNode->parent = currentNode;
					// �ִ� �Ÿ� ������Ʈ
					neighborNode->localGoal = possiblyLowerGoal;
					// �޸���ƽ ����: �ִܰŸ� + �����������Ÿ�
					neighborNode->globalGoal =
						neighborNode->localGoal + heuristic(neighborNode, m_endNode);
				}
			}
		}

		UpdateFinalPath();
	}

	void PathFinding::UpdateFinalPath()
	{
		Node* currentPathNode = m_endNode;

		while (currentPathNode != nullptr)
		{
			m_finalPath.push_back(currentPathNode);
			currentPathNode = currentPathNode->parent;
		}
	}

	MathEngine::Vector2 PathFinding::NearestLocation() const
	{
		return GetLocation(m_finalPath.size() - 2);
	}

	bool PathFinding::onDestination()
	{
		int range = 1;
		return 
			(m_startNode->x - m_endNode->x <= range) && 
			(m_startNode->x - m_endNode->x >= -range) &&
			(m_startNode->y - m_endNode->y <= range) && 
			(m_startNode->y - m_endNode->y >= -range);
	}

	void PathFinding::Show()
	{		
		for (int x = 0; x < m_mapWidth; ++x)
		{
			for (int y = 0; y < m_mapHeight; ++y)
			{
				Node* currentNode = &m_nodes[x * m_mapWidth + y];

				if (currentNode == m_startNode)
					std::cout << "S "; // ���� ���
				else if (currentNode == m_endNode)
					std::cout << "E "; // ��ǥ ���
				else if (currentNode->obstacle)
					std::cout << "# "; // ��ֹ�
				else if (std::find(m_finalPath.begin(), m_finalPath.end(), currentNode) != m_finalPath.end())
					std::cout << "* "; // ���� ��ο� ���ԵǴ� ���
				else if (currentNode->visited)
					std::cout << "_ "; // �湮�� ���
				else
					std::cout << ". "; // �� ����
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

	void PathFinding::SetStartNode(const int& x, const int& y)
	{
		int index = x * m_mapWidth + y;
		//if (m_nodes[index].obstacle == false)
		//{
		//	m_startNode = &m_nodes[index];
		//}
		//else
		//{
		//	std::cout << "�ش� ��ġ�� ��ֹ��� ����" << std::endl;
		//	m_isTherePath = false;
		//}
		m_startNode = &m_nodes[index];
	}

	void PathFinding::SetStartNode(const MathEngine::Vector2& startPos)
	{
		std::pair<MathEngine::Vector2, MathEngine::Vector2> temp = m_findPotition->FindNearest(startPos);
		SetStartNode((int)temp.first.x, (int)temp.first.y);
	}

	void PathFinding::SetEndNode(const int& x, const int& y)
	{
		int index = x * m_mapWidth + y;
		//if (m_nodes[index].obstacle == false)
		//{
		//	m_endNode = &m_nodes[index];
		//}
		//else
		//{
		//	std::cout << "�ش� ��ġ�� ��ֹ��� ����" << std::endl;
		//	m_isTherePath = false;
		//}
		m_endNode = &m_nodes[index];
	}

	void PathFinding::SetEndNode(const MathEngine::Vector2& endPos)
	{
		std::pair<MathEngine::Vector2, MathEngine::Vector2> temp = m_findPotition->FindNearest(endPos);
		SetEndNode((int)temp.first.x, (int)temp.first.y);
	}

	void PathFinding::SetObstacle(const int& x, const int& y)
	{
		int index = y * m_mapWidth + x;
		m_nodes[index].obstacle = true;
	}

	void PathFinding::RemoveObstacle(const int& x, const int& y)
	{
		int index = y * m_mapWidth + x;
		m_nodes[index].obstacle = false;
	}

	int PathFinding::GetFinalPathNodeSize() const
	{
		return m_finalPath.size();
	}

	MathEngine::Vector2 PathFinding::GetLocation(const int& indx) const
	{
		Node* backNode = m_finalPath[indx];
		MathEngine::Vector2 key = { (float)backNode->x, (float)backNode->y };
		MathEngine::Vector2 val = m_findPotition->m_mapData[key];

		return val;
	}

}