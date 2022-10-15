#pragma once
#include <string>
#include "Json.hpp"

using namespace nlohmann;

class config {
public:
	static std::string currentSaveConfigFile;
public:
	//static bool setconfigFile(const std::string& name);								// �����׺ ͳһ��׺.json
	static std::string getConfigFilePath();												// ��ȡ�����ļ���Ŀ¼λ�� \\��β
	static std::vector<std::string> findAllConfigFile();								// �������ļ�Ŀ¼�� ��ȡ���к�׺Ϊjson���ļ�
	static json loadConfigonRootFromFile(const std::string& name);						// ��ȡĳ�������ļ��е�json,��������json����
	static json loadConfigonRootFromDefaultFile();										// ��ȡĬ�������ļ��е�json,��������json����
	static json loadConfigFromFile(const std::string& name, std::string key);			// ��ȡĳ�������ļ��е�json,����ָ��key��json����
	static json loadConfigFromDefaultFile(std::string key);								// ��ȡĬ�������ļ��е�json,����ָ��key��json����(Ĭ�������ļ�:Default.json)

	static bool writeConfigonRootToFile(const std::string& name, json data);			// ��jsonд�뵽����������
	static bool writeConfigonRootFromDefaultFile(json data);							// ��json��ȫд��Ĭ�������ļ���

	template <class T>
	static T readDataFromJson(json data, std::string key, T defdata);
};

template <class T>
T config::readDataFromJson(json data, std::string key, T defdata) {
	if (data.contains(key)) {
		return data[key];
	}
	else {
		return defdata;
	}
}