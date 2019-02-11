#include "stdafx.h"
#include "Battle.h"
#include "Common.h"
#include "input.h"
#include "Enemy.h"
#include "math.h"
#include "MovePerform.h"
#include "ForceMovePerform.h"


Battle::Battle()
{
	bs = BattleState::BattleStateBegin;
	lastBs = BattleState::BattleStateBegin;
	action = NULL;
#ifdef SKILL_EFFICIENCY
	skillEfficiency = SKILL_EFFICIENCY;
#else
	skillEfficiency = 1.0;
#endif
#ifdef DEFENSE_EFFICIENCY
	defEfficiency = DEFENSE_EFFICIENCY;
#else
	defEfficiency = 1.0;
#endif
}

Battle::Battle(MapManage *map, PerformManage *pm, MeumUI* commandMeum, MeumUI* textBox, MeumUI* statusBox, Player* movePointer)
	:map(map), pm(pm), commandMeum(commandMeum), textBox(textBox), statusBox(statusBox), movePointer(movePointer)
{
	bs = BattleState::BattleStateBegin;
	lastBs = BattleState::BattleStateBegin;

	action = NULL;

	createTextBox();
	createStatusBox();

#ifdef SKILL_EFFICIENCY
	skillEfficiency = SKILL_EFFICIENCY;
#else
	skillEfficiency = 1.0;
#endif
#ifdef DEFENSE_EFFICIENCY
	defEfficiency = DEFENSE_EFFICIENCY;
#else
	defEfficiency = 1.0;
#endif
}


Battle::~Battle()
{
	tabDeadEnemy();
	movePointer->setIsDelete(true);
	commandMeum->setIsDelete(true);
	textBox->setIsDelete(true);
	statusBox->setIsDelete(true);
	skillBillboard->setIsDelete(true);
}

void Battle::start(void)
{
	int charasNum = charas.size();
	for (int i = 0; i < charasNum; i++)
	{
		if (typeid(*charas[i]) == typeid(Enemy))
		{
			((Enemy*)charas[i])->setIsPatrol(false);
		}
	}

	commandMeum->setIsReadInput(false);

	switch (bs)
	{
	case BattleStateBegin:
		beginPhase();
		break;
	case BattleStateStandby:
		standbyPhase();
		break;
	case BattleStateCommand:
		commandPhase();
		break;
	case BattleStateMove:
		movePhase();
		break;
	case BattleStateDamage:
		damagePhase();
		break;
	case BattleStateEnd:
		endPhase();
		break;
	case BattleStateMapMove:
		mapMovePhase();
		break;
	}
	calStatusMessage();
}

BOOL Battle::checkEnd(void)
{
	int playerNum = 0, enemyNum = 0;
	int charaNum = charas.size();
	for (int i = 0; i < charaNum; i++)
	{
		if (charas[i]->getBattleChara()->getHpNow() > 0)
		{
			switch (charas[i]->getBattleChara()->getCamp())
			{
			case CampType::CampTypePlayer:
				playerNum++;
				break;
			case CampType::CampTypeEnemy:
				enemyNum++;
				break;
			}
		}
		if (playerNum > 0 && enemyNum > 0)
		{
			return 0;
		}
	}
	if (playerNum <= 0 && enemyNum > 0)
	{
		return -1;
	}
	if (playerNum > 0 && enemyNum <= 0)
	{
		return 1;
	}
	return 0;
}

void Battle::changeBattleState(BattleState newbs)
{
	bs = newbs;
	switch (newbs)
	{
	case BattleState::BattleStateStandby:
		primitivePosition = actionList[nowActionChara]->getBoundingCenter();
		break;
	case BattleState::BattleStateCommand:
		as = ActionPhaseStatus::ActionPhaseStatusActionSelect;
		lastAs = ActionPhaseStatusActionZero;
		if (action != NULL)
		{
			delete action;
		}
		action = new Action;
		action->active = actionList[nowActionChara];
		break;
	case BattleState::BattleStateMove:
		movePlace = { 0, 0 };
		break;
	case BattleState::BattleStateMapMove:
		mapMoveStartFrame = Common::frameCount;
		break;
	}
}

void Battle::createTextBox(void)
{
	UI* ui = new UI({ 0, 0 }, Common::screen_width / 3, Common::screen_height / 5, 0);
	textBox->setBackground(ui);
	textBox->setPosition({ Common::screen_width / 3, Common::screen_height - ui->getHeight() });
	textBox->setIsDisplay(true);
}

