#pragma once
class BattleChara
{
public:
	BattleChara();
	~BattleChara();


	int getHp(void);
	void setHp(int hp);
	//damage can be negative when getting healed
	void takeDamage(int damage);
	int getAtk(void);
	void setAtk(int atk);
	int getSpeed(void);
	void setSpeed(int speed);
	int getMovePoint(void);
	void setMovePoint(int movePoint);
private:
	int hp;
	int atk;
	int speed;
	int movePoint;
};

