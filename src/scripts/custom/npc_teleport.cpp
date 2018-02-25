#include "scriptPCH.h"
#include "Player.h"
#include "GossipDef.h"
#include "Opcodes.h"

void sendMainMenu(Player* player, Item* item) {
	
	player->ADD_GOSSIP_ITEM(1, " |cff8000FF【世界竞技中心】|CFF009933 ", 1, GOSSIP_ACTION_INFO_DEF + 12);
	player->ADD_GOSSIP_ITEM(1, " |CFF0000FF【世界主城传送】|CFF009933 ", 1, GOSSIP_ACTION_INFO_DEF + 1);
	player->ADD_GOSSIP_ITEM(1, " |CFF0000FF【初级副本传送】|CFF009933 ", 1, GOSSIP_ACTION_INFO_DEF + 3);
	player->ADD_GOSSIP_ITEM(1, " |CFF0000FF【中级副本传送】|CFF009933 ", 1, GOSSIP_ACTION_INFO_DEF + 4);
	player->ADD_GOSSIP_ITEM(1, " |CFF0000FF【团队副本传送】|CFF009933 ", 1, GOSSIP_ACTION_INFO_DEF + 5);
	player->ADD_GOSSIP_ITEM(1, " |CFF0000FF【世界战场传送】|CFF009933 ", 1, GOSSIP_ACTION_INFO_DEF + 8);
	player->ADD_GOSSIP_ITEM(1, " |CFF0000FF【附加特殊功能】|CFF009933 ", 1, GOSSIP_ACTION_INFO_DEF + 9);
	player->SEND_GOSSIP_MENU(999999, item->GetGUID());
}
bool GossipHello_npc_teleport(Player* player, Item* item)
{
	player->PlayerTalkClass->ClearMenus();
	sendMainMenu(player, item);
	return true;
}

