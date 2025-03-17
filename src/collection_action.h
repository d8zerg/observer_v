#pragma once

#include <string>
#include <vector>


enum class CollectionAction
{
    Add,
    Remove,
    Clear,
    Assing
};

std::string to_string(CollectionAction const action)
{
    switch (action)
    {
        case CollectionAction::Add:     return "<add>";
        case CollectionAction::Remove:  return "<remove>";
        case CollectionAction::Clear:   return "<clear>";
        case CollectionAction::Assing:  return "<assing>";
    }
}

struct CollectionChangeNotification
{
    CollectionAction action;
    std::vector<size_t> itemIndexes;
};

