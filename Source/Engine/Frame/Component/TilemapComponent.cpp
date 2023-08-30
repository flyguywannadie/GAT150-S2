#include "TilemapComponent.h"
#include "Frame/Actor.h"
#include "Frame/Scene.h"

namespace max
{
    CLASS_DEFINITION(TilemapComponent)

    bool TilemapComponent::Initialize()
    {
        for (int i = 0; i < tiles.size(); i++)
        {
            int index = tiles[i];
            if (index == 0) continue;

            auto actor = INSTANTIATE(Actor, tileNames[index]);
            if (actor)
            {
                int x = i % numColumns;
                int y = i / numColumns;

                actor->transform.position = m_owner->transform.position + (vec2{ x, y } * size);
                m_owner->m_scene->Add(std::move(actor));
            }
        }

        return true;
    }

    void TilemapComponent::Update(float dt)
    {
        //
    }
        
    void TilemapComponent::Read(const json_t& value)
    {
        READ_DATA(value, numColumns);
        READ_DATA(value, numRows);
        READ_DATA(value, size);
        
        READ_DATA(value, tileNames);
        READ_DATA(value, tiles);
    }

}