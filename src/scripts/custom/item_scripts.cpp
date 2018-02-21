
#include "scriptPCH.h"

#include "spell.h"
#define C_DOUBLE_TALENT_COIN          300           //需要300积分开双天赋一个月
#define C_TALENTMONSECOND         2592000           //双天赋30天的秒数

bool FullLevelItem_OnUse(Player* player, Item* item, SpellCastTargets const& target)
{
	if (player->InBattleGround() || player->IsFlying() || player->isInCombat()) {
		ChatHandler(player).SendSysMessage("您当前不能使用这个卷轴哦!");
		
		return false;
	}
	if (player->getLevel() == DEFAULT_MAX_LEVEL) {
		ChatHandler(player).SendSysMessage("您已经最高级了，做人不要太贪心哦!");
		return false;
	}
	player->SetLevel(DEFAULT_MAX_LEVEL);
	return true;
}



bool Item_OnUse(Player* player, Item* item, SpellCastTargets const& target)
{

	//int64 timetemp = player->memberEXInfo.talenttime - time(NULL);   //获取双天赋到期时间和当前时间的差值
	player->PlayerTalkClass->ClearMenus();
	if ((time_t)player->memberEXInfo.talenttime<= time(NULL) && player->m_specsCount>1) {
		player->memberEXInfo.talenttime = 0;
		if (player->m_activeSpec != 0) {
			player->ActivateSpec(0);
		}
		player->m_activeSpec = 0;
		player->m_specsCount = 1;
	
	}

	if (player->m_specsCount > 1) {
		char sMessage[150];

		char tmp[64];
		time_t currenttime = player->memberEXInfo.talenttime;
		strftime(tmp, sizeof(tmp), " %Y-%m-%d %H", localtime(&currenttime));
		sprintf(sMessage, sObjectMgr.GetBroadcastText(110025, 3, player->getGender(), true), tmp, C_DOUBLE_TALENT_COIN);
		player->ADD_GOSSIP_ITEM(0, sMessage, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		for (int i = 0; i < player->m_specsCount; ++i){
			if (i!= player->m_activeSpec){
				sprintf(sMessage, sObjectMgr.GetBroadcastText(110029, 3, player->getGender(), true), i+1);
				player->ADD_GOSSIP_ITEM(0, sMessage, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + i+2);
			}
		}
		
	}else {
		char sMessage[200];
		char titleMessage[100];
		if (player->memberEXInfo.talenttime > 0)
		{
			//还有时间
			if ((time_t)player->memberEXInfo.talenttime> time(NULL)) {

				time_t currenttime = player->memberEXInfo.talenttime;

				char tmp[64];
				strftime(tmp, sizeof(tmp), " %Y-%m-%d %H:%M", localtime(&currenttime));

				//尊敬的 %s,您的瞬飞到期时间为 %s
				sprintf(sMessage, sObjectMgr.GetBroadcastText(110025, 3, player->getGender(), true), player->GetName(), tmp);
				//显示续月菜单
				sprintf(titleMessage, sObjectMgr.GetBroadcastText(110027, 3, player->getGender()), C_DOUBLE_TALENT_COIN);
				//player->PlayerTalkClass->SendText(item->GetProto()->Name1, sMessage);
			}
			else {
				//显示开通菜单

				sprintf(titleMessage, sObjectMgr.GetBroadcastText(110026, 3, player->getGender()), C_DOUBLE_TALENT_COIN);
			}
			
		}else{
			
			
			//1个月双天赋服务需要花费%d积分,现在开通吗?
			sprintf(titleMessage, sObjectMgr.GetBroadcastText(110026, 3, player->getGender()), C_DOUBLE_TALENT_COIN);
			
		}

		//
		player->ADD_GOSSIP_ITEM(0, titleMessage, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
	}
	
	//110028
	player->SEND_GOSSIP_MENU(700001, item->GetGUID());
	//player->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, item->GetGUID());
	return true;
}


	bool OnGossipSelect(Player* player, Item* item, uint32 sender, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		char sMessage[200];

		if (action == GOSSIP_ACTION_INFO_DEF + 1) {
			if (player->getVipInfo(-1) >= C_DOUBLE_TALENT_COIN) {
				//开通双天赋操作
				if (player->m_specsCount = 1) {
					player->m_specsCount = player->m_specsCount + 1;
				}
				player->setUpdateDoubleTalentTime(C_TALENTMONSECOND, C_DOUBLE_TALENT_COIN);

				time_t currenttime =player->memberEXInfo.talenttime;
				char tmp[64];

				strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M", localtime(&currenttime));
				//双天赋已开通,您的双天赋到期时间为 %s.
				sprintf(sMessage, sObjectMgr.GetBroadcastText(110030, 3, player->getGender()), tmp);
		
			}
			else {
				//积分不足,开通服务需要%d积分 
				sprintf(sMessage, sObjectMgr.GetBroadcastText(110009, 3, player->getGender()), C_DOUBLE_TALENT_COIN);
				
			}
			ChatHandler(player).SendSysMessage(sMessage);
			player->CLOSE_GOSSIP_MENU();
			
		}else {
			int64 timetemp = player->memberEXInfo.talenttime - time(NULL);   //获取双天赋到期时间和当前时间的差值
			//当前有天赋时间并且天赋数量大于切换的天赋
			if (timetemp > 0 && player->m_specsCount > action - GOSSIP_ACTION_INFO_DEF - 2) {
				player->ActivateSpec(action - GOSSIP_ACTION_INFO_DEF - 2);
				//切换为第%u天赋
				sprintf(sMessage, sObjectMgr.GetBroadcastText(110029, 3, player->getGender(), true), action - GOSSIP_ACTION_INFO_DEF - 1);
				ChatHandler(player).SendSysMessage(sMessage);

			}
			player->CLOSE_GOSSIP_MENU();
		}
		
		return true;
	}



void AddSC_item_scripts()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "Talent_Book";
    newscript->pItemUse = &Item_OnUse;
	newscript->pItGossipSelect = &OnGossipSelect;
	newscript->RegisterSelf();
	newscript = new Script;
	newscript->Name = "FullLevel_Book";
	newscript->pItemUse = &FullLevelItem_OnUse;
	newscript->RegisterSelf();
	

}
