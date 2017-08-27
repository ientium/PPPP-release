INSERT INTO `migrations` VALUES ('20170724105533'); 

-- Missing movement script to switch to random movement.
-- Used by Rookery Hatcher, Rookery Guardian and Solakar Flamewreath.
DELETE FROM `creature_movement_scripts` WHERE `id`=1026404;
INSERT INTO `creature_movement_scripts` (`id`, `delay`, `command`, `datalong`, `datalong2`, `datalong3`, `datalong4`, `data_flags`, `dataint`, `dataint2`, `dataint3`, `dataint4`, `x`, `y`, `z`, `o`, `comments`) VALUES (1026404, 0, 20, 1, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 'UBRS-Rookery event: Random movement around current position');
-- Missing texts for Rookery Hatcher and Solakar Flamewreath.
INSERT INTO `creature_ai_scripts` (`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) VALUES (1026402, 10264, 11, 0, 100, 0, 0, 0, 0, 0, 1, -5547, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Solakar Flamewreath - Yell Text on Spawn');
INSERT INTO `creature_ai_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES (-5547, 'I am here!  Now, puny little worms, you will pay for your intrusion!', '이 보잘것없는 벌레들아, 내가 왔다! 침입을 한 대가를 치르게 해 주마!', 'Je suis là ! Maintenant, lamentables petites limaces, vous allez payer votre intrusion !', 'Ich bin hier! Jetzt, ihr elenden kleinen Würmer, werdet ihr für euer Eindringen bezahlen!', '我在这儿！可悲的渣滓，你们会为侵入这里付出代价的！', '我在這兒!可悲的渣滓，你們會為侵入這裡付出代價的!', '¡Aquí estoy! Ahora, pequeños gusanos insignificantes, ¡pagaréis por vuestra intromisión!', '¡Aquí estoy! Ahora, pequeños gusanos insignificantes, ¡pagarán por su intromisión!', 'А вот и я! Теперь, жалкие червячки, вы поплатитесь за свое вторжение!', 0, 1, 0, 0, 'Solakar Flamewreath - Yell on Spawn');
INSERT INTO `script_texts` (`entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES (-1229020, 'Intruders are destroying our eggs!  Stop!!', '침입자들이 우리 알을 파괴하고 있다! 저지하라!!', 'Des intrus détruisent nos œufs ! Arrêtez !', 'Eindringlinge vernichten unsere Eier! Halt!!!', '入侵者正在破坏我们的蛋！住手！！', '入侵者正在破壞我們的蛋!住手!!', '¡Unos intrusos están destruyendo nuestros huevos! ¡Basta!', '¡Unos intrusos están destruyendo nuestros huevos! ¡Basta!', 'Враги уничтожают нашу кладку! Остановить!', 0, 1, 0, 0, 'rookery hatcher - SAY_ROOKERY_EVENT_START');
-- They should start with waypoint movement, and it gets switched to random at last waypoint.
UPDATE `creature_template` SET `MovementType`=2 WHERE `entry` IN (10258, 10264, 10683);