void Battle::createStatusBox(void)
{
	UI* ui = new UI({ 0, 0 }, Common::screen_width / 3, Common::screen_height / 5, 0);
	statusBox->setBackground(ui);
	statusBox->setPosition({ (Common::screen_width / 3) * 2, Common::screen_height - ui->getHeight() });
	statusBox->setIsDisplay(true);
}

void Battle::beginPhase(void)
{
	lastBs = bs;
	changeBattleState(BattleState::BattleStateStandby);
}

void Battle::standbyPhase(void)
{
	actionList[nowActionChara]->getBattleChara()->calStatus();
	if (checkDead(actionList[nowActionChara]))
	{
		bs = BattleState::BattleStateEnd;
	}

	lastBs = bs;
	changeBattleState(BattleState::BattleStateCommand);
}

void Battle::commandPhase(void)
{
	lastBs = bs;

	textBox->setIsDisplay(true);
	switch (as)
	{
	case ActionPhaseStatus::ActionPhaseStatusActionSelect:
		selectAction();
		break;
	case ActionPhaseStatus::ActionPhaseStatusTargetSelect:
		selectTarget();
		break;
	case ActionPhaseStatus::ActionPhaseStatusSkillSelect:
		seleteSkill();
		break;
	}
}

void Battle::movePhase(void)
{
	plaseSelect();
	lastBs = bs;
}

void Battle::damagePhase(void)
{
	action->damage = calDamageList(action->active, action->passive, action->isUseSkill, action->skill);
	takeDamage();

	lastBs = bs;
	changeBattleState(BattleState::BattleStateEnd);
}

void Battle::mapMovePhase(void)
{
	lastBs = bs;
	if (Common::frameCount - mapMoveStartFrame >= 60)
	{
		changeBattleState(BattleState::BattleStateStandby);
	}
}

void Battle::endPhase(void)
{
	lastBs = bs;
	skillBillboard->setIsDisplay(false);
	if (!checkEnd())
	{
		do
		{
			nowActionChara = (nowActionChara + 1) % actionList.size();
		} while (nowActionChara > 0 && actionList[nowActionChara]->getBattleChara()->getHpNow() <= 0);
		if (nowActionChara == 0)
		{
			calActionList();
			changeBattleState(BattleState::BattleStateMapMove);
			return;
		}
		changeBattleState(BattleState::BattleStateStandby);
	}
}

void Battle::calActionList(void)
{
	int charaNum = charas.size();
	actionList.clear();
	for (int i = 0; i < charaNum; i++)
	{
		if (charas[i]->getBattleChara()->getHpNow() > 0)
		{
			actionList.push_back(charas[i]);
		}
	}

	int actionNum = actionList.size();
	for (int i = 0; i < actionNum; i++)
	{
		for (int j = i + 1; j < actionNum; j++)
		{
			if (actionList[i]->getBattleChara()->getSpeed() < actionList[j]->getBattleChara()->getSpeed())
			{
				Chara *tmp = actionList[i];
				actionList[i] = actionList[j];
				actionList[j] = tmp;
			}
		}
	}
}

void Battle::selectAction(void)
{
	if (typeid(*actionList[nowActionChara]) == typeid(Player))
	{
		if (as != lastAs)
		{
			createActionMeum();
			displayMessage("Is your turn now, please select a action");
		}
		commandMeum->setIsReadInput(true);
		readActionCommand();
	}
	else
	{
		as = ActionPhaseStatus::ActionPhaseStatusTargetSelect;
		lastSelect = -1;
		action->isUseSkill = false;
	}
}

void Battle::readActionCommand(void)
{
	if (Keyboard_IsTrigger(DIK_RETURN))
	{
		switch (commandMeum->getNowPointingIdentity())
		{
		case UIIdentity::UIIdentityAttack:
			as = ActionPhaseStatus::ActionPhaseStatusTargetSelect;
			lastSelect = -1;
			action->isUseSkill = false;
			break;
		case UIIdentity::UIIdentityUseSkill:
			as = ActionPhaseStatus::ActionPhaseStatusSkillSelect;
			lastSelect = 0;
			action->isUseSkill = true;
			break;
		case UIIdentity::UIIdentityMove:
			changeBattleState(BattleState::BattleStateMove);
			break;
		case UIIdentity::UIIdentitySkip:
			changeBattleState(BattleState::BattleStateEnd);
			break;
		}
	}
}

