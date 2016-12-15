//
//  BattleScene.h
//  DoTaBattle
//
//  Created by yuyu on 15-7-15.
//
//

#ifndef __DoTaBattle__BattleScene__
#define __DoTaBattle__BattleScene__

#include "BaseLayer.h"
#include "HeroController.h"

class BattleLayer : public BaseLayer{
public:
    CREATE_FUNC(BattleLayer)
    virtual bool init();
    void Fight(CCObject *pSender, CCTouch *pTouch);
    void FightOver();
    void defenseOver();
    void setButtonEnable(bool status);
    void continueFight();
    void sortForYqq(CCObject* pSender, CCTouch *pTouch);
    void Sort(int sort_type);
    
private:
    int* InsertionSort(int* array, int size);
    
    void MergeSort(int* array, int p, int r);
    void Merge(int* array, int p, int q, int r);
    
    void HeapSort(int* array, int size);
    void BuildMaxHeap(int* array, int size);
    void MaxHeap(int* array, int size, int i);
    
    void QuickSort(int* array, int p, int r);
    int  Partition(int* array, int p, int r);
    void Swap(int*array, int i, int j);
    
private:
    enum {
        PLAYER_SELF = 0,
        PLAYER_ENERMY,
    };
    enum {
        INSERT_SORT = 0,
        QUICK_SORT,
        HEAP_SORT,
        MERGE_SORT
    };
    CCMenuItemLabel *selfFight;
    CCMenuItemLabel *enermyFight;
    CCArray *players;
    int playerTurn;
    ~BattleLayer();
};

#endif /* defined(__DoTaBattle__BattleScene__) */
