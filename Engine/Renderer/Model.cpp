#include "Model.h"
#include "../Core/File.h"

#include <iostream>
#include <sstream>
namespace neu
{
    Model::Model(const std::string& filename)
    {
        Load(filename);
        m_radius = CalculateRadius();
    }
    void Model::Draw(Renderer& renderer, Vector2& position, float angle, float scale)
    {

        //Draw Model
        for (int i = 0; i < m_points.size() - 1; i++)
        {
            neu::Vector2 p1 = Vector2::Rotate((m_points[i] * scale), angle) + position;
            neu::Vector2 p2 = Vector2::Rotate((m_points[i + 1] * scale), angle) + position;

            renderer.DrawLine(p1, p2, m_color);
        }
    }

    void Model::Load(const std::string& filename)
    {
        std::string buffer; 

        neu::ReadFile(filename, buffer);

        //Read Color
        std::istringstream stream(buffer);
        stream >> m_color;

        // Read number of points
        std::string line;
        std::getline(stream, line);

        // Get Number of Points
        size_t numPoints = std::stoi(line);
        
        // Read Model Points
        for (size_t i = 0; i < numPoints; i++)
        {
            Vector2 point;

            stream >> point;

            m_points.push_back(point);
        }
    }

    float Model::CalculateRadius()
    {
        float radius = 0;

        // Find the largest length (radius)
        for (auto& point : m_points)
        {
            if (point.Length() > radius) radius = point.Length();
        }

        return radius;
    }

}