void Battle::selectTarget(void)
{
	if (typeid(*actionList[nowActionChara]) == typeid(Player))
	{
		if (as != lastAs)
		{
			vector<Chara*> taragetList = calTargetList(action->active, action->skill);
			createTagatMeum(taragetList);
			displayMessage("Please select a target");
		}
		commandMeum->setIsReadInput(true);
		readTargetCommand();
	}
	else
	{
		float dis = D3DXVec2Length(&(actionList[0]->getBoundingCenter() - actionList[nowActionChara]->getBoundingCenter()));
		vector<GameObject*> visionList = map->calObjectOnSightOvl(actionList[nowActionChara], actionList[0]);
		if (dis <= actionList[nowActionChara]->getBattleChara()->getMovePoint() && visionList.size() <= 0)
		{	
			action->passive.push_back(actionList[0]);
			addMovePerform(action->active, action->passive[0], 0);
			bs = BattleState::BattleStateDamage;
		}
		else
		{
			bs = BattleState::BattleStateEnd;
		}
	}

}

void Battle::readTargetCommand(void)
{
	if (Keyboard_IsTrigger(DIK_RETURN))
	{
		vector<Chara*> list = calTargetList(action->active, action->skill);
		D3DXVECTOR2 targetCenter = list[commandMeum->getNowPointing()]->getBoundingCenter();
		float dis = D3DXVec2Length(&(primitivePosition - targetCenter));
		float disLimit = action->isUseSkill ? action->skill->getDistance() : actionList[nowActionChara]->getBattleChara()->getMovePoint();
		if (dis <= disLimit)
		{
			vector<GameObject*> visionList = map->calObjectOnSightOvl(actionList[nowActionChara], list[commandMeum->getNowPointing()]);
			if (visionList.size() <= 0)
			{
				action->passive.push_back(list[commandMeum->getNowPointing()]);
				if (!action->isUseSkill)
				{
					addMovePerform(action->active, action->passive[0], 0);
				}
				else
				{
					D3DXVECTOR3 pos = action->active->getBoundingCenter3D();
					pos.y = 3;
					D3DXVECTOR3 targetPos = action->passive[0]->getBoundingCenter3D();
					targetPos.y = 3;
					createSkillModel(action->skill->getTextureIndex(), pos);
					addSkillPerform(skillBillboard, pos, targetPos);
					if (action->skill->getSideEffect()->getType() == SideEffectType::SideEffectTypePull)
					{
						addMovePerform(action->passive[0], action->active, 1);
					}
				}
				bs = BattleState::BattleStateDamage;
			}
			else
			{
				displayMessage("Is not in vision");
			}
		}
		else
		{
			displayMessage("Is too far");
		}
	}

	if (Keyboard_IsTrigger(DIK_Z))
	{
		as = ActionPhaseStatus::ActionPhaseStatusActionSelect;
	}

}

void Battle::seleteSkill(void)
{
	if (as != lastAs)
	{
		createSkillMeum(actionList[nowActionChara]->getBattleChara()->getSkillList());
		displayMessage("Please select a skill to use");
	}
	commandMeum->setIsReadInput(true);
	readSkillCommand();
}

void Battle::readSkillCommand(void)
{
	if (Keyboard_IsTrigger(DIK_RETURN))
	{
		action->isUseSkill = true;
		action->skill = actionList[nowActionChara]->getBattleChara()->getSkillList()[commandMeum->getNowPointing()];
		as = ActionPhaseStatus::ActionPhaseStatusTargetSelect;
	}
	if (Keyboard_IsTrigger(DIK_Z))
	{
		as = ActionPhaseStatus::ActionPhaseStatusActionSelect;
	}
}

void Battle::plaseSelect(void)
{
	if (bs != lastBs)
	{
		resetMovePointer(actionList[nowActionChara]->getBoundingCenter());
		displayMessage("Please select a place to go");
	}
	map->addGameObject(movePointer);
	movePointer->setIsReadInput(true);
	movePointer->setVecSpeedFront(((Player*)actionList[nowActionChara])->getVecSpeedFront());

	readMovePlace();
}

void Battle::resetMovePointer(D3DXVECTOR2 center)
{
	movePointer->setBoundingCenter(center);
	movePointer->setIsDisplay(true);
}