void SendDefaultMenu_npc_teleport(Player* player, Item* item, uint32 action)
{
	switch (action) {
		// 世界竞技中心
	case GOSSIP_ACTION_INFO_DEF + 12:
		player->TeleportTo(0, -13204, 276, 30, 3.5);
		break;
		// 世界主城
	case GOSSIP_ACTION_INFO_DEF + 1:
		if (player->getRace() == 1 || player->getRace() == 3 || player->getRace() == 4 || player->getRace() == 7 || player->getRace() == 11)
		{
			player->ADD_GOSSIP_ITEM(2, " |cff8000FF攻打 奥格瑞玛|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 5);
			player->ADD_GOSSIP_ITEM(2, " |CFF0000FF联盟 暴风城|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 1);
			player->ADD_GOSSIP_ITEM(2, " |CFF0000FF联盟 铁炉堡|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 2);
			player->ADD_GOSSIP_ITEM(2, " |CFF0000FF联盟 达纳苏斯|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 3);
			
		}
		else {             // 部落
			player->ADD_GOSSIP_ITEM(2, " |cff8000FF攻打 暴风城|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 1);
			player->ADD_GOSSIP_ITEM(2, " |CFF0000FF部落 奥格瑞玛|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 5);
			player->ADD_GOSSIP_ITEM(2, " |CFF0000FF部落 雷霆崖|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 6);
			player->ADD_GOSSIP_ITEM(2, " |CFF0000FF部落 幽暗城|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 7);
			
		}
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF中立 棘齿城|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 9);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF中立 藏宝海湾|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 10);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF中立 冬泉谷|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 11);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF中立 加基森|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 12);

		player->ADD_GOSSIP_ITEM(7, " |cff8000FF返回上一级菜单|CFF009933 ", 2, GOSSIP_ACTION_INFO_DEF + 99);

		player->SEND_GOSSIP_MENU(999999,item->GetGUID());
		break;

		// 初级副本
	case GOSSIP_ACTION_INFO_DEF + 3:
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[14]怒焰裂谷|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 1);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[19]死亡矿井|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 2);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[22]哀嚎洞穴|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 3);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[24]影牙城堡|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 4);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[26]黑暗深渊|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 5);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[27]暴风城监狱|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 6);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[31]剃刀沼泽|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 7);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[33]诺莫瑞根|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 8);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[40]血色修道院|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 9);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[42]剃刀高地|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 10);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[45]奥达曼|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 11);

		player->ADD_GOSSIP_ITEM(7, " |cff8000FF返回上一级菜单|CFF009933 ", 4, GOSSIP_ACTION_INFO_DEF + 99);

		player->SEND_GOSSIP_MENU(999999,item->GetGUID());
		break;
		// 中级副本
	case GOSSIP_ACTION_INFO_DEF + 4:
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[46]祖尔法拉克|CFF009933 ", 5, GOSSIP_ACTION_INFO_DEF + 1);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[49]马拉顿|CFF009933 ", 5, GOSSIP_ACTION_INFO_DEF + 2);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[53]失落的神庙|CFF009933 ", 5, GOSSIP_ACTION_INFO_DEF + 3);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[57]黑石深渊|CFF009933 ", 5, GOSSIP_ACTION_INFO_DEF + 4);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[60]通灵学院|CFF009933 ", 5, GOSSIP_ACTION_INFO_DEF + 5);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[60]厄运[北区]|CFF009933 ", 5, GOSSIP_ACTION_INFO_DEF + 6);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[60]厄运[东区]|CFF009933 ", 5, GOSSIP_ACTION_INFO_DEF + 7);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[60]厄运[西区]|CFF009933 ", 5, GOSSIP_ACTION_INFO_DEF + 8);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[60]斯坦索姆|CFF009933 ", 5, GOSSIP_ACTION_INFO_DEF + 9);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[60]黑石塔下|CFF009933 ", 5, GOSSIP_ACTION_INFO_DEF + 10);

		player->ADD_GOSSIP_ITEM(7, " |cff8000FF返回上一级菜单|CFF009933 ", 5, GOSSIP_ACTION_INFO_DEF + 99);

		player->SEND_GOSSIP_MENU(999999,item->GetGUID());
		break;
		// 高级副本
	case GOSSIP_ACTION_INFO_DEF + 5:
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[团]溶火之心|CFF009933 ", 6, GOSSIP_ACTION_INFO_DEF + 1);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[团]黑石塔|CFF009933 ", 6, GOSSIP_ACTION_INFO_DEF + 2);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[团]祖尔格拉布|CFF009933 ", 6, GOSSIP_ACTION_INFO_DEF + 3);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[团]黑翼之巢|CFF009933 ", 6, GOSSIP_ACTION_INFO_DEF + 4);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[团]安其拉神庙|CFF009933 ", 6, GOSSIP_ACTION_INFO_DEF + 5);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[团]安其拉废墟|CFF009933 ", 6, GOSSIP_ACTION_INFO_DEF + 6);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[团]奥妮克希亚的巢穴|CFF009933 ", 6, GOSSIP_ACTION_INFO_DEF + 7);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF[团]纳克萨玛斯|CFF009933 ", 6, GOSSIP_ACTION_INFO_DEF + 8);


		player->ADD_GOSSIP_ITEM(7, " |cff8000FF返回上一级菜单|CFF009933 ", 6, GOSSIP_ACTION_INFO_DEF + 99);

		player->SEND_GOSSIP_MENU(999999,item->GetGUID());
		break;

		// 四大战场
	case GOSSIP_ACTION_INFO_DEF + 8:
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF奥特兰战场|CFF009933 ", 9, GOSSIP_ACTION_INFO_DEF + 2);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF战歌峡谷|CFF009933 ", 9, GOSSIP_ACTION_INFO_DEF + 3);
		player->ADD_GOSSIP_ITEM(2, " |CFF0000FF阿拉希战场|CFF009933 ", 9, GOSSIP_ACTION_INFO_DEF + 4);

		player->ADD_GOSSIP_ITEM(7, " |cff8000FF返回上一级菜单|CFF009933 ", 9, GOSSIP_ACTION_INFO_DEF + 99);

		player->SEND_GOSSIP_MENU(999999,item->GetGUID());
		break;
		// 附加功能
	case GOSSIP_ACTION_INFO_DEF + 9:
		player->ADD_GOSSIP_ITEM(1, " |CFF0000FF个人银行|CFF009933 ", 10, GOSSIP_ACTION_INFO_DEF + 2);
		player->ADD_GOSSIP_ITEM(1, " |CFF0000FF装备修复|CFF009933 ", 10, GOSSIP_ACTION_INFO_DEF + 3);
		player->ADD_GOSSIP_ITEM(1, " |CFF0000FF开飞行点|CFF009933 ", 10, GOSSIP_ACTION_INFO_DEF + 4);
		player->ADD_GOSSIP_ITEM(1, " |CFF0000FF地图全开|CFF009933 ", 10, GOSSIP_ACTION_INFO_DEF + 5);

		player->ADD_GOSSIP_ITEM(7, " |cff8000FF返回上一级菜单|CFF009933 ", 10, GOSSIP_ACTION_INFO_DEF + 99);
		player->SEND_GOSSIP_MENU(999999,item->GetGUID());
		break;
	}
}

