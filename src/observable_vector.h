#pragma once

#include <algorithm>
#include <memory>
#include <vector>
#include "collection_observer.h"


template <typename T, class Allocator = std::allocator<T>>
class ObservableVector final
{
    typedef typename std::vector<T, Allocator>::size_type size_type;

public:
    ObservableVector() noexcept(noexcept(Allocator())) 
        : ObservableVector(Allocator()) {}
    
    explicit ObservableVector(const Allocator& alloc) noexcept
        : data_(alloc) {}
    
    ObservableVector(size_type count, const T& value, const Allocator& alloc = Allocator())
        : data_(count, value, alloc) {}
    
    explicit ObservableVector (size_type count, const Allocator& alloc = Allocator()) 
        : data_(count, alloc) {}

    ObservableVector (ObservableVector&& other) noexcept
        : data_(other.data) {}
        
    ObservableVector (ObservableVector&& other, const Allocator& alloc) noexcept
        : data_(other.data, alloc) {}

    ObservableVector (std::initializer_list<T> initList, const Allocator& alloc = Allocator()) noexcept
        : data_(initList, alloc) {}    

    template<class InputIt>
    ObservableVector (InputIt first, InputIt last, const Allocator& alloc) noexcept
        : data_(first, last, alloc) {}

    ObservableVector& operator=(const ObservableVector& other)
    {
        if(this != &other)
        {
            data_ = other.data_;
            for(auto observer : observers_)
            {
                if(observer != nullptr)
                {
                    observer->CollectionChanged({CollectionAction::Assing, std::vector<size_t> {}});
                }
            }
        }
        return *this;
    }

    ObservableVector& operator=(ObservableVector&& other)
    {
        if(this != &other)
        {
            data_ = std::move(other.data_);
            for(auto observer : observers_)
            {
                if(observer != nullptr)
                {
                    observer->CollectionChanged({CollectionAction::Assing, std::vector<size_t> {}});
                }
            }
        }
        return *this;
    }
    
    void PushBack(T&& value)
    {
        data_.push_back(value);
        for(auto observer : observers_)
        {
            if(observer != nullptr)
            {
                observer->CollectionChanged({
                    CollectionAction::Add, std::vector<size_t> {data_.size() - 1}
                });
            }
        }
    }

    void PopBack()
    {
        data_.pop_back();
        for(auto observer : observers_)
        {
            if(observer != nullptr)
            {
                observer->CollectionChanged({
                    CollectionAction::Remove, std::vector<size_t> {data_.size() + 1}
                });
            }
        }
    }

    void Clear() noexcept
    {
        data_.clear();
        for(auto observer : observers_)
        {
            if(observer != nullptr)
            {
                observer->CollectionChanged({
                    CollectionAction::Clear, std::vector<size_t> {}
                });
            }
        }
    }

    size_type Size() const noexcept
    {
        return data_.size();
    }

    [[nodiscard]] bool Empty() const noexcept
    {
        return data_.empty();
    }

    void AddOdserver(CollectionObserver * const observer)
    {
        observers_.push_back(observer);
    }

    void RemoveObserver(CollectionObserver const * const observer)
    {
        observers_.erase(
            std::remove(observers_.begin(), observers_.end(), observer), observers_.end()
        );
    }

private:
    std::vector<T, Allocator> data_;
    std::vector<CollectionObserver*> observers_;
};