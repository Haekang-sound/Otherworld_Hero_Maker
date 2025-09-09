///
/// ��ã�� �˰���
/// ����: https://www.youtube.com/watch?v=icZj67PTFhc
/// 

#pragma once

#include "Vector2.h"

#include <vector>
#include <iostream>

namespace MathEngine { struct Vector2; }

namespace Algorithm 
{
	class FindPosition;

	class PathFinding
	{
	public:
		struct Node
		{
			int x = 0;
			int y = 0;
			bool obstacle = false;
			bool visited = false;
			float globalGoal = FLT_MAX;
			float localGoal = FLT_MAX;
			Node* parent = nullptr;
			std::vector<Node*> neigbours{};
		};

		PathFinding();
		~PathFinding();

		// ���� �о���� 
		void ReadSource(std::string path);

		// ���� ��ġ
		void SetStartNode(const MathEngine::Vector2& startPos);
		void SetStartNode(const int& x, const int& y);

		// ��ǥ ��ġ
		void SetEndNode(const MathEngine::Vector2& endPos);
		void SetEndNode(const int& x, const int& y);

		
		// ��ֹ� ����
		void SetObstacle(const int& x, const int& y);
		void RemoveObstacle(const int& x, const int& y);

		// ������ ��� ��������
		int GetFinalPathNodeSize() const;
		MathEngine::Vector2 GetLocation(const int& indx) const;
		MathEngine::Vector2 NearestLocation() const;

		// ���� ��ġ�� ��ǥ ��ġ�� ���� �� �˻�
		bool onDestination();

		bool GetIsTherePath() const { return m_isTherePath; }

		// ������
		void Show();

		// temp
		FindPosition* m_findPotition;
		std::vector<Node*> m_finalPath;

		void SolveAstar();

	private:
		Node* m_nodes; // ��� �迭
		int m_mapWidth;
		int m_mapHeight;

		Node* m_startNode;
		Node* m_endNode;

		bool m_isTherePath;
		void CreateMap(const int* mapArr, const int& sizeOfX, const int& sizeOfY);

		void Init();
		void UpdateFinalPath();

		// ��ǥ ��ȯ �˰���
		//FindPosition* m_findPotition;

		// ���� ���
	};
}