bool GossipSelect_npc_teleport(Player *player, Item* item,  uint32 sender, uint32 action)
{
	switch (sender) {
		// 主选单
	case 1:
		SendDefaultMenu_npc_teleport(player, item, action);
		break;
		// 各大主城
	case 2:
		switch (action) {
			// 暴风城 统一格式说明：(MapID, X, Y, Z, 0);

		case GOSSIP_ACTION_INFO_DEF + 1:
			player->TeleportTo(0, -8829, 626, 96, 4);
			break;
			// 铁炉堡
		case GOSSIP_ACTION_INFO_DEF + 2:

			player->TeleportTo(0, -4948, -921, 504, 5.3);

			break;
			// 达纳苏斯
		case GOSSIP_ACTION_INFO_DEF + 3:

			player->TeleportTo(1, 9951, 2319, 1340, 1.6);

			break;

			// 奥格瑞玛
		case GOSSIP_ACTION_INFO_DEF + 5:

			player->TeleportTo(1, 1541, -4435, 13, 3);

			break;
			// 雷霆崖
		case GOSSIP_ACTION_INFO_DEF + 6:

			player->TeleportTo(1, -1265, 76, 129, 3);


			break;
			// 幽暗城
		case GOSSIP_ACTION_INFO_DEF + 7:

			player->TeleportTo(0, 1607, 239, -50, 1);

			break;
			// 棘齿城
		case GOSSIP_ACTION_INFO_DEF + 9:

			player->TeleportTo(1, -977, -3788, 6, 0);

			break;
			// 藏宝海湾
		case GOSSIP_ACTION_INFO_DEF + 10:

			player->TeleportTo(0, -14406, 425, 10, 4);

			break;
			// 冬泉谷
		case GOSSIP_ACTION_INFO_DEF + 11:

			player->TeleportTo(1, 6706, -4647, 723, 1);

			break;
			// 加基森
		case GOSSIP_ACTION_INFO_DEF + 12:

			player->TeleportTo(1, -7135, -3787, 10, 6);

			break;
			// 返回
		case GOSSIP_ACTION_INFO_DEF + 99:
			sendMainMenu(player, item);
			break;
		}
		break;

		// 初级副本
	case 4:

		switch (action) {
			// [14]怒焰裂谷 统一格式说明：(MapID, X, Y, Z, 0);
		case GOSSIP_ACTION_INFO_DEF + 1:

			player->TeleportTo(389, 2.024650, -10.021000, -16.187500, 0);

			break;
			// [19]死亡矿井
		case GOSSIP_ACTION_INFO_DEF + 2:

			player->TeleportTo(36, -16.4, -383.07, 61.78, 0);

			break;
			// [22]哀嚎洞穴
		case GOSSIP_ACTION_INFO_DEF + 3:

			player->TeleportTo(43, -161.841995, 133.266998, -73.866203, 0);

			break;
			// [24]影牙城堡
		case GOSSIP_ACTION_INFO_DEF + 4:

			player->TeleportTo(33, -228.19, 2110.56, 76.89, 0);

			break;
			// [26]黑暗深渊
		case GOSSIP_ACTION_INFO_DEF + 5:

			player->TeleportTo(48, -150.367004, 102.995003, -40.555801, 0);

			break;
			// [27]暴风城监狱
		case GOSSIP_ACTION_INFO_DEF + 6:

			player->TeleportTo(34, 48.29, 0.45, -16.14, 0);

			break;
			// [31]剃刀沼泽
		case GOSSIP_ACTION_INFO_DEF + 7:

			player->TeleportTo(47, 1943, 1544, 82, 0);

			break;
			// [33]诺莫瑞根
		case GOSSIP_ACTION_INFO_DEF + 8:

			player->TeleportTo(90, -332.562988, -3.445, -152.845993, 0);

			break;
			// [40]血色修道院
		case GOSSIP_ACTION_INFO_DEF + 9:

			player->TeleportTo(189, 855.903992, 1321.939941, 18.673000, 0);

			break;
			// [42]剃刀高地
		case GOSSIP_ACTION_INFO_DEF + 10:

			player->TeleportTo(129, 2593.209961, 1109.459961, 51.093300, 0);

			break;
			// [45]奥达曼
		case GOSSIP_ACTION_INFO_DEF + 11:

			player->TeleportTo(70, -227.529007, 45.009800, -46.019600, 0);

			break;
			// 返回
		case GOSSIP_ACTION_INFO_DEF + 99:
			sendMainMenu(player, item);
			break;
		}
		break;
		// 中级副本
	case 5:

		switch (action) {
			// [46]祖尔法拉克 统一格式说明：(MapID, X, Y, Z, 0);
		case GOSSIP_ACTION_INFO_DEF + 1:

			player->TeleportTo(209, 1213, 841, 8.9, 0);

			break;
			// [49]玛拉顿
		case GOSSIP_ACTION_INFO_DEF + 2:
			player->TeleportTo(349, 1012.700012, -459.317993, -43.547100, 0);
			break;
			// [53]失落的神庙
		case GOSSIP_ACTION_INFO_DEF + 3:
			player->TeleportTo(109, -313.369995, 99.955399, -131.848999, 0);
			break;
			// [57]黑石深渊
		case GOSSIP_ACTION_INFO_DEF + 4:
			player->TeleportTo(230, 456.928986, 34.927700, -69.388100, 0);
			break;
			// [60]通灵学院
		case GOSSIP_ACTION_INFO_DEF + 5:

			player->TeleportTo(289, 199, 126, 135, 0);

			break;
			// [60]厄运之槌 (北区)
		case GOSSIP_ACTION_INFO_DEF + 6:

			player->TeleportTo(429, 255.164001, -17.024200, -2.560600, 0);

			break;
			// [60]厄运之槌 (东区)
		case GOSSIP_ACTION_INFO_DEF + 7:

			player->TeleportTo(429, 46.24, -155.53, -2.71349, 0);

			break;
			// [60]厄运之槌 (西区)
		case GOSSIP_ACTION_INFO_DEF + 8:

			player->TeleportTo(429, 32.722599, 159.417007, -3.470170, 0);

			break;
			// [60]斯坦索姆
		case GOSSIP_ACTION_INFO_DEF + 9:

			player->TeleportTo(329, 3392, -3379, 143, 0);

			break;
			// [60]黑石塔下
		case GOSSIP_ACTION_INFO_DEF + 10:

			player->TeleportTo(229, 78.19, -227.63, 49.72, 0);

			break;
			// 返回
		case GOSSIP_ACTION_INFO_DEF + 99:
			sendMainMenu(player, item);
			break;
		}
		break;
		// 团队副本
	case 6:
		switch (action) {
			// [团]溶火之心 统一格式说明：(MapID, X, Y, Z, 0);
		case GOSSIP_ACTION_INFO_DEF + 1:

			player->TeleportTo(409, 1089.601685, -470.190247, -106.413055, 0);

			break;
			// [团]黑石塔上
		case GOSSIP_ACTION_INFO_DEF + 2:

			player->TeleportTo(229, 78.339836, -227.793518, 49.7103, 0);

			break;
			// [团]祖尔格拉布
		case GOSSIP_ACTION_INFO_DEF + 3:

			player->TeleportTo(309, -11916, -1251.469971, 92.32, 0);

			break;
			// [团]黑翼之巢
		case GOSSIP_ACTION_INFO_DEF + 4:

			player->TeleportTo(469, -7674.470215, -1108.380005, 396.649994, 0);

			break;
			// [团]安其拉神庙
		case GOSSIP_ACTION_INFO_DEF + 5:

			player->TeleportTo(531, -8212.002930, 2034.474854, 129.141342, 0);

			break;
			// [团]安其拉废墟
		case GOSSIP_ACTION_INFO_DEF + 6:

			player->TeleportTo(509, -8443.475586, 1518.648560, 31.906958, 0);

			break;
			// [团]奥妮克希亚的巢穴
		case GOSSIP_ACTION_INFO_DEF + 7:

			player->TeleportTo(249, 30.010290, -58.840508, -5.325367, 0);

			break;
			// [团]纳克萨玛斯
		case GOSSIP_ACTION_INFO_DEF + 8:

			player->TeleportTo(533, 3005.87, -3435.01, 293.882, 0);

			break;
		
			// 返回
		case GOSSIP_ACTION_INFO_DEF + 99:
			sendMainMenu(player, item);
			break;
		}
		break;

	case 9:

		switch (action) {
			// 奥特兰战场（部落）
		case GOSSIP_ACTION_INFO_DEF + 2:

			player->TeleportTo(30, 390.553680, -283.560547, -42.987301, 3.135666);

			break;
			// 战歌峡谷（部落）
		case GOSSIP_ACTION_INFO_DEF + 3:

			player->TeleportTo(489, 1123.168823, 1462.474976, 315.564148, 3.464511);

			break;
			// 阿拉希战场（部落）
		case GOSSIP_ACTION_INFO_DEF + 4:

			player->TeleportTo(529, 855.156128, 828.636108, -57.707348, 2.812707);

			break;
			// 返回
		case GOSSIP_ACTION_INFO_DEF + 99:
			sendMainMenu(player, item);
			break;
		}
		break;
		// 附加功能
	case 10:
		switch (action) {
			// 个人银行
		case GOSSIP_ACTION_INFO_DEF + 2:
			player->GetSession()->SendShowBank(player->GetGUID());
			player->CLOSE_GOSSIP_MENU();
			break;
			// 装备修复
		case GOSSIP_ACTION_INFO_DEF + 3:
			player->DurabilityRepairAll(true, 0);
			player->GetSession()->SendAreaTriggerMessage("你的全部装备修理完毕");
			player->CLOSE_GOSSIP_MENU();
			break;
			//开飞行点
		case GOSSIP_ACTION_INFO_DEF + 4:

			for (uint8 i = 0; i<8; i++)
			{
				player->SetTaxiCheater(true);
			}
			player->GetSession()->SendAreaTriggerMessage("你的飞行点已全部打开");
			player->CLOSE_GOSSIP_MENU();

			break;
			//开地图
		case GOSSIP_ACTION_INFO_DEF + 5:

			for (uint8 i = 0; i<64; i++)
				player->SetFlag(PLAYER_EXPLORED_ZONES_1 + i, 0xFFFFFFFF);
			player->GetSession()->SendAreaTriggerMessage("你的地图已全开");
			player->CLOSE_GOSSIP_MENU();
			break;

			// 返回
		case GOSSIP_ACTION_INFO_DEF + 99:
			sendMainMenu(player, item);
			break;

		}
		break;

	}
	return true;
}
void AddSC_npc_teleport()
{
	Script *newscript;
	
	newscript = new Script;
	newscript->Name = "npc_teleport";
	newscript->pQItemUse = &GossipHello_npc_teleport;
	newscript->pItGossipSelect = &GossipSelect_npc_teleport;
	newscript->RegisterSelf();

}