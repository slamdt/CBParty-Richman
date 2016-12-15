//
//  BattleScene.cpp
//  DoTaBattle
//
//  Created by yuyu on 15-7-15.
//
//

#include "BattleLayer.h"
#include "HeroModel.h"

BattleLayer::~BattleLayer() {
    players->removeAllObjects();
    players->release();
    players = NULL;
}

bool BattleLayer::init() {
    if (!BaseLayer::init()) {
        return false;
    }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    players = CCArray::create();
    players->retain();
    
    HeroController *playerSelf = HeroController::create("ailisi_1",true);
    playerSelf->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.5));
    this->addChild(playerSelf);
    players->addObject(playerSelf);
    
    HeroController *playerEnermy = HeroController::create("ailun_1");
    this->addChild(playerEnermy);
    playerEnermy->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.5));
    players->addObject(playerEnermy);
    
    selfFight = CCMenuItemLabel::create(CCLabelTTF::create("攻击(点我点我)", FONT_NAME, 20), this,menu_selector(BattleLayer::Fight));
    selfFight->setTag(PLAYER_SELF);
    selfFight->setPosition(ccp(winSize.width * 0.3, winSize.height * 0.3));
    
    enermyFight = CCMenuItemLabel::create(CCLabelTTF::create("攻击(点我点我)", FONT_NAME, 20), this,menu_selector(BattleLayer::Fight));
    enermyFight->setTag(PLAYER_ENERMY);
    enermyFight->setPosition(ccp(winSize.width * 0.7, winSize.height * 0.3));
    
    
    CCMenuItemLabel *insertSortBtn = CCMenuItemLabel::create(CCLabelTTF::create("插入排序", FONT_NAME, 20), this, menu_selector(BattleLayer::sortForYqq));
    insertSortBtn->setTag(INSERT_SORT);
    insertSortBtn->setAnchorPoint(ccp(0, 0.5));
    insertSortBtn->setPosition(ccp(0, winSize.height * 0.7));
    
    CCMenuItemLabel *quickSortBtn = CCMenuItemLabel::create(CCLabelTTF::create("快速排序", FONT_NAME, 20), this, menu_selector(BattleLayer::sortForYqq));
    quickSortBtn->setTag(QUICK_SORT);
    quickSortBtn->setAnchorPoint(ccp(0, 0.5));
    quickSortBtn->setPosition(ccp(0, winSize.height * 0.6));
    
    CCMenuItemLabel *heapSortBtn = CCMenuItemLabel::create(CCLabelTTF::create("堆排序", FONT_NAME, 20), this, menu_selector(BattleLayer::sortForYqq));
    heapSortBtn->setTag(HEAP_SORT);
    heapSortBtn->setAnchorPoint(ccp(0, 0.5));
    heapSortBtn->setPosition(ccp(0, winSize.height * 0.5));
    
    CCMenuItemLabel *mergeSortBtn = CCMenuItemLabel::create(CCLabelTTF::create("合并排序", FONT_NAME, 20), this, menu_selector(BattleLayer::sortForYqq));
    mergeSortBtn->setTag(MERGE_SORT);
    mergeSortBtn->setAnchorPoint(ccp(0, 0.5));
    mergeSortBtn->setPosition(ccp(0, winSize.height * 0.4));
    
    CCMenu *menu = CCMenu::create(selfFight,enermyFight,insertSortBtn,quickSortBtn,heapSortBtn,mergeSortBtn,NULL);
    menu->setPosition(0, 0);
    this->addChild(menu);
    
    return true;
}

void BattleLayer::setButtonEnable(bool status) {
    selfFight->setEnabled(status);
    enermyFight->setEnabled(status);
}

void BattleLayer::Fight(cocos2d::CCObject *pSender, cocos2d::CCTouch *pTouch) {
    setButtonEnable(false);
    playerTurn = dynamic_cast<CCNode*>(pSender)->getTag();
    ((HeroController*)players->objectAtIndex(playerTurn))->fight(FIGHT_ATTACT,this,callfunc_selector(BattleLayer::FightOver));;
}

void BattleLayer::FightOver() {
    playerTurn = playerTurn == PLAYER_SELF ? PLAYER_ENERMY : PLAYER_SELF;
    ((HeroController*)players->objectAtIndex(playerTurn))->fight(FIGHT_DEFENSE,this,callfunc_selector(BattleLayer::defenseOver));
}

void BattleLayer::defenseOver() {
//    setButtonEnable(true);
    ((HeroController*)players->objectAtIndex(playerTurn))->fight(FIGHT_CHAOFENG,this,callfunc_selector(BattleLayer::continueFight));
}

void BattleLayer::continueFight() {
    ((HeroController*)players->objectAtIndex(playerTurn))->fight(FIGHT_ATTACT,this,callfunc_selector(BattleLayer::FightOver));;
}


