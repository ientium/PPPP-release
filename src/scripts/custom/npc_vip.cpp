/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/* ScriptData
SDName: Npc_Professions
SD%Complete: 80
SDComment: Provides learn/unlearn/relearn-options for professions. Not supported: Unlearn engineering, re-learn engineering, re-learn leatherworking.
SDCategory: NPCs
EndScriptData */

#include "scriptPCH.h"

/*
A few notes for future developement:
- A full implementation of gossip for GO's is required. They must have the same scripting capabilities as creatures. Basically,
there is no difference here (except that default text is chosen with `gameobject_template`.`data3` (for GO type2, different dataN for a few others)
- It's possible blacksmithing still require some tweaks and adjustments due to the way we _have_ to use reputation.
*/

/*
-- UPDATE `gameobject_template` SET `ScriptName` = 'go_soothsaying_for_dummies' WHERE `entry` = 177226;
*/



/*############################################################################################################
# VIP商人点数消费
############################################################################################################*/

/*###
# VIP价格定义
###*/

#define GOSSIP_SENDER_INQUIRECOIN                      60   //查询积分
#define GOSSIP_SENDER_INSTANTFLIGHT                    61   //瞬飞操作
#define GOSSIP_SENDER_INSTANTFLIGHT_START              611  //瞬飞开通
#define GOSSIP_SENDER_INSTANTFLIGHT_BACK               612  //瞬飞返回
#define GOSSIP_SENDER_CHANGENAME                       62   //改名
#define GOSSIP_SENDER_CHANGENAME_CHANGE                       621   //改名
#define GOSSIP_SENDER_CHANGENAME_BACK                       622   //改名返回
#define GOSSIP_SENDER_LEVELUP                          63   //等级提升
#define GOSSIP_SENDER_LEVELUP_ONE                     631   //等级提升1级操作
#define GOSSIP_SENDER_LEVELUP_ALL                     632   //等级提升到60级操作
#define GOSSIP_SENDER_LEVELUP_BACK                    633   //等级提升子菜单返回
#define GOSSIP_SENDER_CHANGERACE                       64   //修改种族
#define GOSSIP_SENDER_INQUIRECOIN_CHANGE              601   //修改积分
#define GOSSIP_SENDER_INQUIRECOIN_BACK                602   //积分子菜单返回
#define GOSSIP_SENDER_ADDSKILL                        65   //增加技能
#define GOSSIP_SENDER_ADDSKILL_ONE                        651   //增加一个技能
#define GOSSIP_SENDER_ADDSKILL_MENU                   6502   //技能学满列表子菜单返回
#define GOSSIP_SENDER_ADDSKILL_BACK                   652   //技能学习子菜单返回
#define GOSSIP_SENDER_SKILLSMENU_BACK                 6501   //技能学习，学满技能菜单选择
#define GOSSIP_SENDER_BACK						       59    //返回

#define C_FLYINGMON_COIN          50            //需要50积分开瞬飞一个月
#define C_TIMETOCOIN              7200          //每2小时变化1点积分
#define C_FLYINGMONSECOND         2592000       //瞬飞30天的秒数
#define C_CHANGENAME_COIN         300           //改名需要300点
#define C_LEVELUP_COIN            10            //提升一级需要的点数
#define C_MAXLEVEL_COIN           500           //直接满级需要点数
#define C_NEW_SKILL_COIN          300           //学习新技能的点数
#define C_MAX_SKILL_COIN          1000          //学习满技能的点数

#define GOSSIP_VIP_TEXT_INQUIRECOIN					110015      //"我想查询我的积分"
#define GOSSIP_VIP_TEXT_INSTANTFLIGHT				110016      //"我想了解瞬飞的事"
#define GOSSIP_VIP_TEXT_CHANGENAME					110017      //"我想修改名字"
#define GOSSIP_VIP_TEXT_CHANGENAME_STRING			110018      //"是的,我要修改我的角色名称."
#define GOSSIP_VIP_TEXT_LEVELUP						110019      //"我想提升等级"
#define GOSSIP_VIP_TEXT_CHANGERACE					110020      //"我想改变种族"
#define GOSSIP_VIP_TEXT_ADDSKILL					110031      //"我想学习新技能"
#define GOSSIP_VIP_TEXT_BACK						110021      //"返回"
#define GOSSIP_VIP_TEXT_VENDOR                      110022      //"查看出售物品"
#define GOSSIP_VIP_TEXT_INQUIRECOIN_CHANGE          110023      //"现在转换积分"


