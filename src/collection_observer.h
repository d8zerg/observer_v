#pragma once

#include "collection_action.h"


class CollectionObserver
{
public:
    virtual void CollectionChanged(CollectionChangeNotification notification) = 0;
    virtual ~CollectionObserver() {}
};

