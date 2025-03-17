#pragma once

#include <iostream>
#include "collection_observer.h"


class Observer : public CollectionObserver
{
public:
    virtual void CollectionChanged(CollectionChangeNotification notification) override
    {
        std::cout << "action: " << to_string(notification.action);
        if(!notification.itemIndexes.empty())
        {
            std::cout << ", index: ";
            for(auto i : notification.itemIndexes)
            {
                std::cout << i << ' ';
            }
        }
        std::cout << std::endl;
    }
};