//XSkillEffect
#include "XSkillEffect.h"
static XSkillEffect* instance;

XSkillEffect* XSkillEffect::record(Value v){ 
	if(instance==NULL) instance=new XSkillEffect();
	if(instance->doc.IsNull()){
		std::string fullPath=FileUtils::getInstance()->fullPathForFilename("XSkillEffect.json");
		std::string str=FileUtils::getInstance()->getStringFromFile(fullPath);
		instance->doc.Parse<0>(str.c_str());
		if(instance->doc.HasParseError()){
			log("GetParseError %s",instance->doc.GetParseError());
		}
	}
	instance->v=v;
	return instance;
}
int XSkillEffect::getId(){
	return doc[v.asString().c_str()]["id"].GetInt();
}
std::string XSkillEffect::getSpell(){
	return doc[v.asString().c_str()]["spell"].GetString();
}
std::string XSkillEffect::getCast(){
	return doc[v.asString().c_str()]["cast"].GetString();
}
std::string XSkillEffect::getBullet(){
	return doc[v.asString().c_str()]["bullet"].GetString();
}
int XSkillEffect::getBulletType(){
	return doc[v.asString().c_str()]["bulletType"].GetInt();
}
int XSkillEffect::getParam1(){
	return doc[v.asString().c_str()]["param1"].GetInt();
}
int XSkillEffect::getParam2(){
	return doc[v.asString().c_str()]["param2"].GetInt();
}
int XSkillEffect::getParam3(){
	return doc[v.asString().c_str()]["param3"].GetInt();
}
int XSkillEffect::getParam4(){
	return doc[v.asString().c_str()]["param4"].GetInt();
}
int XSkillEffect::getParam5(){
	return doc[v.asString().c_str()]["param5"].GetInt();
}
std::string XSkillEffect::getHit(){
	return doc[v.asString().c_str()]["hit"].GetString();
}