void Battle::readMovePlace(void)
{
	if (Keyboard_IsTrigger(DIK_RETURN))
	{
	//	float dis = D3DXVec2Length(&(actionList[nowActionChara]->getBoundingCenter() - movePointer->getBoundingCenter()));
		float dis = D3DXVec2Length(&(primitivePosition - movePointer->getBoundingCenter()));

		if (dis <= actionList[nowActionChara]->getBattleChara()->getMovePoint())
		{
			vector<GameObject*> list = map->calObjectOnSightOvl(actionList[nowActionChara], movePointer);
			if (list.size() <= 0)
			{
				addMovePerform(actionList[nowActionChara], movePointer, 0);
				movePointer->setIsDisplay(false);
				changeBattleState(BattleState::BattleStateCommand);
			}
			else
			{
				displayMessage("Is not in vision");
			}
		}
		else
		{
			displayMessage("too far");
		}
	}

	if (Keyboard_IsTrigger(DIK_Z))
	{
		movePointer->setIsDisplay(false);
		changeBattleState(BattleState::BattleStateCommand);
	}
}

bool Battle::checkDead(Chara * chara)
{
	if (chara->getBattleChara()->getHpNow() <= 0)
	{
		return true;
	}
	return false;
}

void Battle::addCharas(Chara * chara)
{
	if (!checkCharaIsInBattle(chara))
	{
		charas.push_back(chara);
		calActionList();
	}
}

bool Battle::checkCharaIsInBattle(Chara * chara)
{
	int charaNum = charas.size();
	for (int i = 0; i < charaNum; i++)
	{
		if (charas[i] == chara)
		{
			return true;
		}
	}
	return false;
}

void Battle::createActionMeum(void)
{
	commandMeum->cleanOption();

	UI* ui = new UI({ 0, 0 }, Common::screen_width / 3, Common::screen_height / 5, 0);
	UI* ui1 = new UI({ 0, 0 }, ui->getWidth() / 4, ui->getHeight() / 5, 1);
	UI* ui2 = new UI({ (ui->getWidth() / 4 * 2), (ui->getHeight() / 5) * 1 }, ui->getWidth() / 4, ui->getHeight() / 5, 1);
	ui2->setStr("ATTACK");
	ui2->setIdentity(UIIdentity::UIIdentityAttack);
	UI* ui3 = new UI({ (ui->getWidth() / 4 * 2), (ui->getHeight() / 5) * 2 }, ui->getWidth() / 4, ui->getHeight() / 5, 1);
	ui3->setStr("SKIP");
	ui3->setIdentity(UIIdentity::UIIdentitySkip);
	UI* ui4 = new UI({ (ui->getWidth() / 4 * 2), (ui->getHeight() / 5) * 3 }, ui->getWidth() / 4, ui->getHeight() / 5, 1);
	ui4->setStr("MOVE");
	ui4->setIdentity(UIIdentity::UIIdentityMove);
	UI* ui5 = new UI({ (ui->getWidth() / 4 * 2), (ui->getHeight() / 5) * 4 }, ui->getWidth() / 4, ui->getHeight() / 5, 1);
	ui5->setStr("SKILL");
	ui5->setIdentity(UIIdentity::UIIdentityUseSkill);
	commandMeum->addOptins(ui2);
	commandMeum->addOptins(ui3);
	commandMeum->addOptins(ui4);
	commandMeum->addOptins(ui5);
	commandMeum->setBackground(ui);
	commandMeum->setPointer(ui1);
	commandMeum->setPosition({ 0, Common::screen_height - ui->getHeight() });
	commandMeum->setIsDisplay(true);

	lastAs = ActionPhaseStatus::ActionPhaseStatusActionSelect;
}

void Battle::createSkillMeum(vector<BattleSkill*> list)
{
	commandMeum->cleanOption();
	UI* ui = new UI({ 0, 0 }, Common::screen_width / 3, Common::screen_height / 5, 0);
	commandMeum->setBackground(ui);
	UI* ui1 = new UI({ 0, 0 }, ui->getWidth() / 4, ui->getHeight() / 5, 1);
	commandMeum->setPointer(ui1);
	//commandMeum->setPosition({ 0, 0 });

	int listNum = list.size();
	for (int i = 0; i < listNum; i++)
	{
		ui1 = new UI({ (ui->getWidth() / 4 * 2), (ui->getHeight() / (listNum + 2)) * (i + 1) }, ui->getWidth() / 4, ui->getHeight() / (listNum + 2), 1);
		ui1->setStr(list[i]->getName());
		commandMeum->addOptins(ui1);
	}

	lastAs = ActionPhaseStatus::ActionPhaseStatusSkillSelect;
}

