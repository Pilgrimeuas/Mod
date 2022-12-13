#include "config.h"
#include <io.h>
#include "Utils.h"
//#include "Logger.h"
//#include <fstream>
//#include <iostream>
//#include <vector>

std::string config::currentSaveConfigFile = "Default";					// ָʾ��ǰʹ�õ������ļ���Ĭ��ֵ Ҳ����Ĭ��ʹ�� Default.json ��������ļ�

std::string config::getConfigFilePath() {
	static std::string configFilePath = Utils::WStringToString(Utils::GetRoamingFolderPath()) + "\\Mod\\Config\\";
	return configFilePath;
}


std::vector<std::string> config::findAllConfigFile() {
	std::vector<std::string> files;
	intptr_t hFile = 0;
	struct _finddata_t fileinfo;
	if ((hFile = _findfirst(getConfigFilePath().append("*.json").c_str(),&fileinfo)) != -1) {
		do {
			if (!(fileinfo.attrib & _A_SUBDIR)) {
				if (strcmp(fileinfo.name, "config.json") != 0) {				// config.json ��Ϊ�̶�����,����������ģ����Ϣ�����ò�һ��
					auto fname = std::string(fileinfo.name);
					auto find = fname.find(".json");
					files.push_back(fname.substr(0, find));
				}
			}
			else {
				//�ݹ��ѯ�ڲ��ļ��� ���ﲻ��Ҫ
			}
		} while (_findnext(hFile, &fileinfo) == 0);
	}
	_findclose(hFile);
	return files;
}



json config::loadConfigonRootFromFile(const std::string& name) {
	json ret = {};
	std::ifstream f((getConfigFilePath() + name + ".json").c_str());
	if (f.good())								//��ʾ�����ļ�����
	{
		f >> ret;
		f.close();
	}
	return ret;
}

json config::loadConfigonRootFromDefaultFile() {
	return loadConfigonRootFromFile("Default");
}

json config::loadConfigFromFile(const std::string& name, std::string key) {
	auto root = loadConfigonRootFromFile(name);
	if (root.contains(key)) {
		return root[key];
	}
	else {
		return {};
	}
}

json config::loadConfigFromDefaultFile(std::string key) {
	return loadConfigFromFile("Default", key);
}

// д������
bool config::writeConfigonRootToFile(const std::string& name, json data) {
	std::ofstream c((getConfigFilePath() + name + ".json").c_str());
	c << data.dump(2);
	c.close();
	return true;
}

bool config::writeConfigonRootFromDefaultFile(json data) {
	return writeConfigonRootToFile("Default", data);
}

