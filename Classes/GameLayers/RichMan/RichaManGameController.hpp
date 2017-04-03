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
    PLAYER1_TURN = 0,
    PLAYER2_TURN
};
enum QUESTIONTYPE {
    TANG_SHI = 0,
    SONG_CI
};

enum PLAYERID {
    PLAYER_1 = 0,
    PLAYER_2
};

enum RICHMANPOPTYPE {
    GAME_START = 0, //游戏开始倒计时
    GAME_FORWARD, //游戏摇骰子
    GAME_BUILD, //游戏设置题库
    GAME_CROSS, //游戏路过被占据的地方
    GAME_RANDOM, //触发随机事件
    GAME_SHOP, //进入商城
};

enum RANDOMTYPE {
    RANDOM_INCREASE_SCORE = 0,
    RANDOM_DECREASE_SCORE,
    RANDOM_STOP_FOR_2_ROUND
};

enum GAMEMODEL {
    PLAY_WITH_PLAYER = 0,
    PLAY_WITH_NPC
};

enum EDITBOXTYPE{
    EDIT_SELF = 0,
    EDIT_FRIEND
};

class RichManGameController : public CCObject {
public:
    SINGLETON(RichManGameController)
    void resetData();
    void addMapNodes(RichManMapNode* node);
    void setPlayer(RichManPlayer* _player, int playerId);
    void setPlayerName(int editType, const char* playerName);
    bool checkPlayerName();
    bool getIsPlayWithNPC();
    RichManPlayer* getCurPlayer();
    void gameStart();
    const char* getPlayerName(int playerId);
    const char* getTheOtherPlayerName(int playerId);
    void setForwardBlocks(int block);
    int getCurPlayerScore();
    int getCurPlayerId();
    const char* getCurPlayerName();
    void setCurPlayerScore(int scoreDelta);
    Json::Value& setQuestion(int questionType);
    bool getCurPlayerIsNPC();
    Json::Value& getCurHolderInfo();
    void reduceHolderQuestions(int reduceSize);
    void grabHolder(int questionType);
    void freeHoldedBlock();
    void answerWrong();
    void setRestRound(int restRounds);
    void setGameModel(int model);
    void move();
    void moveOver();
    void next();
private:
    CCArray* mapNodes;
    RichManPlayer* player1;
    RichManPlayer* player2;
    int curRound;
    int curTurn;
    int forwardBlocks;
    RichManMapNode* endNode;
    int mapSize;
    std::string player1Name;
    std::string player2Name;
    Json::Value tangshiLib;
    Json::Value songciLib;
    int gameModel;
};

#endif /* RichaManGameController_hpp */
