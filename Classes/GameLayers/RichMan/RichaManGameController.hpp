//
//  RichaManGameController.hpp
//  DoTaBattle
//
//  Created by Yu Yu on 2017/4/1.
//
//

#ifndef RichaManGameController_hpp
#define RichaManGameController_hpp

#include "RichManPlayer.hpp"
#include "RichManMapNode.hpp"
#define RichManGameController_ RichManGameController::shared()

enum GAMETURN {
    PLAYER_TURN = 0,
    NPC_TURN
};

class RichManGameController : public CCObject {
public:
    SINGLETON(RichManGameController)
    void addMapNodes(RichManMapNode* node);
    void setPlayer(RichManPlayer* _player, bool isNPC);
    void gameStart();
    const char* getPlayerName(bool isNPC);
    void setForwardBlocks(int block);
    void move();
    void moveOver();
    void next();
private:
    CCArray* mapNodes;
    RichManPlayer* player;
    RichManPlayer* NPC;
    int curRound;
    int curTurn;
    int forwardBlocks;
    RichManMapNode* endNode;
    int mapSize;
};

#endif /* RichaManGameController_hpp */
