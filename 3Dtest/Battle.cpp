#include "stdafx.h"
#include "Battle.h"
#include "input.h"


Battle::Battle()
{
	commandMeum = new MeumUI();
	UI* ui = new UI({ 0, 0 }, 200, 200, 0);
	UI* ui1 = new UI({ 20, 20 }, 50, 50, 1);
	UI* ui2 = new UI({ 80, 20 }, 50, 50, 1);
	ui2->setStr("ATTACK");
	UI* ui3 = new UI({ 80, 80 }, 50, 50, 1);
	ui3->setStr("RUN");
	commandMeum->addOptins(ui2);
	commandMeum->addOptins(ui3);
	commandMeum->setBackground(ui);
	commandMeum->setPointer(ui1);
	commandMeum->setPosition({ 0, Common::screen_height - ui->getHeight() });

	action = NULL;
}


Battle::~Battle()
{
}

void Battle::start(void)
{
	switch (bs)
	{
	case BattleStateStandby:
		standbyPhase();
		break;
	case BattleStateCommand:
		commandPhase();
		break;
	case BattleStateTaragetSelect:
		taragetSelectPhase();
		break;
	case BattleStateMove:
		movePhase();
		break;
	case BattleStatePlaceSelect:
		placeSelectPhase();
		break;
	case BattleStateDamage:
		damagePhase();
		break;
	case BattleStateMapMove:
		mapMovePhase();
		break;
	case BattleStateEnd:
		endPhase();
		break;
	}
}

void Battle::standbyPhase(void)
{
	actionList[nowActionChara]->getBattleChara()->calStatus();
	if (checkDead(actionList[nowActionChara]))
	{
		bs = BattleState::BattleStateEnd;
	}
	if (action != NULL)
	{
		delete action;
	}
	action = new Action;
	action->active = actionList[nowActionChara];
}

void Battle::commandPhase(void)
{

	switch (as)
	{
	case ActionPhaseStatus::ActionPhaseStatusActionSelect:
		readCommand();
		break;
	case ActionPhaseStatus::ActionPhaseStatusTargetSelect:
		selectTarget();
		break;
	case ActionPhaseStatus::ActionPhaseStatusSkillSelect:
		seleteSkill();
		break;
	}
}

void Battle::taragetSelectPhase(void)
{
}

void Battle::movePhase(void)
{
}

void Battle::placeSelectPhase(void)
{
}

void Battle::damagePhase(void)
{
}

void Battle::mapMovePhase(void)
{
}

void Battle::endPhase(void)
{
}

void Battle::calActionList(void)
{
	int charaNum = charas.size();
	actionList.clear();
	if (actionList.size() <= 0)
	{
		for (int i = 0; i < charaNum; i++)
		{
			if (charas[i]->getBattleChara()->getHpNow() >= 0)
			{
				actionList.push_back(charas[i]);
			}
		}
	}

	int actionNum = charas.size();
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

void Battle::readCommand(void)
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
		}
	}
}

void Battle::selectTarget(void)
{
}

void Battle::seleteSkill(void)
{
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
	charas.push_back(chara);
}

void Battle::createTagatMeum(vector<Chara*> list)
{
	commandMeum->cleanOption();
	int listNum = list.size();
	for (int i = 0; i < listNum; i++)
	{
		UI* ui = new UI({ 0, 0 }, 200, 200, 0);
	}

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
