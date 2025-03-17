#include <iostream>
#include "observable_vector.h" 
#include "observer.h"


int main()
{
    ObservableVector<int> vec;
    Observer observer;

    vec.AddOdserver(&observer);
    vec.PushBack(1);
    vec.PushBack(2);
    vec.PushBack(3);
    vec.PopBack();
    vec.Clear();

    vec.RemoveObserver(&observer);
    vec.PushBack(4);
    vec.PushBack(5);

    vec.AddOdserver(&observer);
    ObservableVector<int> vec2 {1, 2, 3};
    vec = vec2;
    vec = ObservableVector<int> {4, 5, 6};
    
    return 0;
}