#include "SpriteAnimComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Engine.h"

void neu::SpriteAnimComponent::Update()
{
    // Update Frame
    frameTimer += g_time.deltaTime;
    if (frameTimer >= 1.0f / fps)
    {
        frameTimer = 0;
        frame++;
        if (frame > end_frame)
        {
            frame = start_frame;
        }
    }

    // Calculate Source Rect
    Vector2 cellSize = m_texture->GetSize() / Vector2{ num_columns, num_rows };

    int column = (frame - 1) % num_columns;
    int row = (frame - 1) / num_columns;

    source.x = (int)(column * cellSize.x);
    source.y = (int)(row * cellSize.y);
    source.w = (int)(cellSize.x);
    source.h = (int)(cellSize.y);
}

void neu::SpriteAnimComponent::Draw(Renderer& renderer)
{
    enderer.Draw(m_texture, GetSource(), m_owner->m_transform);
}

bool neu::SpriteAnimComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool neu::SpriteAnimComponent::Read(const rapidjson::Value& value)
{
    std::string texture_name;
    READ_DATA(value, texture_name);

    m_texture = g_resources.Get<Texture>(texture_name, g_renderer);

    READ_DATA(value, fps);
    READ_DATA(value, num_columns);
    READ_DATA(value, num_rows);
    READ_DATA(value, start_frame);
    READ_DATA(value, end_frame);

    return true;
}

Rect& neu::SpriteAnimComponent::GetSource()
{
    // calculate source rect 
    Vector2 cellSize = m_texture->GetSize() / Vector2{ num_columns, num_rows };

    int column = (frame - 1) % num_columns;
    int row = (frame - 1) / num_columns;

    source.x = (int)(column * cellSize.x);
    source.y = (int)(row * cellSize.y);
    source.w = (int)(cellSize.x);
    source.h = (int)(cellSize.y);

    return source;
}