//返回操作

//积分查询及转换部分

//瞬飞开通部分

//升级服务
//新开Skill服务。最多开6个
//skill满技能服务
void learnFullLevelSkill(Player* pPlayer,uint32 spellid,uint32 skillid ,uint32 coseCoin) {
	if (!pPlayer->HasSkill(skillid)) {
		if (pPlayer->GetFreePrimaryProfessionPoints() <= 0) {
			pPlayer->GetSession()->SendNotification("你无法再学习新的技能.");
			return;
		}
	}
	if (pPlayer->getVipInfo(-1)<coseCoin) {
		pPlayer->GetSession()->SendNotification("积分点数不足.");
		return;
	}
	pPlayer->costVipCoin(2, coseCoin);
	pPlayer->learnSpell(spellid, false);
	pPlayer->SetSkill(skillid, 300, 300);
}
//改名服务
/*void SendChildMenu_GOSSIP_SENDER_CHANGENAME(Player* pPlayer, Creature* pCreature, uint32 uiAction) {
	switch (uiAction)
	{
		case 3:
			char sMessage[100];
			sprintf(sMessage, "尊敬的%s ,修改名字需要%d积分.", pPlayer->GetName(), C_CHANGENAME_COIN);
			pPlayer->SEND_GOSSIP_TEXT(sMessage);
			if (pPlayer->getVipInfo(-1) >= C_CHANGENAME_COIN) {
				pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, GOSSIP_VIP_TEXT_CHANGENAME_STRING, GOSSIP_SENDER_CHANGENAME, GOSSIP_SENDER_CHANGENAME_CHANGE, "请在输入框中填写新名字?", 0);
			}
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VIP_TEXT_BACK, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_BACK);
	
			pPlayer->SEND_GOSSIP_MENU(0x7FFFFFFF, pCreature->GetGUID()); //80001为VIP商人菜单
		break;
		case GOSSIP_SENDER_CHANGENAME_CHANGE:
			if (pPlayer->getVipInfo(-1) >= C_CHANGENAME_COIN) {
				
			}
		break;
	}

}*/
void SendChildMenu_GOSSIP_SENDER_MAIN(Player* pPlayer, Creature* pCreature) {
	pPlayer->PlayerTalkClass->ClearMenus();
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VIP_TEXT_INQUIRECOIN, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INQUIRECOIN);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VIP_TEXT_INSTANTFLIGHT, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INSTANTFLIGHT);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VIP_TEXT_ADDSKILL, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL);
	//pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VIP_TEXT_CHANGERACE, GOSSIP_SENDER_CHANGERACE, 4);
	if (pPlayer->GetInfoLevel() < DEFAULT_MAX_LEVEL)
	{
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VIP_TEXT_LEVELUP, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_LEVELUP);
	}
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_VIP_TEXT_VENDOR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
	
	char sMessage[100];
	//欢迎您，%s
	sprintf(sMessage, sObjectMgr.GetBroadcastText(110024, 3, pPlayer->getGender(),true), pPlayer->GetName());
	pPlayer->SEND_GOSSIP_TEXT("赞助商人",sMessage);
	pPlayer->SEND_GOSSIP_MENU(0x7FFFFFFF, pCreature->GetGUID()); //80001为VIP商人菜单

}
bool GossipHello_npc_prof_vipnpc(Player* pPlayer, Creature* pCreature)
{
	SendChildMenu_GOSSIP_SENDER_MAIN(pPlayer,pCreature);

	return true;

}
void SendChildMenu_GOSSIP_SENDER_INQUIRECOIN(Player* pPlayer, Creature* pCreature) {
	pPlayer->PlayerTalkClass->ClearMenus();
	char sMessage[100];
	int t_coin = (pPlayer->getVipInfoTimeToCoin() / C_TIMETOCOIN);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VIP_TEXT_INQUIRECOIN_CHANGE, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INQUIRECOIN_CHANGE);
	pPlayer->ADD_GOSSIP_ITEM(7, " |cff8000FF返回上一级菜单|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_BACK);

	//尊敬的 %s,您的剩余积分为 %d,未转化积分为 %d
	sprintf(sMessage, sObjectMgr.GetBroadcastText(110001, 3, pPlayer->getGender(), true), pPlayer->GetName(), pPlayer->getVipInfo(-1), t_coin);
	pPlayer->SEND_GOSSIP_TEXT("赞助商人", sMessage);
	pPlayer->SEND_GOSSIP_MENU(0x7FFFFFFF, pCreature->GetGUID()); //80001为VIP商人菜单
}
//升级服务菜单
void SendChildMenu_GOSSIP_SENDER_LEVELUP(Player* pPlayer, Creature* pCreature) {
	pPlayer->PlayerTalkClass->ClearMenus();
	char sMessage[100];
	if (pPlayer->getLevel()<DEFAULT_MAX_LEVEL) {
		//"使用%d点积分提升1级."
		sprintf(sMessage, sObjectMgr.GetBroadcastText(110010, 3, pPlayer->getGender()), C_LEVELUP_COIN);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sMessage, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_LEVELUP_ONE);
		//使用%d点积分迅速升级到%d级
		sprintf(sMessage, sObjectMgr.GetBroadcastText(110011, 3, pPlayer->getGender()), C_MAXLEVEL_COIN, DEFAULT_MAX_LEVEL);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sMessage, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_LEVELUP_ALL);
		pPlayer->ADD_GOSSIP_ITEM(7, " |cff8000FF返回上一级菜单|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_BACK);
		//使用游戏积分提升等级会影响游戏体验，您想好了使用了吗?
		sprintf(sMessage, sObjectMgr.GetBroadcastText(110012, 3, pPlayer->getGender()));
		pPlayer->SEND_GOSSIP_TEXT("赞助商人", sMessage);
		pPlayer->SEND_GOSSIP_MENU(0x7FFFFFFF, pCreature->GetGUID()); //80001为VIP商人菜单
	}
	else {
		//您已经不需要这项服务了
		pCreature->MonsterSay(sObjectMgr.GetBroadcastText(110013, 3, pPlayer->getGender()), LANG_UNIVERSAL);
	}
}
//瞬飞服务菜单
void SendChildMenu_GOSSIP_SENDER_FLYING(Player* pPlayer, Creature* pCreature) {
	uint32 timetemp = pPlayer->getVipInfo(2) - time(NULL);   //获取瞬飞到期时间和当前时间的差值
	char sMessage[100];
	if (pPlayer->getVipInfo(2) > 0)
	{
		if (timetemp > 0) {
			char sMessage[100];

			time_t currenttime = pPlayer->getVipInfo(2);

			char tmp[64];
			strftime(tmp, sizeof(tmp), " %Y-%m-%d %H:%M", localtime(&currenttime));

			//尊敬的 %s,您的瞬飞到期时间为 %s
			sprintf(sMessage, sObjectMgr.GetBroadcastText(110004, 3, pPlayer->getGender(), true),tmp);
			
			pPlayer->SEND_GOSSIP_TEXT("赞助商人", sMessage);
		}

	}
	else {
		//您还没有开通瞬飞
		pPlayer->SEND_GOSSIP_TEXT("赞助商人", sObjectMgr.GetBroadcastText(110005, 3, pPlayer->getGender()));
	}

	if (pPlayer->getVipInfo(2) > 0) {

		//花费 %d积分,续费1个月瞬飞服务
		sprintf(sMessage, sObjectMgr.GetBroadcastText(110006, 3, pPlayer->getGender()), C_FLYINGMON_COIN);

	}
	else {
		//1个月瞬飞服务需要花费 %d积分,现在开通吗?
		sprintf(sMessage, sObjectMgr.GetBroadcastText(110007, 3, pPlayer->getGender()), C_FLYINGMON_COIN);

	}
	pPlayer->PlayerTalkClass->ClearMenus();
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sMessage, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INSTANTFLIGHT_START); //611
	pPlayer->ADD_GOSSIP_ITEM(7, " |cff8000FF返回上一级菜单|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_BACK);
	pPlayer->SEND_GOSSIP_MENU(0x7FFFFFFF, pCreature->GetGUID()); //80001为VIP商人菜单

}

