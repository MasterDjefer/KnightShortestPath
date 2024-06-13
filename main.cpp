#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

class Point
{
public:
    int x;
    int y;

    Point(int iX = -1, int iY = -1) : x(iX), y(iY) {}
    bool operator==(const Point& p) const
    {
        return x == p.x && y == p.y;
    }
};

class Node
{
public:
    Node* parent;
    Point point;
    std::vector<Node> children;

    Node(Node* iParent = nullptr, Point iPoint = Point()) : parent(iParent), point(iPoint) {}
};

std::array<Point, 8> knightDirectionPattern = { Point{-2,1},Point{-1,2},Point{1,2},Point{2,1},Point{2,-1},Point{1,-2},Point{-1,-2},Point{-2,-1} };

bool isPointVisited(const Point& point, const std::vector<Point>& points)
{
    for (std::size_t i = 0; i < points.size(); ++i)
    {
        if (points.at(i) == point)
        {
            return true;
        }
    }
    return false;
}

bool isPointOnTable(const Point& point)
{
    return point.x >= 0 && point.y >= 0 && point.x <= 7 && point.y <= 7;
}

Node searchPath(Node* root, const Point& startPos, const Point& endPos)
{
    std::queue<Node*> q;
    q.push(root);
    std::vector<Point> visited = { startPos };

    while (!q.empty())
    {
        Node* parent = q.front();
        q.pop();

        for (std::size_t i = 0; i < knightDirectionPattern.size(); ++i)
        {
            const Point& direction = knightDirectionPattern.at(i);
            Point newPos(parent->point.x + direction.x, parent->point.y + direction.y);

            if (endPos == newPos)
            {
                return Node(parent, newPos);
            }

            if (isPointOnTable(newPos) && !isPointVisited(newPos, visited))
            {
                visited.push_back(newPos);
                Node *newNode = new Node(parent, newPos);
                parent->children.push_back(newNode);
                q.push(newNode);
            }
        }
    }

    return Node();
}

void printPath(Node* path)
{
    while (path != nullptr)
    {
        std::cout << "(" << (char)(97 + path->point.x) << "; " << path->point.y + 1 << ")" << std::endl;
        path = path->parent;
    }
}

int main()
{
    Point startPos(1, 0);
    Point endPos(0, 1);

    Node root(nullptr, startPos);
    Node path = searchPath(&root, startPos, endPos);

    printPath(&path);
}