void Battle::createTagatMeum(vector<Chara*> list)
{
	commandMeum->cleanOption();
	UI* ui = new UI({ 0, 0 }, Common::screen_width / 3, Common::screen_height / 5, 0);
	commandMeum->setBackground(ui);
	UI* ui1 = new UI({ 0, 0 }, ui->getWidth() / 4, ui->getHeight() / 5, 1);
	commandMeum->setPointer(ui1);
//	commandMeum->setPosition({ 0, 0 });

	int listNum = list.size();
	for (int i = 0; i < listNum; i++)
	{
		ui1 = new UI({ (ui->getWidth() / 4 * 2), (ui->getHeight() / (listNum + 2)) * (i + 1) }, ui->getWidth() / 4, ui->getHeight() / (listNum + 2), 1);
		ui1->setStr(list[i]->getBattleChara()->getName());
		commandMeum->addOptins(ui1);
	}

	lastAs = ActionPhaseStatus::ActionPhaseStatusTargetSelect;
}

vector<Chara*> Battle::calTargetList(Chara * acvite, BattleSkill * skill)
{
	vector<Chara*> list;
	EffectTarget eTar;
	if (skill == NULL)
	{
		eTar = EffectTarget::EffectTargetEnemy;
	}
	else
	{
		eTar = skill->getMainTarget();
	}
	CampType acvCamp = acvite->getBattleChara()->getCamp();
	CampType targetCamp;
	if (acvCamp == CampType::CampTypePlayer)
	{
		if (eTar == EffectTarget::EffectTargetAllEnemy || eTar == EffectTarget::EffectTargetEnemy)
		{
			targetCamp = CampType::CampTypeEnemy;
		}
		else if (eTar == EffectTarget::EffectTargetAllFriendly || eTar == EffectTarget::EffectTargetFriendly)
		{
			targetCamp = CampType::CampTypePlayer;
		}
	}
	else
	{
		if (eTar == EffectTarget::EffectTargetAllEnemy || eTar == EffectTarget::EffectTargetEnemy)
		{
			targetCamp = CampType::CampTypePlayer;
		}
		else if (eTar == EffectTarget::EffectTargetAllFriendly || eTar == EffectTarget::EffectTargetFriendly)
		{
			targetCamp = CampType::CampTypeEnemy;
		}
	}

	int num = actionList.size();
	for (int i = 0; i < num; i++)
	{
		if (actionList[i]->getBattleChara()->getCamp() == targetCamp)
		{
			list.push_back(actionList[i]);
		}
	}

	return list;
}

vector<int> Battle::calDamageList(Chara* active, vector<Chara*>passive, bool isUseSkill, BattleSkill* skill)
{
	int targetNum = passive.size();
	vector<int> damage;
	int atk = 0, def = 0;
	for (int i = 0; i < targetNum; i++)
	{
		damage.push_back(calDamageSingle(active->getBattleChara(), passive[i]->getBattleChara(), isUseSkill, skill));
	}
	return damage;
}

int Battle::calDamageSingle(BattleChara * active, BattleChara * passive, bool isUseSkill, BattleSkill * skill)
{
	int damage = 0;
	if (passive->checkEffect(SideEffectType::SideEffectTypeDamageImmune))
	{
		damage = -1;
	}
	else
	{
		if (!isUseSkill)
		{
			
			int atk = active->getAtk();
			int def = 0;
			damage = calDamageVal(atk, def, 0);

			/*int atk = active->getAtk();
			int def = action->passive->getDefense();
			damage = atk - def * DEFENSE_EFFICIENCY + 1 > 1 ?
			atk - def * DEFENSE_EFFICIENCY + 1 : 1;*/
		}
		else
		{
			/*	int atk = skill->getSkillType() == magic ? active->getMAtk() : active->getAtk();

			int def = skill->getSkillType() == magic ? passive->getMDefense() : passive->getDefense();

			damage = atk + skill->getDamage() * SKILL_EFFICIENCY - def * DEFENSE_EFFICIENCY + 1 > 1 ?
			atk + skill->getDamage() * SKILL_EFFICIENCY - def * DEFENSE_EFFICIENCY + 1 : 1);*/
			int atk = active->getAtk();
			int def = 0;
			damage = calDamageVal(atk, def, (int)skill->getDamage());
		}
	}
	return damage;
}

int Battle::calDamageVal(int atk, int def, int skillDamage)
{
	int damage = 1;
	damage = (int)(atk + skillDamage * skillEfficiency - def * defEfficiency);
	damage = damage < 1 ? 1 : damage;
	return damage;
}