//技能学习子菜单菜单
void SendChildMenu_GOSSIP_SENDER_SKILL(Player* pPlayer, Creature* pCreature) {
	
	char sMessage[100];
	
		pPlayer->PlayerTalkClass->ClearMenus();
		//使用%d点积分增加一个新技能
		sprintf(sMessage, sObjectMgr.GetBroadcastText(110034, 3, pPlayer->getGender()), C_NEW_SKILL_COIN);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sMessage, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL_ONE);
		//使用%d点积分迅速升级到%d级
		sprintf(sMessage, sObjectMgr.GetBroadcastText(110035, 3, pPlayer->getGender()), C_MAX_SKILL_COIN);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sMessage, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL_MENU);
		pPlayer->ADD_GOSSIP_ITEM(7, " |cff8000FF返回上一级菜单|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_BACK);
		//使用游戏积分提升等级会影响游戏体验，您想好了使用了吗?
		sprintf(sMessage, sObjectMgr.GetBroadcastText(110036, 3, pPlayer->getGender()), sWorld.getConfig(CONFIG_UINT32_MAX_PRIMARY_TRADE_SKILL) + pPlayer->m_skillCount);
		pPlayer->SEND_GOSSIP_TEXT("赞助商人", sMessage);
		pPlayer->SEND_GOSSIP_MENU(0x7FFFFFFF, pCreature->GetGUID()); //80001为VIP商人菜单
	
	

}
//技能学满子菜单菜单
void SendChildMenu_GOSSIP_SENDER_SKILLSMENU(Player* pPlayer, Creature* pCreature) {
	char sMessage[100];
	pPlayer->PlayerTalkClass->ClearMenus();
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " |CFF0000FF裁缝技能学满|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL_MENU+1);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " |CFF0000FF附魔技能学满|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL_MENU+2);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " |CFF0000FF采矿技能学满|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL_MENU+3);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " |CFF0000FF采药技能学满|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL_MENU+4);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " |CFF0000FF炼金技能学满|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL_MENU+5);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " |CFF0000FF锻造技能学满|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL_MENU+6);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " |CFF0000FF剥皮技能学满|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL_MENU+7);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " |CFF0000FF制皮技能学满|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL_MENU+8);
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, " |CFF0000FF工程技能学满|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_ADDSKILL_MENU+9);
		pPlayer->ADD_GOSSIP_ITEM(7, " |cff8000FF返回上一级菜单|CFF009933 ", GOSSIP_SENDER_MAIN, GOSSIP_SENDER_SKILLSMENU_BACK);
		//使用游戏积分提升等级会影响游戏体验，您想好了使用了吗?
		sprintf(sMessage, sObjectMgr.GetBroadcastText(110012, 3, pPlayer->getGender()));
		pPlayer->SEND_GOSSIP_TEXT("赞助商人", sMessage);
		pPlayer->SEND_GOSSIP_MENU(0x7FFFFFFF, pCreature->GetGUID()); //80001为VIP商人菜单
	
}
//菜单选择主函数