void BattleLayer::sortForYqq(cocos2d::CCObject *pSender, cocos2d::CCTouch *pTouch) {
    int sort_type = dynamic_cast<CCNode*>(pSender)->getTag();
    Sort(sort_type);
}

using namespace std;

void BattleLayer::Sort(int type) {
    int array_size = 7;
    int in_array[7] = {48, 10, 9, 16, 5, 4, 2};
    int* out_array = NULL;
    
    switch (type) {
        case INSERT_SORT:
            out_array = InsertionSort(in_array, array_size);
            break;
        case QUICK_SORT:
            QuickSort(in_array, 0, array_size - 1);
            out_array = in_array;
            break;
        case HEAP_SORT:
            HeapSort(in_array, array_size);
            out_array = in_array;
            break;
        case MERGE_SORT:
            MergeSort(in_array, 0, array_size - 1);
            out_array = in_array;
            break;
    }
    
    if (out_array == NULL)
        return;
    for (int i = 0; i < array_size; ++i) {
        cout<<out_array[i]<<" ";
    }
    cout<<endl;
}

////////////////////////////////////////////插入排序////////////////////////////////////////////
int*  BattleLayer::InsertionSort(int* array, int size) {
        int* out_array = new int[size];
        for(int i = 0; i < size; ++i)
        {
            int tmp = array[i];
            
            int j = i - 1;
            while(j >= 0 && tmp < out_array[j])
            {
                out_array[j + 1] = out_array[j];
                --j;
            }
            
            out_array[j + 1] = tmp;
        }
        
        return out_array;
}

////////////////////////////////////////////合并排序////////////////////////////////////////////

void BattleLayer::MergeSort(int* array, int p, int r)
{
    int q = (p + r) / 2;
    if (p < r)
    {
        MergeSort(array, p, q);
        MergeSort(array, q + 1, r);
        Merge(array, p, q, r);
    }
}

void BattleLayer::Merge(int* array, int p, int q, int r)
{
    int size_a = q - p + 1;
    int* array_a = new int[size_a];
    int i_a = 0;
    for(int i = p; i <= q; ++i)
    {
        array_a[i_a] = array[i];
        ++i_a;
    }
    
    int size_b = r - q;
    int* array_b = new int[size_b];
    int i_b = 0;
    for(int i = q + 1; i <= r; ++i)
    {
        array_b[i_b] = array[i];
        ++i_b;
    }
    
    int i = 0, j= 0;
    int k = p;
    while(i < size_a && j < size_b)
    {
        if (array_a[i] < array_b[j])
        {
            array[k] = array_a[i];
            ++i;
        }
        else
        {
            array[k] = array_b[j];
            ++j;
        }
        ++k;
    }
    
    while(i < size_a)
    {
        array[k] = array_a[i];
        ++i;
        ++k;
    }
    
    while(j < size_b)
    {
        array[k] = array_b[j];
        ++j;
        ++k;
    }
}

////////////////////////////////////////////堆排序////////////////////////////////////////////

void BattleLayer::HeapSort(int* array, int size)
{
    BuildMaxHeap(array, size);
    
    while(size > 1)
    {
        int temp = array[size - 1];
        array[size - 1] = array[0];
        array[0] = temp;
        
        --size;
        MaxHeap(array, size, 1);
    }
}

//构建大堆
void BattleLayer::BuildMaxHeap(int* array, int size)
{
    int k = size / 2;       //第一个非叶子节点
    for(int i = k; i > 0; i--)
    {
        MaxHeap(array, size, i);
    }
}

void BattleLayer::MaxHeap(int* array, int size, int i)
{
    int left_i = 2 * i;
    int right_i = left_i + 1;
    
    int largest = i;
    if ( left_i <= size && array[largest - 1] < array[left_i - 1])
        largest = left_i;
    if( right_i <= size && array[largest - 1] < array[right_i - 1])
        largest = right_i;
    
    if (largest == i)
        return;
    int temp = array[i - 1];
    array[i - 1] = array[largest - 1];
    array[largest - 1] = temp;
    
    MaxHeap(array, size, largest);
}

////////////////////////////////////////////快速排序////////////////////////////////////////////

void BattleLayer::QuickSort(int* array, int p, int r)
{
    if (p >= r)
        return;
    int q = Partition(array, p, r);
    //cout << "q " << q << endl;
    QuickSort(array, p, q - 1);
    QuickSort(array, q + 1, r);
}

int BattleLayer::Partition(int* array, int p, int r)
{
    int i = p - 1;
    int j = p;
    int key = array[r];
    
    while(j < r)
    {
        if (array[j] < key)
        {
            ++i;
            Swap(array, i, j);
        }
        ++j;
    }
    
    ++i;
    Swap(array, i, r);
    return i;
}

void BattleLayer::Swap(int* array, int i, int j)
{
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}