void Battle::takeDamage(void)
{
	int targetNum = action->passive.size();
	for (int i = 0; i < targetNum; i++)
	{
		if (action->damage[i] > 0)
		{
			action->passive[i]->getBattleChara()->takeDamage(action->damage[i]);
			if (action->passive[i]->getBattleChara()->getHpNow() <= 0)
			{
				action->passive[i]->setDisappear(true);
			}
		}
	}
}

void Battle::addMovePerform(Chara * act, Chara * target, int flag)
{
	MovePerform *mvp;
	if (flag == 0)
	{
		mvp = new MovePerform();
	}
	else
	{
		mvp = new ForceMovePerform();
	}
	mvp->setActor(act);
	D3DXVECTOR2 actCenter = act->getBoundingCenter();
	D3DXVECTOR2 pasCenter = target->getBoundingCenter();
	D3DXVECTOR2 dis = actCenter - pasCenter;
	RECTF actRect = act->getBoundingRect();
	RECTF pasRect = target->getBoundingRect();
	if (actCenter.x < pasRect.left || actCenter.x > pasRect.right)
	{
		int flag = dis.x >= 0 ? 1 : -1;
		float newX = pasCenter.x + flag * (abs(pasRect.right - pasRect.left) / 2 + abs(actRect.right - actRect.left) / 2);
		mvp->setVecTarget({ newX, act->getVecNowPos()->y, target->getBoundingCenter().y });
	}
	else
	{
		int flag = dis.y >= 0 ? 1 : -1;
		float newY = pasCenter.y + flag * (abs(pasRect.top - pasRect.bottom) / 2 + abs(actRect.top - actRect.bottom) / 2);
		mvp->setVecTarget({ target->getBoundingCenter().x, act->getVecNowPos()->y, newY });
	}
	mvp->setVecStart({ actCenter.x, act->getVecNowPos()->y, actCenter.y});
	mvp->setMoveSpeed(0.1f);
	pm->addPerforms(mvp);
}

void Battle::addSkillPerform(GameObject * act, D3DXVECTOR3 start, D3DXVECTOR3 target)
{
	MovePerform *mvp = new MovePerform();
	mvp->setActor(act);
	mvp->setVecTarget(target);
	mvp->setVecStart(start);
	mvp->setMoveSpeed(0.1f);
	pm->addPerforms(mvp);
}

void Battle::displayMessage(string str)
{
	textBox->setDisplayStr(str);
}

void Battle::tabDeadEnemy(void)
{
	int charaNum = charas.size();
	for (int i = 0; i < charaNum; i++)
	{
		if (charas[i]->getBattleChara()->getHpNow() <= 0)
		{
			charas[i]->setIsDelete(true);
		}
	}
}

void Battle::calStatusMessage(void)
{
	int charasNum = charas.size();
	string displayStr;
	stringstream ss;
	string tmpStr;
	for (int i = 0; i < charasNum; i++)
	{
		displayStr += charas[i]->getBattleChara()->getName();
		displayStr += "         ";

		ss.clear();
		ss << charas[i]->getBattleChara()->getHpNow();
		ss >> tmpStr;
		displayStr += tmpStr;

		displayStr += "/";

		ss.clear();
		ss << charas[i]->getBattleChara()->getHpMax();
		ss >> tmpStr;
		displayStr += tmpStr;

		displayStr += "%";
	}
	statusBox->setDisplayStr(displayStr);
}

void Battle::createSkillModel(int textureIndex, D3DXVECTOR3 position)
{
	skillBillboard->setTextureIndex(textureIndex);
	skillBillboard->setVecNowPos(&position);
	skillBillboard->setIsDisplay(true);
	skillBillboard->setCanMove(true);
}

void Battle::setPerformManager(PerformManage * pm)
{
	this->pm = pm;
}

void Battle::setSkillBillboard(Billboard * billboard)
{
	this->skillBillboard = billboard;
}

void Battle::setMap(MapManage * map)
{
	this->map = map;
}

BattleState Battle::getBattleState(void)
{
	return bs;
}

void Battle::setMovePointer(Player * pointer)
{
	this->movePointer = pointer;
}

void Battle::setSkillEfficiency(float se)
{
	this->skillEfficiency = se;
}

void Battle::setDefEfficiency(float de)
{
	this->defEfficiency = de;
}

void Battle::setCommandMeum(MeumUI * commandMeum)
{
	this->commandMeum = commandMeum;
}

void Battle::setTextBox(MeumUI * textBox)
{
	this->textBox = textBox;
	createTextBox();
}

void Battle::setStatusBox(MeumUI * statusBox)
{
	this->statusBox = statusBox;
}