bool GossipSelect_npc_prof_vipnpc(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	
	uint32 timetemp = pPlayer->getVipInfo(2) - time(NULL);   //获取瞬飞到期时间和当前时间的差值
	int flag = pPlayer->setVipMemberCoin(C_TIMETOCOIN);  //每7200秒转换1分
	int t_coin = (pPlayer->getVipInfoTimeToCoin() / C_TIMETOCOIN);
	char sMessage[100];
	switch (uiAction)
	{
	case GOSSIP_SENDER_INQUIRECOIN:   //查询积分
		SendChildMenu_GOSSIP_SENDER_INQUIRECOIN(pPlayer, pCreature);
	
		break;
	case GOSSIP_SENDER_INQUIRECOIN_CHANGE:     //转换积分
		
		if (flag < 0) {
		}
		else if (flag == 0) {
			// "您的等级未达到 %d 级."
			sprintf(sMessage, sObjectMgr.GetBroadcastText(110002, 3, pPlayer->getGender()), DEFAULT_MAX_LEVEL);
			pCreature->MonsterSay(sMessage, LANG_UNIVERSAL);
		}
		else if (flag == 1) {
			//"转换了 %d 积分."
			sprintf(sMessage, sObjectMgr.GetBroadcastText(110003, 3, pPlayer->getGender()), t_coin);
			pCreature->MonsterSay(sMessage, LANG_UNIVERSAL);
			pPlayer->CLOSE_GOSSIP_MENU();

		}
		break;
	case GOSSIP_SENDER_INSTANTFLIGHT:  //瞬飞服务子菜单
		SendChildMenu_GOSSIP_SENDER_FLYING(pPlayer,pCreature);
	
		break;
	case GOSSIP_SENDER_INSTANTFLIGHT_START: //点击瞬飞操作

		if (pPlayer->getVipInfo(-1) >= C_FLYINGMON_COIN) {
			pPlayer->setUpdateVIPFlyingTime(C_FLYINGMONSECOND, C_FLYINGMON_COIN);
			
			time_t currenttime = pPlayer->getVipInfo(2);
			char tmp[64];

			strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&currenttime));
			//瞬飞已开通,您的瞬飞时间到期时间为 %s
			sprintf(sMessage, sObjectMgr.GetBroadcastText(110008, 3, pPlayer->getGender()), tmp);
			pCreature->MonsterSay(sMessage, LANG_UNIVERSAL, pPlayer);
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		else {
			//积分不足,开通服务需要%d积分 
			sprintf(sMessage, sObjectMgr.GetBroadcastText(110009, 3, pPlayer->getGender()), C_FLYINGMON_COIN);
			pCreature->MonsterSay(sMessage, LANG_UNIVERSAL, pPlayer);
		}
		
		break;
	case GOSSIP_SENDER_CHANGENAME:     //改名
		//SendActionMenu_npc_prof_leather(pPlayer, pCreature, uiAction);
		break;
	case GOSSIP_SENDER_CHANGERACE:     //修改种族
		//SendActionMenu_npc_prof_leather(pPlayer, pCreature, uiAction);
		break;
	case GOSSIP_SENDER_LEVELUP:        //升级服务子菜单
		SendChildMenu_GOSSIP_SENDER_LEVELUP(pPlayer, pCreature);
		
		break;
	case GOSSIP_SENDER_LEVELUP_ONE:     //单级提升操作

		if (pPlayer->getVipInfo(-1) >= C_LEVELUP_COIN) {
			//char sMessage[100];
			pPlayer->LevelUp(1, C_LEVELUP_COIN);
			//等级提升为 %d级
			sprintf(sMessage, sObjectMgr.GetBroadcastText(110014, 3, pPlayer->getGender()), pPlayer->getLevel());
			pCreature->MonsterSay(sMessage, LANG_UNIVERSAL);
			if (pPlayer->getLevel() == DEFAULT_MAX_LEVEL)
			{
				SendChildMenu_GOSSIP_SENDER_MAIN(pPlayer,pCreature);
			}
		}
		else {
			
			sprintf(sMessage, sObjectMgr.GetBroadcastText(110009, 3, pPlayer->getGender()), C_LEVELUP_COIN);
			pCreature->MonsterSay(sMessage, LANG_UNIVERSAL);

		}
		
		
		break;
	case GOSSIP_SENDER_LEVELUP_ALL:   //秒升提升操作

		if (pPlayer->getVipInfo(-1) >= C_LEVELUP_COIN) {
			
			pPlayer->LevelUp((DEFAULT_MAX_LEVEL - pPlayer->GetInfoLevel()), C_MAXLEVEL_COIN);
			//等级提升为 %d级
			sprintf(sMessage, sObjectMgr.GetBroadcastText(110014, 3, pPlayer->getGender()), DEFAULT_MAX_LEVEL);
			pCreature->MonsterSay(sMessage, LANG_UNIVERSAL);
			pPlayer->CLOSE_GOSSIP_MENU();
		}
		if (pPlayer->GetInfoLevel() == DEFAULT_MAX_LEVEL)
		{
			SendChildMenu_GOSSIP_SENDER_MAIN(pPlayer,pCreature);
		}
		
		break;
	case GOSSIP_ACTION_TRADE:        //交易商店
		pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
	
		break;
	case  GOSSIP_SENDER_BACK:        //返回
	case  GOSSIP_SENDER_INSTANTFLIGHT_BACK:   //瞬飞子菜单返回
	case  GOSSIP_SENDER_LEVELUP_BACK:    //等级子菜单返回
	case  GOSSIP_SENDER_INQUIRECOIN_BACK:// 积分修改子菜单返回
	case  GOSSIP_SENDER_ADDSKILL_BACK://技能学习子菜单返回

		SendChildMenu_GOSSIP_SENDER_MAIN(pPlayer,pCreature);
		
		break;
	case GOSSIP_SENDER_SKILLSMENU_BACK:  //返回技能学习类菜单
		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);
		break;
	case GOSSIP_SENDER_ADDSKILL_ONE://增加一个技能项
		if (pPlayer->m_skillCount>sWorld.getConfig(CONFIG_UINT32_MAX_PRIMARY_SKILL_COUNT)) {
			ChatHandler(pPlayer).SendSysMessage("你无法再学习新的技能.");
			
			break;
		}

		pPlayer->costVipCoin(2, C_NEW_SKILL_COIN);
		pPlayer->m_skillCount = pPlayer->m_skillCount + 1;

		pPlayer->SetFreePrimaryProfessions(pPlayer->GetFreePrimaryProfessionPoints() + 1);
		ChatHandler(pPlayer).SendSysMessage("可以学习一个新的技能了.");

		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);
		break;
	case GOSSIP_SENDER_ADDSKILL:// 技能学习类菜单
		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);
		break;
	case GOSSIP_SENDER_ADDSKILL_MENU:// 技能学习类菜单
		SendChildMenu_GOSSIP_SENDER_SKILLSMENU(pPlayer, pCreature);
		break;
	case GOSSIP_SENDER_ADDSKILL_MENU + 1:  //裁缝技能学满
		learnFullLevelSkill(pPlayer, 12180, 197, C_MAX_SKILL_COIN);
		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);
		break;
		break;
	case GOSSIP_SENDER_ADDSKILL_MENU + 2:  //附魔技能学满
		learnFullLevelSkill(pPlayer, 13920,333, C_MAX_SKILL_COIN);
		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);
		break;
	case GOSSIP_SENDER_ADDSKILL_MENU + 3:  //采矿技能学满
		learnFullLevelSkill(pPlayer, 10248, 186, C_MAX_SKILL_COIN);
		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);
		break;
	case GOSSIP_SENDER_ADDSKILL_MENU + 4:  //采药技能学满 182

		learnFullLevelSkill(pPlayer, 11993, 182, C_MAX_SKILL_COIN);
		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);

		break;
    case GOSSIP_SENDER_ADDSKILL_MENU + 5:  //炼金技能学满 182
		learnFullLevelSkill(pPlayer, 11611, 171, C_MAX_SKILL_COIN);
		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);
		break;
	case GOSSIP_SENDER_ADDSKILL_MENU + 6:  //锻造学满 182
		learnFullLevelSkill(pPlayer, 9785, 164, C_MAX_SKILL_COIN);
		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);
		break;
	case GOSSIP_SENDER_ADDSKILL_MENU + 7:  //剥皮学满 393
		learnFullLevelSkill(pPlayer, 10768, 393, C_MAX_SKILL_COIN);
		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);
		break;
	case GOSSIP_SENDER_ADDSKILL_MENU + 8:  //制皮学满 165
		learnFullLevelSkill(pPlayer, 10662, 165, C_MAX_SKILL_COIN);
		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);
		break;
	case GOSSIP_SENDER_ADDSKILL_MENU + 9:  //工程学满 165
		learnFullLevelSkill(pPlayer, 12656, 202, C_MAX_SKILL_COIN);
		SendChildMenu_GOSSIP_SENDER_SKILL(pPlayer, pCreature);
		break;
	}
	
	return true;
}


void AddSC_npc_vip()
{
	Script *newscript;

	newscript = new Script;
	newscript->Name = "npc_prof_vipnpc";
	newscript->pGossipHello = &GossipHello_npc_prof_vipnpc; //主菜单
	newscript->pGossipSelect = &GossipSelect_npc_prof_vipnpc;
	newscript->RegisterSelf();
	/*newscript = new Script;
	newscript->Name = "go_soothsaying_for_dummies";
	newscript->pGOHello =  &GOHello_go_soothsaying_for_dummies;
	//newscript->pGossipSelect = &GossipSelect_go_soothsaying_for_dummies;
	newscript->RegisterSelf();*/
}
