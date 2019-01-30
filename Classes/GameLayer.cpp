#include "GameLayer.h"
#include "SceneManager.h"

USING_NS_CC;
using namespace std;

GameLayer::GameLayer()
{

}

GameLayer::~GameLayer()
{

}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	makeField();

	makeControlButton();

	startGame();

	return true;
}

void GameLayer::makeField()
{
	Size winSize = Director::getInstance()->getWinSize();

	for (int i = 0; i < FIELD_HEIGHT; i++)
	{
		for (int k = 0; k <= FIELD_WIDTH_RIGHT_INDEX - FIELD_WIDTH_LEFT_INDEX; k++)
		{
			LabelTTF* field = LabelTTF::create(u8"□", "Arial", 12.0f);
			field->setPosition(winSize.width * (0.32 + k * 0.04), winSize.height * (0.1 + i * 0.04));
			field->setColor(Color3B(128, 128, 128));
			this->addChild(field);
		}
	}
}

void GameLayer::makeControlButton()
{
	Size winSize = Director::getInstance()->getWinSize();

	LabelTTF* moveLeftLabel = LabelTTF::create(u8"左", "Arial", 24.0f);
	MenuItemLabel* moveLeft = MenuItemLabel::create(moveLeftLabel, this, menu_selector(GameLayer::tapMoveLeft));
	moveLeft->setPosition(winSize.width * 0.1, winSize.height * 0.2);

	LabelTTF* moveRightLabel = LabelTTF::create(u8"右", "Arial", 24.0f);
	MenuItemLabel* moveRight = MenuItemLabel::create(moveRightLabel, this, menu_selector(GameLayer::tapMoveRight));
	moveRight->setPosition(winSize.width * 0.2f, winSize.height * 0.2);

	LabelTTF* turnLeftLabel = LabelTTF::create(u8"左", "Arial", 24.0f);
	MenuItemLabel* turnLeft = MenuItemLabel::create(turnLeftLabel, this, menu_selector(GameLayer::tapTurnLeft));
	turnLeft->setPosition(winSize.width * 0.8, winSize.height * 0.2);

	LabelTTF* turnRightLabel = LabelTTF::create(u8"右", "Arial", 24.0f);
	MenuItemLabel* turnRigth = MenuItemLabel::create(turnRightLabel, this, menu_selector(GameLayer::tapTurnRight));
	turnRigth->setPosition(winSize.width * 0.9, winSize.height * 0.2);

	Menu* menu = Menu::create(moveLeft, moveRight, turnLeft, turnRigth, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
}

void GameLayer::tapMoveLeft(Ref* pSender)
{
	game->moveLeft();
	moveChunk();
}

void GameLayer::tapMoveRight(cocos2d::Ref* pSender)
{
	game->moveRight();
	moveChunk();
}

void GameLayer::tapTurnLeft(cocos2d::Ref* pSender)
{
	game->chunk->turnLeft();
	moveChunk();
}

void GameLayer::tapTurnRight(cocos2d::Ref* pSender)
{
	game->chunk->turnRight();
	moveChunk();
}

void GameLayer::startGame()
{
	game = new Game();
	this->scheduleOnce(schedule_selector(GameLayer::makeAndMoveChunk), 1.0f);
}

void GameLayer::makeChunk()
{
	int number = lastBlockNumber + 1;
	int numbers[] = {number, number + 1, number + 2, number + 3};
	game->makeChunk(CHUNK_START_X, CHUNK_START_Y, numbers);

	Size winSize = Director::getInstance()->getWinSize();
	
	for (int i = 0; i < CHUNK_HEIGHT; i++)
	{
		for (int k = 0; k < CHUNK_WIDTH; k++)
		{
			if (game->chunk->blocks[i][k] != NULL)
			{
				LabelTTF* label = LabelTTF::create(u8"■", "Arial", 12.0f);
				int x = CHUNK_START_X - FIELD_WIDTH_LEFT_INDEX + k;
				// blocksの座標と画面の座標の開始位置が異なるので調整
				int y = (FIELD_HEIGHT - 1) - (CHUNK_START_Y + i);
				log("[makeChunk]=== x:%d y:%d", x, y);
				label->setPosition(winSize.width * (0.32 + x * 0.04), winSize.height * (0.1 + y * 0.04));
				label->setTag(number);
				number++;
				this->addChild(label);
			}
		}
	}
	lastBlockNumber += 4;
}

void GameLayer::moveUnder(float dt)
{
	if (game->canMoveUnder())
	{
		game->moveUnder();
		moveChunk();
	}
	else
	{
		game->copyBlocks();
		this->unschedule(schedule_selector(GameLayer::moveUnder));
		deleteLines();
		resetIfGameover();
		this->scheduleOnce(schedule_selector(GameLayer::makeAndMoveChunk), 1.0f);
	}
}

void GameLayer::moveChunk()
{
	Size winSize = Director::getInstance()->getWinSize();

	for (int i = 0; i < CHUNK_WIDTH; i++)
	{
		for (int k = 0; k < CHUNK_HEIGHT; k++)
		{
			if (game->chunk->blocks[i][k] != NULL)
			{
				Block* _block = game->chunk->blocks[i][k];
				int number = _block->GetNumber();
				LabelTTF* label = (LabelTTF*)this->getChildByTag(number);
				int x = game->chunk->posX - FIELD_WIDTH_LEFT_INDEX + k;
				int y = (FIELD_HEIGHT - 1) - (game->chunk->posY + i);
				label->setPosition(winSize.width * (0.32f + x * 0.04), winSize.height * (0.1 + y * 0.04));
				log("[showChunk]=== x:%d y:%d", x, y);
			}
		}
	}
}

void GameLayer::makeAndMoveChunk(float dt)
{
	makeChunk();
	this->schedule(schedule_selector(GameLayer::moveUnder), 0.25f);
}

void GameLayer::deleteLines()
{
	if (game->checkDeletableLines())
	{
		for (int i = 0; i < FIELD_HEIGHT; i++)
		{
			if (game->deletableLines[i])
			{
				for (int k = 0; k < FIELD_WIDTH; k++)
				{
					if (game->field->blocks[i][k] != NULL)
					{
						Block* _block = game->field->blocks[i][k];
						int number = _block->GetNumber();
						this->removeChildByTag(number);
					}
				}
			}
		}

		game->deleteDeletableLines();

		Size winSize = Director::getInstance()->getWinSize();

		for (int i = 0; i < FIELD_HEIGHT; i++)
		{
			for (int k = 0; k < FIELD_WIDTH; k++)
			{
				if (game->field->blocks[i][k] != NULL)
				{
					Block* _block = game->field->blocks[i][k];
					int number = _block->GetNumber();
					LabelTTF* label = (LabelTTF*)this->getChildByTag(number);
					int x = k - FIELD_WIDTH_LEFT_INDEX;
					int y = (FIELD_HEIGHT - 1) - i;
					MoveTo* action = MoveTo::create(0.2f, Vec2(winSize.width * (0.32 + x * 0.04), winSize.height * (0.1 + y * 0.04)));
					label->runAction(action);
				}
			}
		}
	}
}

void GameLayer::resetIfGameover()
{
	for (int i = 0; i < FIELD_HEIGHT_UPPER_INDEX; i++)
	{
		for (int k = 0; k < FIELD_WIDTH; k++)
		{
			if (game->field->blocks[i][k] != NULL)
			{
				SceneManager::CreateGameScene();
			}
		}
	}
}